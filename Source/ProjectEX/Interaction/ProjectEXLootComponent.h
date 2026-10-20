// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectEXItemDefinition.h"
#include "ProjectEXLootComponent.generated.h"

class AProjectEXLootContainer;

/** Opens a loot container for the owning player and transfers stacks into the inventory. */
UCLASS(ClassGroup=(Interaction), meta=(BlueprintSpawnableComponent))
class PROJECTEX_API UProjectEXLootComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UProjectEXLootComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void OpenLoot(AProjectEXLootContainer* Container);
	void CloseLoot();
	void RequestClose();

	void RequestTake(int32 EntryId);
	void RequestTakeAt(int32 EntryId, int32 GridX, int32 GridY, bool bRotated);
	void RequestDeposit(int32 PlayerEntryId);
	void RequestDepositAt(int32 PlayerEntryId, int32 GridX, int32 GridY, bool bRotated);
	void RequestDepositEquippedAt(EProjectEXEquipmentSlot Slot, int32 GridX, int32 GridY, bool bRotated);
	void RequestMoveContainerItem(int32 EntryId, int32 GridX, int32 GridY, bool bRotated);
	void RequestEquipContainerItem(int32 EntryId, EProjectEXEquipmentSlot Slot);

	AProjectEXLootContainer* GetOpenContainer() const { return OpenContainer.Get(); }

	bool IsLootOpen() const { return bLootSessionOpen || OpenContainer.IsValid(); }

protected:

	UPROPERTY(Replicated)
	bool bLootSessionOpen = false;

	UFUNCTION(Client, Reliable)
	void ClientOpenLoot(AProjectEXLootContainer* Container);

	UFUNCTION(Client, Reliable)
	void ClientCloseLoot();

	UFUNCTION(Server, Reliable)
	void ServerCloseLoot();

	UFUNCTION(Server, Reliable)
	void ServerTakeContainerItem(AProjectEXLootContainer* Container, int32 EntryId);

	UFUNCTION(Server, Reliable)
	void ServerTakeContainerItemAt(AProjectEXLootContainer* Container, int32 EntryId, int32 GridX, int32 GridY, bool bRotated);

	UFUNCTION(Server, Reliable)
	void ServerDeposit(AProjectEXLootContainer* Container, int32 PlayerEntryId);

	UFUNCTION(Server, Reliable)
	void ServerDepositAt(AProjectEXLootContainer* Container, int32 PlayerEntryId, int32 GridX, int32 GridY, bool bRotated);

	UFUNCTION(Server, Reliable)
	void ServerDepositEquippedAt(AProjectEXLootContainer* Container, EProjectEXEquipmentSlot Slot, int32 GridX, int32 GridY, bool bRotated);

	UFUNCTION(Server, Reliable)
	void ServerMoveContainerItem(AProjectEXLootContainer* Container, int32 EntryId, int32 GridX, int32 GridY, bool bRotated);

	UFUNCTION(Server, Reliable)
	void ServerEquipContainerItem(AProjectEXLootContainer* Container, int32 EntryId, EProjectEXEquipmentSlot Slot);

private:

	bool IsLocalOwner() const;
	bool CanUseContainer(AProjectEXLootContainer* Container) const;

	TWeakObjectPtr<AProjectEXLootContainer> OpenContainer;
};
