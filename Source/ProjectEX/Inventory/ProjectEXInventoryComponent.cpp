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

namespace
{
	bool RectsOverlap(int32 AX, int32 AY, int32 AWidth, int32 AHeight, int32 BX, int32 BY, int32 BWidth, int32 BHeight)
	{
		return AX < BX + BWidth && AX + AWidth > BX && AY < BY + BHeight && AY + AHeight > BY;
	}
}

UProjectEXInventoryComponent::UProjectEXInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	ToggleInventoryKey = EKeys::Tab;
	RotateItemKey = EKeys::R;
}

void UProjectEXInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UProjectEXInventoryComponent, Entries, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UProjectEXInventoryComponent, GridColumns, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UProjectEXInventoryComponent, GridRows, COND_OwnerOnly);
}

void UProjectEXInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (InventoryWidget)
	{
		InventoryWidget->CancelDrag();
	}

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

	EnsureInputActions();
	RegisterMappingContext(Pawn);

	if (ToggleInventoryAction)
	{
		EnhancedInput->BindAction(ToggleInventoryAction, ETriggerEvent::Started, this, &UProjectEXInventoryComponent::ToggleInventory);
	}

	if (RotateItemAction)
	{
		EnhancedInput->BindAction(RotateItemAction, ETriggerEvent::Started, this, &UProjectEXInventoryComponent::HandleRotateItem);
	}
}

int32 UProjectEXInventoryComponent::AddItem(UProjectEXItemDefinition* Definition, int32 Quantity)
{
	if (!HasInventoryAuthority() || !Definition || Quantity <= 0)
	{
		return 0;
	}

	const int32 Columns = GetGridColumns();
	const int32 Rows = GetGridRows();
	const int32 MaxStack = FMath::Max(1, Definition->MaxStackSize);
	int32 Remaining = Quantity;

	struct FStackPlan
	{
		int32 EntryId = INDEX_NONE;
		int32 Amount = 0;
	};

	TArray<FStackPlan> StackPlans;
	for (const FProjectEXInventoryEntry& Entry : Entries)
	{
		if (Remaining <= 0)
		{
			break;
		}

		if (Entry.Definition != Definition || Entry.Quantity >= MaxStack)
		{
			continue;
		}

		const int32 Amount = FMath::Min(MaxStack - Entry.Quantity, Remaining);
		FStackPlan& Plan = StackPlans.AddDefaulted_GetRef();
		Plan.EntryId = Entry.EntryId;
		Plan.Amount = Amount;
		Remaining -= Amount;
	}

	TArray<uint8> Occupied;
	Occupied.SetNumZeroed(Columns * Rows);
	for (const FProjectEXInventoryEntry& Entry : Entries)
	{
		if (!Entry.Definition || Entry.Quantity <= 0)
		{
			continue;
		}

		const FIntPoint Size = Entry.Definition->GetGridSize(Entry.bRotated);
		MarkOccupied(Occupied, Entry.GridX, Entry.GridY, Size.X, Size.Y);
	}

	struct FNewPlan
	{
		int32 X = 0;
		int32 Y = 0;
		bool bRotated = false;
		int32 Quantity = 0;
	};

	TArray<FNewPlan> NewPlans;
	while (Remaining > 0)
	{
		int32 X = 0;
		int32 Y = 0;
		bool bRotated = false;
		if (!FindFreePosition(Occupied, Definition, X, Y, bRotated))
		{
			return 0;
		}

		const FIntPoint Size = Definition->GetGridSize(bRotated);
		const int32 Chunk = FMath::Min(MaxStack, Remaining);
		FNewPlan& Plan = NewPlans.AddDefaulted_GetRef();
		Plan.X = X;
		Plan.Y = Y;
		Plan.bRotated = bRotated;
		Plan.Quantity = Chunk;
		MarkOccupied(Occupied, X, Y, Size.X, Size.Y);
		Remaining -= Chunk;
	}

	for (const FNewPlan& Plan : NewPlans)
	{
		FProjectEXInventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
		NewEntry.EntryId = NextEntryId++;
		NewEntry.Definition = Definition;
		NewEntry.Quantity = Plan.Quantity;
		NewEntry.GridX = Plan.X;
		NewEntry.GridY = Plan.Y;
		NewEntry.bRotated = Plan.bRotated;
	}

	for (const FStackPlan& Plan : StackPlans)
	{
		if (FProjectEXInventoryEntry* Entry = FindEntry(Plan.EntryId))
		{
			Entry->Quantity += Plan.Amount;
		}
	}

	NotifyChanged();
	return Quantity;
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

void UProjectEXInventoryComponent::RequestMoveItem(int32 EntryId, int32 GridX, int32 GridY, bool bRotated)
{
	if (HasInventoryAuthority())
	{
		MoveItem(EntryId, GridX, GridY, bRotated);
		return;
	}

	ServerMoveItem(EntryId, GridX, GridY, bRotated);
}

void UProjectEXInventoryComponent::ServerMoveItem_Implementation(int32 EntryId, int32 GridX, int32 GridY, bool bRotated)
{
	MoveItem(EntryId, GridX, GridY, bRotated);
}

void UProjectEXInventoryComponent::RequestDrop(int32 EntryId)
{
	if (HasInventoryAuthority())
	{
		DropItem(EntryId, 1);
		return;
	}

	ServerDropItem(EntryId);
}

void UProjectEXInventoryComponent::ServerDropItem_Implementation(int32 EntryId)
{
	DropItem(EntryId, 1);
}

void UProjectEXInventoryComponent::RequestDropStack(int32 EntryId)
{
	if (HasInventoryAuthority())
	{
		if (const FProjectEXInventoryEntry* Entry = FindEntry(EntryId))
		{
			DropItem(EntryId, Entry->Quantity);
		}
		return;
	}

	ServerDropStack(EntryId);
}

void UProjectEXInventoryComponent::ServerDropStack_Implementation(int32 EntryId)
{
	if (const FProjectEXInventoryEntry* Entry = FindEntry(EntryId))
	{
		DropItem(EntryId, Entry->Quantity);
	}
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
		InventoryWidget->SetInputHints(ToggleInventoryKey, RotateItemKey);
		InventoryWidget->BindInventory(this);
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		SetInventoryInputMode(true);
	}
	else
	{
		InventoryWidget->CancelDrag();
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
		SetInventoryInputMode(false);
	}
}

