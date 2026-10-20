// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXLootComponent.h"
#include "ProjectEXInventoryComponent.h"
#include "ProjectEXLootContainer.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"

UProjectEXLootComponent::UProjectEXLootComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UProjectEXLootComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UProjectEXLootComponent, bLootSessionOpen);
}

void UProjectEXLootComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CloseLoot();
	Super::EndPlay(EndPlayReason);
}

void UProjectEXLootComponent::OpenLoot(AProjectEXLootContainer* Container)
{
	AActor* Owner = GetOwner();
	if (!Owner || !Owner->HasAuthority() || !Container)
	{
		return;
	}

	bLootSessionOpen = true;
	Owner->ForceNetUpdate();
	ClientOpenLoot(Container);
}

void UProjectEXLootComponent::CloseLoot()
{
	if (AActor* Owner = GetOwner(); Owner && Owner->HasAuthority() && bLootSessionOpen)
	{
		bLootSessionOpen = false;
		Owner->ForceNetUpdate();
		ClientCloseLoot();
	}

	RequestClose();
}

void UProjectEXLootComponent::RequestClose()
{
	bLootSessionOpen = false;
	ServerCloseLoot();
	OpenContainer = nullptr;

	if (UProjectEXInventoryComponent* Inventory = GetOwner() ? GetOwner()->FindComponentByClass<UProjectEXInventoryComponent>() : nullptr)
	{
		Inventory->ClearSearchedContainer();
	}

	if (!IsLocalOwner())
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Cast<APawn>(GetOwner())->GetController()))
	{
		const UProjectEXInventoryComponent* Inventory = GetOwner()->FindComponentByClass<UProjectEXInventoryComponent>();
		if (!Inventory || !Inventory->IsInventoryOpen())
		{
			PlayerController->SetIgnoreLookInput(false);
			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			PlayerController->SetShowMouseCursor(false);
		}
	}
}

void UProjectEXLootComponent::ClientOpenLoot_Implementation(AProjectEXLootContainer* Container)
{
	if (!IsLocalOwner() || !Container)
	{
		return;
	}

	APlayerController* PlayerController = Cast<APlayerController>(Cast<APawn>(GetOwner())->GetController());
	if (!PlayerController)
	{
		return;
	}

	OpenContainer = Container;

	if (UProjectEXInventoryComponent* Inventory = GetOwner()->FindComponentByClass<UProjectEXInventoryComponent>())
	{
		Inventory->ShowSearchedContainer(Container);
	}

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	PlayerController->SetInputMode(InputMode);
	PlayerController->SetShowMouseCursor(true);
	PlayerController->SetIgnoreLookInput(true);
}

void UProjectEXLootComponent::ClientCloseLoot_Implementation()
{
	OpenContainer = nullptr;
	if (UProjectEXInventoryComponent* Inventory = GetOwner() ? GetOwner()->FindComponentByClass<UProjectEXInventoryComponent>() : nullptr)
	{
		Inventory->ClearSearchedContainer();
	}

	if (!IsLocalOwner())
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Cast<APawn>(GetOwner())->GetController()))
	{
		const UProjectEXInventoryComponent* Inventory = GetOwner()->FindComponentByClass<UProjectEXInventoryComponent>();
		if (!Inventory || !Inventory->IsInventoryOpen())
		{
			PlayerController->SetIgnoreLookInput(false);
			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			PlayerController->SetShowMouseCursor(false);
		}
	}
}

void UProjectEXLootComponent::ServerCloseLoot_Implementation()
{
	if (AActor* Owner = GetOwner(); Owner && Owner->HasAuthority())
	{
		bLootSessionOpen = false;
		Owner->ForceNetUpdate();
	}
}

void UProjectEXLootComponent::ServerTakeContainerItem_Implementation(AProjectEXLootContainer* Container, int32 EntryId)
{
	if (CanUseContainer(Container))
	{
		Container->TryTakeEntry(Cast<APawn>(GetOwner()), EntryId);
	}
}

void UProjectEXLootComponent::RequestTake(int32 EntryId)
{
	if (AProjectEXLootContainer* Container = OpenContainer.Get())
	{
		ServerTakeContainerItem(Container, EntryId);
	}
}

