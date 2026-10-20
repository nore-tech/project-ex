// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectEXInteractable.h"
#include "ProjectEXInventoryTypes.h"
#include "ProjectEXLootContainer.generated.h"

class UStaticMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FProjectEXContainerChanged);

/** Searchable container with a grid smaller than the player inventory. */
UCLASS()
class PROJECTEX_API AProjectEXLootContainer : public AActor, public IProjectEXInteractable
{
	GENERATED_BODY()

public:

	AProjectEXLootContainer();

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual FText GetInteractionPrompt_Implementation() const override;
	virtual bool CanInteract_Implementation(APawn* Interactor) const override;
	virtual void Interact_Implementation(APawn* Interactor) override;

	const TArray<FProjectEXInventoryEntry>& GetEntries() const { return Contents; }
	int32 GetGridColumns() const { return FMath::Max(1, GridColumns); }
	int32 GetGridRows() const { return FMath::Max(1, GridRows); }

	/**
	 *  Server only, including an actor that has not begun play yet.
	 *  Places the full quantity into the grid, or changes nothing.
	 */
	int32 AddItem(UProjectEXItemDefinition* Definition, int32 Quantity, int32 MagazineRounds = -1);

	/** Server only. Moves one grid entry into the first free player cells. Does not equip it. */
	bool TryTakeEntry(APawn* Pawn, int32 EntryId);

	/** Server only. Moves one grid entry onto a player cell. Rejected when that cell cannot hold it. */
	bool TryTakeEntryAt(APawn* Pawn, int32 EntryId, int32 GridX, int32 GridY, bool bRotated);

	/** Server only. Moves one player stack into the first free container cells. */
	bool TryDeposit(APawn* Pawn, int32 PlayerEntryId);

	/** Server only. Moves one player stack onto a container cell. */
	bool TryDepositAt(APawn* Pawn, int32 PlayerEntryId, int32 GridX, int32 GridY, bool bRotated);

	/** Server only. Moves a worn item onto a container cell and clears that equipment slot. */
	bool TryDepositEquippedAt(APawn* Pawn, EProjectEXEquipmentSlot Slot, int32 GridX, int32 GridY, bool bRotated);

	/** Server only. Moves one container entry to another cell in this grid. */
	bool TryMoveEntry(int32 EntryId, int32 GridX, int32 GridY, bool bRotated);

	/** Server only. Equips a container entry into an empty compatible slot. */
	bool TryEquipEntry(APawn* Pawn, int32 EntryId, EProjectEXEquipmentSlot Slot);

	bool CanPlaceItem(const UProjectEXItemDefinition* Definition, int32 Quantity, int32 MagazineRounds, int32 GridX, int32 GridY, bool bRotated, int32 IgnoreEntryId = INDEX_NONE) const;

	FText GetContainerName() const;

	UPROPERTY(BlueprintAssignable, Category="Loot")
	FProjectEXContainerChanged OnContentsChanged;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category="Loot")
	FText ContainerName;

	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, Replicated, Category="Loot", meta=(ClampMin="1"))
	int32 GridColumns = 6;

	UPROPERTY(EditAnywhere, Replicated, Category="Loot", meta=(ClampMin="1"))
	int32 GridRows = 4;

	UPROPERTY(ReplicatedUsing=OnRep_Contents)
	TArray<FProjectEXInventoryEntry> Contents;

	UFUNCTION()
	void OnRep_Contents();

private:

	void NotifyContentsChanged();
	bool IsPawnInRange(const APawn* Pawn) const;
	bool ExtractEntry(int32 EntryId, FProjectEXInventoryEntry& OutEntry);
	bool InsertEntryAt(const FProjectEXInventoryEntry& Entry, int32 GridX, int32 GridY, bool bRotated);

	int32 NextEntryId = 1;
};
