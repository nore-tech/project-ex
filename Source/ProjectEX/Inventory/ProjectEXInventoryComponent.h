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
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	int32 AddItem(UProjectEXItemDefinition* Definition, int32 Quantity);

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

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void ToggleInventory();

	/** True when the entry can move, rotate, or merge at this cell. Ignores the entry's own cells. */
	UFUNCTION(BlueprintPure, Category="Inventory")
	bool CanPlaceEntry(int32 EntryId, int32 GridX, int32 GridY, bool bRotated) const;

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
	void OnRep_GridLayout();

	UFUNCTION(Server, Reliable)
	void ServerMoveItem(int32 EntryId, int32 GridX, int32 GridY, bool bRotated);

	UFUNCTION(Server, Reliable)
	void ServerDropItem(int32 EntryId);

	UFUNCTION(Server, Reliable)
	void ServerDropStack(int32 EntryId);

private:

	bool HasInventoryAuthority() const;
	void NotifyChanged();
	bool MoveItem(int32 EntryId, int32 GridX, int32 GridY, bool bRotated);
	bool DropItem(int32 EntryId, int32 Quantity);
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

	UPROPERTY(Transient)
	TObjectPtr<UInputMappingContext> InventoryMappingContext;

	UPROPERTY(Transient)
	TObjectPtr<UProjectEXInventoryWidget> InventoryWidget;

	int32 NextEntryId = 1;
	bool bRegisteredMappingContext = false;
	bool bInventoryOpen = false;
	bool bLookInputIgnored = false;
};