bool UProjectEXInventoryComponent::CanPlaceEntry(int32 EntryId, int32 GridX, int32 GridY, bool bRotated) const
{
	int32 MergeEntryId = INDEX_NONE;
	return QueryPlacement(EntryId, GridX, GridY, bRotated, MergeEntryId);
}

int32 UProjectEXInventoryComponent::GetOccupiedCellCount() const
{
	int32 Count = 0;
	for (const FProjectEXInventoryEntry& Entry : Entries)
	{
		if (!Entry.Definition || Entry.Quantity <= 0)
		{
			continue;
		}

		const FIntPoint Size = Entry.Definition->GetGridSize(Entry.bRotated);
		Count += Size.X * Size.Y;
	}

	return Count;
}

void UProjectEXInventoryComponent::OnRep_Entries()
{
	NotifyChanged();
}

void UProjectEXInventoryComponent::OnRep_GridLayout()
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

bool UProjectEXInventoryComponent::MoveItem(int32 EntryId, int32 GridX, int32 GridY, bool bRotated)
{
	if (!HasInventoryAuthority())
	{
		return false;
	}

	FProjectEXInventoryEntry* Source = FindEntry(EntryId);
	if (!Source || !Source->Definition || Source->Quantity <= 0)
	{
		return false;
	}

	int32 MergeEntryId = INDEX_NONE;
	if (!QueryPlacement(EntryId, GridX, GridY, bRotated, MergeEntryId))
	{
		return false;
	}

	if (MergeEntryId != INDEX_NONE)
	{
		FProjectEXInventoryEntry* Destination = FindEntry(MergeEntryId);
		if (!Destination || !Destination->Definition)
		{
			return false;
		}

		const int32 MaxStack = FMath::Max(1, Destination->Definition->MaxStackSize);
		const int32 Transfer = FMath::Min(FMath::Max(0, MaxStack - Destination->Quantity), Source->Quantity);
		if (Transfer <= 0)
		{
			return false;
		}

		Destination->Quantity += Transfer;
		Source->Quantity -= Transfer;
		if (Source->Quantity <= 0)
		{
			for (int32 Index = 0; Index < Entries.Num(); ++Index)
			{
				if (Entries[Index].EntryId == EntryId)
				{
					Entries.RemoveAt(Index);
					break;
				}
			}
		}

		NotifyChanged();
		return true;
	}

	if (Source->GridX == GridX && Source->GridY == GridY && Source->bRotated == bRotated)
	{
		return true;
	}

	Source->GridX = GridX;
	Source->GridY = GridY;
	Source->bRotated = bRotated;
	NotifyChanged();
	return true;
}

