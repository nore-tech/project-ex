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
 *  Per-player inventory. The server mutates entries, and they replicate only to the owning player.
 *  Slot count is the capacity limit for now. EntryId is the stable handle for later grid and equipment work.
 */
UCLASS(ClassGroup=(Inventory), meta=(BlueprintSpawnableComponent))
class PROJECTEX_API UProjectEXInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UProjectEXInventoryComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Binds the inventory toggle. When no input action is assigned, creates a runtime mapping for ToggleInventoryKey. */
	void BindInput(UEnhancedInputComponent* EnhancedInput);

	/** Adds as many units as capacity and stacking allow. Server only. Returns the amount added. */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	int32 AddItem(UProjectEXItemDefinition* Definition, int32 Quantity);

	/** Removes up to Quantity from one entry. Server only. Returns the amount removed. */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	int32 RemoveItem(int32 EntryId, int32 Quantity);

	/** Asks the server to drop one unit from an entry. */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RequestDrop(int32 EntryId);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void ToggleInventory();

	UFUNCTION(BlueprintPure, Category="Inventory")
	TArray<FProjectEXInventoryEntry> GetEntries() const { return Entries; }

	UFUNCTION(BlueprintPure, Category="Inventory")
	int32 GetUsedSlotCount() const { return Entries.Num(); }

	UFUNCTION(BlueprintPure, Category="Inventory")
	int32 GetMaxSlotCount() const { return MaxSlots; }

	UFUNCTION(BlueprintPure, Category="Inventory")
	bool IsInventoryOpen() const { return bInventoryOpen; }

	FKey GetToggleInventoryKey() const { return ToggleInventoryKey; }

	UPROPERTY(BlueprintAssignable, Category="Inventory")
	FProjectEXInventoryChanged OnInventoryChanged;

protected:

	/** Maximum occupied slots. A stack uses one slot. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory", meta=(ClampMin="1"))
	int32 MaxSlots = 8;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ToggleInventoryAction;

	UPROPERTY(EditAnywhere, Category="Input")
	FKey ToggleInventoryKey;

	UPROPERTY(EditAnywhere, Category="Inventory")
	TSubclassOf<UProjectEXInventoryWidget> InventoryWidgetClass;

	UFUNCTION()
	void OnRep_Entries();

	UFUNCTION(Server, Reliable)
	void ServerDropItem(int32 EntryId);

private:

	bool HasInventoryAuthority() const;
	void NotifyChanged();
	bool DropItem(int32 EntryId);
	FTransform MakeDropTransform(const APawn* Pawn) const;
	FProjectEXInventoryEntry* FindEntry(int32 EntryId);
	void EnsureToggleAction();
	void RegisterMappingContext(const APawn* Pawn);
	void EnsureWidget();
	void SetInventoryInputMode(bool bOpen);
	bool IsLocalOwner() const;

	UPROPERTY(ReplicatedUsing=OnRep_Entries)
	TArray<FProjectEXInventoryEntry> Entries;

	UPROPERTY(Transient)
	TObjectPtr<UInputMappingContext> ToggleMappingContext;

	UPROPERTY(Transient)
	TObjectPtr<UProjectEXInventoryWidget> InventoryWidget;

	int32 NextEntryId = 1;
	bool bRegisteredMappingContext = false;
	bool bInventoryOpen = false;
	bool bLookInputIgnored = false;
};
