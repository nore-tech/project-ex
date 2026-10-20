// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputCoreTypes.h"
#include "ProjectEXInventoryTypes.h"
#include "ProjectEXInventoryWidget.h"
#include "ProjectEXInventoryComponent.generated.h"

class APawn;
class AProjectEXPickup;
class UEnhancedInputComponent;
class UInputAction;
class UInputMappingContext;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FProjectEXInventoryChanged);

/**
 *  Per-player grid inventory. The server mutates entries, and they replicate only to the owning player.
 *  Grid coordinates are validated here. The UI sends requests and does not change entries itself.
 */
UCLASS(ClassGroup=(Inventory), meta=(BlueprintSpawnableComponent))
class PROJECTEX_API UProjectEXInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UProjectEXInventoryComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Binds inventory toggle and drag rotation. Missing actions get a runtime mapping. */
	void BindInput(UEnhancedInputComponent* EnhancedInput);

	/**
	 *  Adds the full quantity, stacking first and then finding free rectangles.
	 *  Server only. Returns Quantity when the whole amount fits, otherwise 0 and the inventory is unchanged.
	 *  MagazineRounds is stored on each new entry. Pass -1 for ordinary stacks.
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	int32 AddItem(UProjectEXItemDefinition* Definition, int32 Quantity, int32 MagazineRounds = -1);

	/** Server only. Sets the loaded rounds stored on one entry. */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool SetEntryMagazine(int32 EntryId, int32 MagazineRounds);

	UFUNCTION(BlueprintPure, Category="Inventory")
	int32 GetEntryMagazine(int32 EntryId) const;

	UFUNCTION(BlueprintPure, Category="Inventory")
	int32 CountItem(const UProjectEXItemDefinition* Definition) const;

	/** Server only. Removes this item type across stacks. Returns the amount actually removed. */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	int32 ConsumeItem(UProjectEXItemDefinition* Definition, int32 Quantity);

	/** Removes up to Quantity from one entry. Server only. Returns the amount removed. */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	int32 RemoveItem(int32 EntryId, int32 Quantity);

	/** Asks the server to move or rotate an entry, or merge it into one compatible stack it overlaps. */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RequestMoveItem(int32 EntryId, int32 GridX, int32 GridY, bool bRotated);

	/** Asks the server to drop one unit from an entry. */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RequestDrop(int32 EntryId);

	/** Asks the server to drop every unit in an entry as one world pickup. */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RequestDropStack(int32 EntryId);

	/** Moves one grid entry into an empty compatible equipment slot. Server-authoritative. */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RequestEquip(int32 EntryId, EProjectEXEquipmentSlot Slot);

	/** Ctrl-click. Equips into an empty compatible slot. Does nothing when that slot is already worn. */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RequestAutoEquip(int32 EntryId);

	/** Server only. Places a stack on the grid, or merges it into one compatible stack. Rejects a partial fit. */
	bool InsertItemAt(UProjectEXItemDefinition* Definition, int32 Quantity, int32 MagazineRounds, int32 GridX, int32 GridY, bool bRotated);

	/** Asks the server to move a worn item onto a pockets cell. Rejected when that cell is not free. */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RequestUnequipAt(EProjectEXEquipmentSlot Slot, int32 GridX, int32 GridY, bool bRotated);

	/** Asks the server to move a worn item into another empty compatible slot. */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RequestMoveEquipped(EProjectEXEquipmentSlot FromSlot, EProjectEXEquipmentSlot ToSlot);

	/** Server only. Removes a worn item and leaves the slot empty. */
	bool TakeEquippedItem(EProjectEXEquipmentSlot Slot, FProjectEXEquippedItem& OutItem);

	/** Server only. Fills an empty compatible slot. */
	bool ReceiveEquippedItem(EProjectEXEquipmentSlot Slot, UProjectEXItemDefinition* Definition, int32 Quantity, int32 MagazineRounds);

	/** Read-only. True when a new stack can occupy this cell or merge into one compatible stack. */
	UFUNCTION(BlueprintPure, Category="Inventory")
	bool CanAcceptItem(const UProjectEXItemDefinition* Definition, int32 Quantity, int32 MagazineRounds, int32 GridX, int32 GridY, bool bRotated) const;

	void ShowSearchedContainer(class AProjectEXLootContainer* Container);
	void ClearSearchedContainer();

	/** Server only. Equips the newest stack of an equippable definition. */
	bool AutoEquipNewest(const UProjectEXItemDefinition* Definition);

	/** Opens the inventory on the local owner without closing it when it is already open. */
	void ShowInventory();

	/** Returns a worn item to the grid. Rejected when the grid cannot hold it. */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RequestUnequip(EProjectEXEquipmentSlot Slot);

	/** Uses one medical item from the grid. Rejected at full health. */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RequestUseItem(int32 EntryId);

	UFUNCTION(BlueprintPure, Category="Inventory")
	bool GetEquippedItem(EProjectEXEquipmentSlot Slot, FProjectEXEquippedItem& OutItem) const;

	/** Server only. Writes the loaded rounds stored on a worn weapon. */
	bool SetEquippedMagazine(EProjectEXEquipmentSlot Slot, int32 MagazineRounds);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void ToggleInventory();

	/** True when the entry can move, rotate, or merge at this cell. Ignores the entry's own cells. */
	UFUNCTION(BlueprintPure, Category="Inventory")
	bool CanPlaceEntry(int32 EntryId, int32 GridX, int32 GridY, bool bRotated) const;

	static bool SlotAcceptsItem(EProjectEXEquipmentSlot Slot, const UProjectEXItemDefinition* Definition);

	UFUNCTION(BlueprintPure, Category="Inventory")
	TArray<FProjectEXInventoryEntry> GetEntries() const { return Entries; }

	UFUNCTION(BlueprintPure, Category="Inventory")
	int32 GetGridColumns() const { return FMath::Max(1, GridColumns); }

	UFUNCTION(BlueprintPure, Category="Inventory")
	int32 GetGridRows() const { return FMath::Max(1, GridRows); }

	UFUNCTION(BlueprintPure, Category="Inventory")
	int32 GetOccupiedCellCount() const;

	UFUNCTION(BlueprintPure, Category="Inventory")
	int32 GetGridCellCount() const { return GetGridColumns() * GetGridRows(); }

	UFUNCTION(BlueprintPure, Category="Inventory")
	bool IsInventoryOpen() const { return bInventoryOpen; }

	FKey GetToggleInventoryKey() const { return ToggleInventoryKey; }
	FKey GetRotateItemKey() const { return RotateItemKey; }

	UPROPERTY(BlueprintAssignable, Category="Inventory")
	FProjectEXInventoryChanged OnInventoryChanged;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_GridLayout, Category="Inventory", meta=(ClampMin="1"))
	int32 GridColumns = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_GridLayout, Category="Inventory", meta=(ClampMin="1"))
	int32 GridRows = 6;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ToggleInventoryAction;

	UPROPERTY(EditAnywhere, Category="Input")
	FKey ToggleInventoryKey;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> RotateItemAction;

	UPROPERTY(EditAnywhere, Category="Input")
	FKey RotateItemKey;

	UPROPERTY(EditAnywhere, Category="Inventory")
	TSubclassOf<UProjectEXInventoryWidget> InventoryWidgetClass;

	UFUNCTION()
	void OnRep_Entries();

	UFUNCTION()
	void OnRep_Equipment();

	UFUNCTION()
	void OnRep_GridLayout();

	UFUNCTION(Server, Reliable)
	void ServerMoveItem(int32 EntryId, int32 GridX, int32 GridY, bool bRotated);

	UFUNCTION(Server, Reliable)
	void ServerDropItem(int32 EntryId);

	UFUNCTION(Server, Reliable)
	void ServerDropStack(int32 EntryId);

	UFUNCTION(Server, Reliable)
	void ServerEquip(int32 EntryId, EProjectEXEquipmentSlot Slot);

	UFUNCTION(Server, Reliable)
	void ServerAutoEquip(int32 EntryId);

	UFUNCTION(Server, Reliable)
	void ServerUnequipAt(EProjectEXEquipmentSlot Slot, int32 GridX, int32 GridY, bool bRotated);

	UFUNCTION(Server, Reliable)
	void ServerMoveEquipped(EProjectEXEquipmentSlot FromSlot, EProjectEXEquipmentSlot ToSlot);

	UFUNCTION(Server, Reliable)
	void ServerUnequip(EProjectEXEquipmentSlot Slot);

	UFUNCTION(Server, Reliable)
	void ServerUseItem(int32 EntryId);