bool UProjectEXInventoryComponent::DropItem(int32 EntryId, int32 Quantity)
{
	if (!HasInventoryAuthority() || Quantity <= 0)
	{
		return false;
	}

	FProjectEXInventoryEntry* Entry = FindEntry(EntryId);
	UProjectEXItemDefinition* Definition = Entry ? Entry->Definition.Get() : nullptr;
	if (!Entry || Entry->Quantity <= 0 || !Definition)
	{
		return false;
	}

	const int32 DropQuantity = FMath::Min(Quantity, Entry->Quantity);

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

	Pickup->SetItemStack(Definition, DropQuantity);
	Pickup->FinishSpawning(SpawnTransform);

	if (!IsValid(Pickup))
	{
		UE_LOG(LogProjectEX, Warning, TEXT("Drop failed for entry %d. The spawned pickup was invalid, so the item stayed in inventory."), EntryId);
		return false;
	}

	Pickup->StartDropPhysics();

	const int32 Removed = RemoveItem(EntryId, DropQuantity);
	if (Removed != DropQuantity)
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

const FProjectEXInventoryEntry* UProjectEXInventoryComponent::FindEntry(int32 EntryId) const
{
	for (const FProjectEXInventoryEntry& Entry : Entries)
	{
		if (Entry.EntryId == EntryId)
		{
			return &Entry;
		}
	}

	return nullptr;
}

bool UProjectEXInventoryComponent::QueryPlacement(int32 EntryId, int32 GridX, int32 GridY, bool bRotated, int32& OutMergeEntryId) const
{
	OutMergeEntryId = INDEX_NONE;

	const FProjectEXInventoryEntry* Source = FindEntry(EntryId);
	if (!Source || !Source->Definition || Source->Quantity <= 0)
	{
		return false;
	}

	const FIntPoint Size = Source->Definition->GetGridSize(bRotated);
	if (GridX < 0 || GridY < 0 || GridX + Size.X > GetGridColumns() || GridY + Size.Y > GetGridRows())
	{
		return false;
	}

	const FProjectEXInventoryEntry* MergeTarget = nullptr;
	for (const FProjectEXInventoryEntry& Other : Entries)
	{
		if (Other.EntryId == EntryId || !Other.Definition || Other.Quantity <= 0)
		{
			continue;
		}

		const FIntPoint OtherSize = Other.Definition->GetGridSize(Other.bRotated);
		if (!RectsOverlap(GridX, GridY, Size.X, Size.Y, Other.GridX, Other.GridY, OtherSize.X, OtherSize.Y))
		{
			continue;
		}

		const int32 MaxStack = FMath::Max(1, Other.Definition->MaxStackSize);
		if (MergeTarget || Other.Definition != Source->Definition || Other.Quantity >= MaxStack)
		{
			return false;
		}

		MergeTarget = &Other;
	}

	if (MergeTarget)
	{
		OutMergeEntryId = MergeTarget->EntryId;
	}

	return true;
}

bool UProjectEXInventoryComponent::FindFreePosition(const TArray<uint8>& Occupied, const UProjectEXItemDefinition* Definition, int32& OutX, int32& OutY, bool& bOutRotated) const
{
	if (!Definition)
	{
		return false;
	}

	const int32 Columns = GetGridColumns();
	const int32 Rows = GetGridRows();
	const FIntPoint Upright = Definition->GetGridSize(false);
	const FIntPoint Turned = Definition->GetGridSize(true);

	auto Search = [&](const FIntPoint& Size, bool bRotated) -> bool
	{
		for (int32 Y = 0; Y <= Rows - Size.Y; ++Y)
		{
			for (int32 X = 0; X <= Columns - Size.X; ++X)
			{
				if (RectIsFree(Occupied, X, Y, Size.X, Size.Y))
				{
					OutX = X;
					OutY = Y;
					bOutRotated = bRotated;
					return true;
				}
			}
		}

		return false;
	};

	if (Search(Upright, false))
	{
		return true;
	}

	return Turned != Upright && Search(Turned, true);
}

void UProjectEXInventoryComponent::MarkOccupied(TArray<uint8>& Occupied, int32 X, int32 Y, int32 Width, int32 Height) const
{
	const int32 Columns = GetGridColumns();
	const int32 Rows = GetGridRows();
	for (int32 DY = 0; DY < Height; ++DY)
	{
		for (int32 DX = 0; DX < Width; ++DX)
		{
			const int32 CellX = X + DX;
			const int32 CellY = Y + DY;
			if (CellX < 0 || CellY < 0 || CellX >= Columns || CellY >= Rows)
			{
				continue;
			}

			Occupied[CellY * Columns + CellX] = 1;
		}
	}
}

bool UProjectEXInventoryComponent::RectIsFree(const TArray<uint8>& Occupied, int32 X, int32 Y, int32 Width, int32 Height) const
{
	const int32 Columns = GetGridColumns();
	const int32 Rows = GetGridRows();
	if (X < 0 || Y < 0 || Width <= 0 || Height <= 0 || X + Width > Columns || Y + Height > Rows)
	{
		return false;
	}

	for (int32 DY = 0; DY < Height; ++DY)
	{
		for (int32 DX = 0; DX < Width; ++DX)
		{
			if (Occupied[(Y + DY) * Columns + (X + DX)] != 0)
			{
				return false;
			}
		}
	}

	return true;
}

void UProjectEXInventoryComponent::HandleRotateItem()
{
	if (!bInventoryOpen || !IsLocalOwner() || !InventoryWidget)
	{
		return;
	}

	InventoryWidget->RotateDraggedItem();
}

void UProjectEXInventoryComponent::EnsureInputActions()
{
	if (!InventoryMappingContext)
	{
		InventoryMappingContext = NewObject<UInputMappingContext>(this, TEXT("IMC_Inventory"));
	}

	if (!ToggleInventoryAction)
	{
		ToggleInventoryAction = NewObject<UInputAction>(this, TEXT("IA_ToggleInventory"));
		ToggleInventoryAction->ValueType = EInputActionValueType::Boolean;
		InventoryMappingContext->MapKey(ToggleInventoryAction, ToggleInventoryKey);
	}

	if (!RotateItemAction)
	{
		RotateItemAction = NewObject<UInputAction>(this, TEXT("IA_RotateItem"));
		RotateItemAction->ValueType = EInputActionValueType::Boolean;
		InventoryMappingContext->MapKey(RotateItemAction, RotateItemKey);
	}
}

void UProjectEXInventoryComponent::RegisterMappingContext(const APawn* Pawn)
{
	if (bRegisteredMappingContext || !InventoryMappingContext || !Pawn)
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
		Subsystem->AddMappingContext(InventoryMappingContext, 0);
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