void UProjectEXLootComponent::RequestTakeAt(int32 EntryId, int32 GridX, int32 GridY, bool bRotated)
{
	if (AProjectEXLootContainer* Container = OpenContainer.Get())
	{
		ServerTakeContainerItemAt(Container, EntryId, GridX, GridY, bRotated);
	}
}

void UProjectEXLootComponent::RequestDeposit(int32 PlayerEntryId)
{
	if (AProjectEXLootContainer* Container = OpenContainer.Get())
	{
		ServerDeposit(Container, PlayerEntryId);
	}
}

void UProjectEXLootComponent::RequestDepositAt(int32 PlayerEntryId, int32 GridX, int32 GridY, bool bRotated)
{
	if (AProjectEXLootContainer* Container = OpenContainer.Get())
	{
		ServerDepositAt(Container, PlayerEntryId, GridX, GridY, bRotated);
	}
}

void UProjectEXLootComponent::RequestDepositEquippedAt(EProjectEXEquipmentSlot Slot, int32 GridX, int32 GridY, bool bRotated)
{
	if (AProjectEXLootContainer* Container = OpenContainer.Get())
	{
		ServerDepositEquippedAt(Container, Slot, GridX, GridY, bRotated);
	}
}

void UProjectEXLootComponent::RequestMoveContainerItem(int32 EntryId, int32 GridX, int32 GridY, bool bRotated)
{
	if (AProjectEXLootContainer* Container = OpenContainer.Get())
	{
		ServerMoveContainerItem(Container, EntryId, GridX, GridY, bRotated);
	}
}

void UProjectEXLootComponent::RequestEquipContainerItem(int32 EntryId, EProjectEXEquipmentSlot Slot)
{
	if (AProjectEXLootContainer* Container = OpenContainer.Get())
	{
		ServerEquipContainerItem(Container, EntryId, Slot);
	}
}

void UProjectEXLootComponent::ServerTakeContainerItemAt_Implementation(AProjectEXLootContainer* Container, int32 EntryId, int32 GridX, int32 GridY, bool bRotated)
{
	if (CanUseContainer(Container))
	{
		Container->TryTakeEntryAt(Cast<APawn>(GetOwner()), EntryId, GridX, GridY, bRotated);
	}
}

void UProjectEXLootComponent::ServerDeposit_Implementation(AProjectEXLootContainer* Container, int32 PlayerEntryId)
{
	if (CanUseContainer(Container))
	{
		Container->TryDeposit(Cast<APawn>(GetOwner()), PlayerEntryId);
	}
}

void UProjectEXLootComponent::ServerDepositAt_Implementation(AProjectEXLootContainer* Container, int32 PlayerEntryId, int32 GridX, int32 GridY, bool bRotated)
{
	if (CanUseContainer(Container))
	{
		Container->TryDepositAt(Cast<APawn>(GetOwner()), PlayerEntryId, GridX, GridY, bRotated);
	}
}

void UProjectEXLootComponent::ServerDepositEquippedAt_Implementation(AProjectEXLootContainer* Container, EProjectEXEquipmentSlot Slot, int32 GridX, int32 GridY, bool bRotated)
{
	if (CanUseContainer(Container))
	{
		Container->TryDepositEquippedAt(Cast<APawn>(GetOwner()), Slot, GridX, GridY, bRotated);
	}
}

void UProjectEXLootComponent::ServerMoveContainerItem_Implementation(AProjectEXLootContainer* Container, int32 EntryId, int32 GridX, int32 GridY, bool bRotated)
{
	if (CanUseContainer(Container))
	{
		Container->TryMoveEntry(EntryId, GridX, GridY, bRotated);
	}
}

void UProjectEXLootComponent::ServerEquipContainerItem_Implementation(AProjectEXLootContainer* Container, int32 EntryId, EProjectEXEquipmentSlot Slot)
{
	if (CanUseContainer(Container))
	{
		Container->TryEquipEntry(Cast<APawn>(GetOwner()), EntryId, Slot);
	}
}

bool UProjectEXLootComponent::CanUseContainer(AProjectEXLootContainer* Container) const
{
	return Container && bLootSessionOpen;
}

bool UProjectEXLootComponent::IsLocalOwner() const
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	return Pawn && Pawn->IsLocallyControlled();
}
