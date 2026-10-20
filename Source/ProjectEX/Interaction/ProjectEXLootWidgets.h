// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ProjectEXInventoryTypes.h"
#include "ProjectEXLootWidgets.generated.h"

class AProjectEXLootContainer;
class UProjectEXLootWidget;
class UBorder;
class UCanvasPanel;
class USizeBox;
class UTextBlock;

UCLASS()
class PROJECTEX_API UProjectEXLootSilentButton : public UButton
{
	GENERATED_BODY()

public:

	UProjectEXLootSilentButton()
	{
		InitIsFocusable(false);
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FProjectEXLootTake, int32, EntryId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FProjectEXLootClosed);

/** One item in a container grid. Double-click takes it. */
UCLASS()
class PROJECTEX_API UProjectEXLootItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void ApplyEntry(class UProjectEXLootWidget* InOwner, const FProjectEXInventoryEntry& Entry, float InCellSize);

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:

	TWeakObjectPtr<UProjectEXLootWidget> OwnerWidget;

	UPROPERTY(Transient)
	TObjectPtr<UBorder> Face;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> NameText;

	int32 EntryId = INDEX_NONE;
	double LastClickSeconds = -1.0;
};

/** Smaller grid for a searched container. */
UCLASS()
class PROJECTEX_API UProjectEXLootWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void Open(AProjectEXLootContainer* InContainer);
	void NotifyTake(int32 EntryId);

	UPROPERTY(BlueprintAssignable, Category="Loot")
	FProjectEXLootTake OnTakeClicked;

	UPROPERTY(BlueprintAssignable, Category="Loot")
	FProjectEXLootClosed OnClosed;

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;

private:

	void BuildLayout();
	void Refresh();

	UFUNCTION()
	void HandleContentsChanged();

	UFUNCTION()
	void HandleCloseClicked();

	TWeakObjectPtr<AProjectEXLootContainer> Container;

	UPROPERTY(Transient)
	TObjectPtr<USizeBox> GridSizeBox;

	UPROPERTY(Transient)
	TObjectPtr<UCanvasPanel> GridCanvas;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> HintText;

	float CellSize = 52.0f;
};
