// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "InputCoreTypes.h"
#include "ProjectEXInventoryWidget.generated.h"

class UButton;
class UProjectEXInventoryComponent;
class UScrollBox;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FProjectEXInventorySlotClicked, int32, EntryId);

/** Button that does not take keyboard focus, so Tab still toggles the inventory. */
UCLASS()
class PROJECTEX_API UProjectEXInventoryButton : public UButton
{
	GENERATED_BODY()

public:

	UProjectEXInventoryButton()
	{
		InitIsFocusable(false);
	}
};

/** One clickable inventory row. */
UCLASS()
class PROJECTEX_API UProjectEXInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void Setup(int32 InEntryId, const FText& InLabel, bool bInSelected);
	void SetSelected(bool bInSelected);
	int32 GetEntryId() const { return EntryId; }

	UPROPERTY(BlueprintAssignable, Category="Inventory")
	FProjectEXInventorySlotClicked OnSlotClicked;

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;

private:

	void ApplyPresentation();

	UFUNCTION()
	void HandleClicked();

	UPROPERTY(Transient)
	TObjectPtr<UButton> Button;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> LabelText;

	int32 EntryId = INDEX_NONE;
	FText Label;
	bool bSelected = false;
};

/**
 *  Temporary inventory panel. Presentation only; the component owns the items.
 */
UCLASS()
class PROJECTEX_API UProjectEXInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void BindInventory(UProjectEXInventoryComponent* Inventory);
	void SetToggleKey(const FKey& InKey);

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void NativeDestruct() override;

private:

	void BuildLayout();
	void Refresh();
	void UpdateSelectionVisuals();
	void QueueRefresh();
	void PerformRefresh();

	UFUNCTION()
	void HandleInventoryChanged();

	UFUNCTION()
	void HandleSlotClicked(int32 ClickedEntryId);

	UFUNCTION()
	void HandleDropClicked();

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> CapacityText;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> HintText;

	UPROPERTY(Transient)
	TObjectPtr<UScrollBox> ItemList;

	UPROPERTY(Transient)
	TObjectPtr<UButton> DropButton;

	TWeakObjectPtr<UProjectEXInventoryComponent> BoundInventory;

	FKey ToggleKey;
	int32 SelectedEntryId = INDEX_NONE;
	bool bRefreshQueued = false;
};