private:

	bool HasInventoryAuthority() const;
	void NotifyChanged();
	bool MoveItem(int32 EntryId, int32 GridX, int32 GridY, bool bRotated);
	bool DropItem(int32 EntryId, int32 Quantity);
	bool EquipItem(int32 EntryId, EProjectEXEquipmentSlot Slot);
	bool AutoEquip(int32 EntryId);
	bool UnequipAt(EProjectEXEquipmentSlot Slot, int32 GridX, int32 GridY, bool bRotated);
	bool MoveEquipped(EProjectEXEquipmentSlot FromSlot, EProjectEXEquipmentSlot ToSlot);
	bool UnequipItem(EProjectEXEquipmentSlot Slot);
	bool UseItem(int32 EntryId);
	int32 FindNewestEntryId(const UProjectEXItemDefinition* Definition) const;
	bool TakeEntry(int32 EntryId, FProjectEXInventoryEntry& OutEntry);
	FProjectEXEquippedItem* FindEquipmentSlot(EProjectEXEquipmentSlot Slot);
	const FProjectEXEquippedItem* FindEquipmentSlot(EProjectEXEquipmentSlot Slot) const;
	FTransform MakeDropTransform(const APawn* Pawn) const;
	FProjectEXInventoryEntry* FindEntry(int32 EntryId);
	const FProjectEXInventoryEntry* FindEntry(int32 EntryId) const;

	/** False when the rectangle is rejected. OutMergeEntryId is set when the placement merges into one stack. */
	bool QueryPlacement(int32 EntryId, int32 GridX, int32 GridY, bool bRotated, int32& OutMergeEntryId) const;

	bool FindFreePosition(const TArray<uint8>& Occupied, const UProjectEXItemDefinition* Definition, int32& OutX, int32& OutY, bool& bOutRotated) const;
	void MarkOccupied(TArray<uint8>& Occupied, int32 X, int32 Y, int32 Width, int32 Height) const;
	bool RectIsFree(const TArray<uint8>& Occupied, int32 X, int32 Y, int32 Width, int32 Height) const;

	void HandleRotateItem();
	void EnsureInputActions();
	void RegisterMappingContext(const APawn* Pawn);
	void EnsureWidget();
	void SetInventoryInputMode(bool bOpen);
	bool IsLocalOwner() const;

	UPROPERTY(ReplicatedUsing=OnRep_Entries)
	TArray<FProjectEXInventoryEntry> Entries;

	UPROPERTY(ReplicatedUsing=OnRep_Equipment)
	TArray<FProjectEXEquippedItem> Equipment;

	UPROPERTY(Transient)
	TObjectPtr<UInputMappingContext> InventoryMappingContext;

	UPROPERTY(Transient)
	TObjectPtr<UProjectEXInventoryWidget> InventoryWidget;

	int32 NextEntryId = 1;
	bool bRegisteredMappingContext = false;
	bool bInventoryOpen = false;
	bool bLookInputIgnored = false;
};
