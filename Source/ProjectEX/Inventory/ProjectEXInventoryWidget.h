// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "InputCoreTypes.h"
#include "ProjectEXInventoryTypes.h"
#include "ProjectEXInventoryWidget.generated.h"

class UBorder;
class UCanvasPanel;
class UImage;
class UProjectEXInventoryComponent;
class UTexture2D;
class USizeBox;
class UTextBlock;

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

/** One grid item. Presentation only; placement is requested from the inventory component. */
UCLASS()
class PROJECTEX_API UProjectEXInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void ApplyEntry(UProjectEXInventoryWidget* InOwner, const FProjectEXInventoryEntry& Entry, float InCellSize, bool bInSelected);
	void SetSelected(bool bInSelected);
	int32 GetEntryId() const { return EntryId; }

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;

private:

	void BuildItemLayout();
	void ApplyPresentation();

	TWeakObjectPtr<UProjectEXInventoryWidget> OwnerWidget;

	UPROPERTY(Transient)
	TObjectPtr<UBorder> OuterBorder;

	UPROPERTY(Transient)
	TObjectPtr<UBorder> InnerBorder;

	UPROPERTY(Transient)
	TObjectPtr<UImage> IconImage;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> NameText;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> InitialsText;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> QuantityText;

	UPROPERTY(Transient)
	TObjectPtr<UTexture2D> IconTexture;

	int32 EntryId = INDEX_NONE;
	FText ItemName;
	int32 Quantity = 0;
	int32 GridWidth = 1;
	int32 GridHeight = 1;
	float CellSize = 64.0f;
	FLinearColor Tint = FLinearColor(0.16f, 0.18f, 0.17f, 1.0f);
	bool bRotated = false;
	bool bHasIcon = false;
	bool bSelected = false;
};

/**
 *  Grid inventory panel. Dragging is local until the server accepts a move.
 */
UCLASS()
class PROJECTEX_API UProjectEXInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void BindInventory(UProjectEXInventoryComponent* Inventory);
	void SetInputHints(const FKey& InToggleKey, const FKey& InRotateKey);
	void CancelDrag();
	void RotateDraggedItem();

	void BeginItemPointer(int32 EntryId, const FVector2D& ScreenPosition, const FVector2D& LocalGrabOffset);
	void UpdateItemPointer(const FVector2D& ScreenPosition);
	void EndItemPointer(const FVector2D& ScreenPosition);

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:

	void BuildLayout();
	void Refresh();
	void QueueRefresh();
	void PerformRefresh();
	void UpdateHints();
	void UpdateDragVisual(const FVector2D& ScreenPosition);
	void ShowHighlight(int32 OriginX, int32 OriginY, int32 Width, int32 Height, bool bValid);
	bool IsPointerInsideInventory(const FVector2D& ScreenPosition) const;
	void HideHighlight();
	void HideGhost();
	int32 ComputeCellSize() const;
	bool FindEntry(int32 InEntryId, FProjectEXInventoryEntry& OutEntry) const;
	UProjectEXInventoryItemWidget* FindItemWidget(int32 InEntryId) const;
	UBorder* GetHighlightCell(int32 Index);

	UFUNCTION()
	void HandleInventoryChanged();

	UFUNCTION()
	void HandleCloseClicked();

	UFUNCTION()
	void HandleDropClicked();

	UPROPERTY(Transient)
	TObjectPtr<UCanvasPanel> RootCanvas;

	UPROPERTY(Transient)
	TObjectPtr<UBorder> InventoryFrame;

	UPROPERTY(Transient)
	TObjectPtr<USizeBox> GridSizeBox;

	UPROPERTY(Transient)
	TObjectPtr<UCanvasPanel> GridCanvas;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> CapacityText;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> HintText;

	UPROPERTY(Transient)
	TObjectPtr<UButton> DropButton;

	UPROPERTY(Transient)
	TObjectPtr<UProjectEXInventoryItemWidget> GhostItem;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UBorder>> CellBorders;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UBorder>> HighlightCells;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UProjectEXInventoryItemWidget>> ItemWidgets;

	TWeakObjectPtr<UProjectEXInventoryComponent> BoundInventory;

	FKey ToggleKey;
	FKey RotateKey;
	int32 SelectedEntryId = INDEX_NONE;
	int32 CellSize = 64;
	int32 LaidOutColumns = 0;
	int32 LaidOutRows = 0;
	int32 LaidOutCellSize = 0;

	int32 DragEpoch = 0;
	int32 DragEpochAtPointer = 0;
	int32 DragEntryId = INDEX_NONE;
	int32 DragPreviewX = 0;
	int32 DragPreviewY = 0;
	FVector2D DragGrabOffset = FVector2D::ZeroVector;
	FVector2D PointerStartScreen = FVector2D::ZeroVector;
	FVector2D LastScreenPosition = FVector2D::ZeroVector;
	bool bDragRotated = false;
	bool bDragPreviewValid = false;
	bool bPointerDown = false;
	bool bDragActive = false;
	bool bRefreshQueued = false;
};
