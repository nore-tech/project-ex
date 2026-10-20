// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXInventoryComponent.h"
#include "ProjectEX.h"
#include "ProjectEXItemDefinition.h"
#include "ProjectEXPickup.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Net/UnrealNetwork.h"

UProjectEXInventoryComponent::UProjectEXInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	ToggleInventoryKey = EKeys::Tab;
}

void UProjectEXInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UProjectEXInventoryComponent, Entries, COND_OwnerOnly);
}

void UProjectEXInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (bInventoryOpen)
	{
		SetInventoryInputMode(false);
		bInventoryOpen = false;
	}

	if (InventoryWidget)
	{
		InventoryWidget->RemoveFromParent();
		InventoryWidget = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

void UProjectEXInventoryComponent::BindInput(UEnhancedInputComponent* EnhancedInput)
{
	if (!EnhancedInput)
	{
		return;
	}

	const APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn || !Pawn->IsLocallyControlled())
	{
		return;
	}

	EnsureToggleAction();
	if (!ToggleInventoryAction)
	{
		return;
	}

	RegisterMappingContext(Pawn);
	EnhancedInput->BindAction(ToggleInventoryAction, ETriggerEvent::Started, this, &UProjectEXInventoryComponent::ToggleInventory);
}

int32 UProjectEXInventoryComponent::AddItem(UProjectEXItemDefinition* Definition, int32 Quantity)
{
	if (!HasInventoryAuthority() || !Definition || Quantity <= 0)
	{
		return 0;
	}

	const int32 MaxStack = FMath::Max(1, Definition->MaxStackSize);
	int32 Remaining = Quantity;

	for (FProjectEXInventoryEntry& Entry : Entries)
	{
		if (Remaining <= 0)
		{
			break;
		}

		if (Entry.Definition != Definition || Entry.Quantity >= MaxStack)
		{
			continue;
		}

		const int32 AddedToStack = FMath::Min(MaxStack - Entry.Quantity, Remaining);
		Entry.Quantity += AddedToStack;
		Remaining -= AddedToStack;
	}

	while (Remaining > 0 && Entries.Num() < MaxSlots)
	{
		const int32 AddedToSlot = FMath::Min(MaxStack, Remaining);
		FProjectEXInventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
		NewEntry.EntryId = NextEntryId++;
		NewEntry.Definition = Definition;
		NewEntry.Quantity = AddedToSlot;
		Remaining -= AddedToSlot;
	}

	const int32 Added = Quantity - Remaining;
	if (Added > 0)
	{
		NotifyChanged();
	}

	return Added;
}

int32 UProjectEXInventoryComponent::RemoveItem(int32 EntryId, int32 Quantity)
{
	if (!HasInventoryAuthority() || Quantity <= 0)
	{
		return 0;
	}

	for (int32 Index = 0; Index < Entries.Num(); ++Index)
	{
		if (Entries[Index].EntryId != EntryId)
		{
			continue;
		}

		const int32 Removed = FMath::Min(Entries[Index].Quantity, Quantity);
		Entries[Index].Quantity -= Removed;
		if (Entries[Index].Quantity <= 0)
		{
			Entries.RemoveAt(Index);
		}

		if (Removed > 0)
		{
			NotifyChanged();
		}

		return Removed;
	}

	return 0;
}

void UProjectEXInventoryComponent::RequestDrop(int32 EntryId)
{
	if (HasInventoryAuthority())
	{
		DropItem(EntryId);
		return;
	}

	ServerDropItem(EntryId);
}

void UProjectEXInventoryComponent::ServerDropItem_Implementation(int32 EntryId)
{
	DropItem(EntryId);
}

void UProjectEXInventoryComponent::ToggleInventory()
{
	if (!IsLocalOwner())
	{
		return;
	}

	EnsureWidget();
	if (!InventoryWidget)
	{
		return;
	}

	bInventoryOpen = !bInventoryOpen;
	if (bInventoryOpen)
	{
		InventoryWidget->SetToggleKey(ToggleInventoryKey);
		InventoryWidget->BindInventory(this);
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		SetInventoryInputMode(true);
	}
	else
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
		SetInventoryInputMode(false);
	}
}

void UProjectEXInventoryComponent::OnRep_Entries()
{
	NotifyChanged();
}

bool UProjectEXInventoryComponent::HasInventoryAuthority() const
{
	const AActor* Owner = GetOwner();
	return Owner && Owner->HasAuthority();
}

void UProjectEXInventoryComponent::NotifyChanged()
{
	if (AActor* Owner = GetOwner())
	{
		if (Owner->HasAuthority())
		{
			Owner->ForceNetUpdate();
		}
	}

	OnInventoryChanged.Broadcast();
}

bool UProjectEXInventoryComponent::DropItem(int32 EntryId)
{
	if (!HasInventoryAuthority())
	{
		return false;
	}

	FProjectEXInventoryEntry* Entry = FindEntry(EntryId);
	UProjectEXItemDefinition* Definition = Entry ? Entry->Definition.Get() : nullptr;
	if (!Entry || Entry->Quantity <= 0 || !Definition)
	{
		return false;
	}

	UWorld* World = GetWorld();
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!World || !Pawn)
	{
		return false;
	}

	TSubclassOf<AProjectEXPickup> PickupClass = Definition->PickupClass;
	if (!PickupClass)
	{
		PickupClass = AProjectEXPickup::StaticClass();
	}

	const FTransform SpawnTransform = MakeDropTransform(Pawn);
	AProjectEXPickup* Pickup = World->SpawnActorDeferred<AProjectEXPickup>(
		PickupClass,
		SpawnTransform,
		nullptr,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

	if (!Pickup)
	{
		UE_LOG(LogProjectEX, Warning, TEXT("Drop failed for entry %d. The pickup could not be spawned, so the item stayed in inventory."), EntryId);
		return false;
	}

	Pickup->SetItemStack(Definition, 1);
	Pickup->FinishSpawning(SpawnTransform);

	if (!IsValid(Pickup))
	{
		UE_LOG(LogProjectEX, Warning, TEXT("Drop failed for entry %d. The spawned pickup was invalid, so the item stayed in inventory."), EntryId);
		return false;
	}

	Pickup->StartDropPhysics();

	const int32 Removed = RemoveItem(EntryId, 1);
	if (Removed != 1)
	{
		Pickup->Destroy();
		UE_LOG(LogProjectEX, Warning, TEXT("Drop failed for entry %d. The inventory remove was rejected and the spawned pickup was destroyed."), EntryId);
		return false;
	}

	return true;
}

FTransform UProjectEXInventoryComponent::MakeDropTransform(const APawn* Pawn) const
{
	FRotator FlatView = Pawn->GetControlRotation();
	FlatView.Pitch = 0.0f;
	FlatView.Roll = 0.0f;

	const FVector Forward = FlatView.Vector();
	float CapsuleRadius = 42.0f;
	if (const ACharacter* Character = Cast<ACharacter>(Pawn))
	{
		if (const UCapsuleComponent* Capsule = Character->GetCapsuleComponent())
		{
			CapsuleRadius = Capsule->GetScaledCapsuleRadius();
		}
	}

	const float ItemRadius = 30.0f;
	const float MinDistance = CapsuleRadius + ItemRadius + 10.0f;
	const float DesiredDistance = CapsuleRadius + ItemRadius + 50.0f;
	const FVector Start = Pawn->GetActorLocation();
	FVector Desired = Start + (Forward * DesiredDistance);

	FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(ProjectEXItemDrop), false, Pawn);
	FHitResult Hit;
	const FCollisionShape Shape = FCollisionShape::MakeSphere(ItemRadius);
	if (GetWorld()->SweepSingleByChannel(Hit, Start, Desired, FQuat::Identity, ECC_Visibility, Shape, QueryParams) && !Hit.bStartPenetrating)
	{
		Desired = Hit.Location;
	}

	if (FVector::DistSquared(Start, Desired) < FMath::Square(MinDistance))
	{
		Desired = Start + (Forward * MinDistance);
	}

	return FTransform(FlatView, Desired);
}

FProjectEXInventoryEntry* UProjectEXInventoryComponent::FindEntry(int32 EntryId)
{
	for (FProjectEXInventoryEntry& Entry : Entries)
	{
		if (Entry.EntryId == EntryId)
		{
			return &Entry;
		}
	}

	return nullptr;
}

void UProjectEXInventoryComponent::EnsureToggleAction()
{
	if (ToggleInventoryAction)
	{
		return;
	}

	ToggleInventoryAction = NewObject<UInputAction>(this, TEXT("IA_ToggleInventory"));
	ToggleInventoryAction->ValueType = EInputActionValueType::Boolean;

	ToggleMappingContext = NewObject<UInputMappingContext>(this, TEXT("IMC_Inventory"));
	ToggleMappingContext->MapKey(ToggleInventoryAction, ToggleInventoryKey);
}

void UProjectEXInventoryComponent::RegisterMappingContext(const APawn* Pawn)
{
	if (bRegisteredMappingContext || !ToggleMappingContext || !Pawn)
	{
		return;
	}

	const APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());
	if (!PlayerController || !PlayerController->IsLocalController())
	{
		return;
	}

	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	if (!LocalPlayer)
	{
		return;
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		Subsystem->AddMappingContext(ToggleMappingContext, 0);
		bRegisteredMappingContext = true;
	}
}

void UProjectEXInventoryComponent::EnsureWidget()
{
	if (InventoryWidget || !IsLocalOwner())
	{
		return;
	}

	APawn* Pawn = Cast<APawn>(GetOwner());
	APlayerController* PlayerController = Pawn ? Cast<APlayerController>(Pawn->GetController()) : nullptr;
	if (!PlayerController || !PlayerController->IsLocalController())
	{
		return;
	}

	TSubclassOf<UProjectEXInventoryWidget> ClassToSpawn = InventoryWidgetClass;
	if (!ClassToSpawn)
	{
		ClassToSpawn = UProjectEXInventoryWidget::StaticClass();
	}

	InventoryWidget = CreateWidget<UProjectEXInventoryWidget>(PlayerController, ClassToSpawn);
	if (!InventoryWidget)
	{
		return;
	}

	InventoryWidget->SetIsFocusable(false);
	InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	InventoryWidget->AddToViewport(20);
}

void UProjectEXInventoryComponent::SetInventoryInputMode(bool bOpen)
{
	APawn* Pawn = Cast<APawn>(GetOwner());
	APlayerController* PlayerController = Pawn ? Cast<APlayerController>(Pawn->GetController()) : nullptr;
	if (!PlayerController)
	{
		return;
	}

	if (bOpen)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetHideCursorDuringCapture(false);
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);
		PlayerController->SetShowMouseCursor(true);

		if (!bLookInputIgnored)
		{
			PlayerController->SetIgnoreLookInput(true);
			bLookInputIgnored = true;
		}
	}
	else
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);

		if (bLookInputIgnored)
		{
			PlayerController->SetIgnoreLookInput(false);
			bLookInputIgnored = false;
		}
	}
}

bool UProjectEXInventoryComponent::IsLocalOwner() const
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	return Pawn && Pawn->IsLocallyControlled();
}
