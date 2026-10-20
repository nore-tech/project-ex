// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "InputCoreTypes.h"
#include "ProjectEXInventoryTypes.h"
#include "ProjectEXInventoryWidget.generated.h"

class AProjectEXLootContainer;
class UProjectEXLootComponent;
class UBorder;
class UCanvasPanel;
class UHorizontalBox;
class UImage;
class UProjectEXInventoryComponent;
class UTexture2D;
class USizeBox;
class UTextBlock;
class UVerticalBox;

enum class EProjectEXDragOrigin : uint8
{
	Pockets,
	Container,
	Equipment
};

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

	void ApplyEntry(UProjectEXInventoryWidget* InOwner, const FProjectEXInventoryEntry& Entry, float InCellSize, bool bInSelected, EProjectEXDragOrigin InOrigin = EProjectEXDragOrigin::Pockets);
	void SetSelected(bool bInSelected);
	int32 GetEntryId() const { return EntryId; }
	EProjectEXDragOrigin GetOrigin() const { return Origin; }

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
	EProjectEXDragOrigin Origin = EProjectEXDragOrigin::Pockets;
};

/** One right-click action. It does not take keyboard focus. */
UCLASS()
class PROJECTEX_API UProjectEXContextActionButton : public UProjectEXInventoryButton
{
	GENERATED_BODY()

public:

	int32 ActionId = 0;

	TWeakObjectPtr<UProjectEXInventoryWidget> OwnerWidget;

	UFUNCTION()
	void HandleClicked();
};

class UProjectEXInventoryWidget;

/** One worn slot in the inventory panel. */
UCLASS()
class PROJECTEX_API UProjectEXEquipmentSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeSlot(UProjectEXInventoryWidget* InOwner, EProjectEXEquipmentSlot InSlot, const FText& InLabel, bool bInEnabled);
	void SetOccupiedName(const FText& InName);
	void SetOccupiedIcon(UTexture2D* Texture);
	void SetDropHighlight(bool bActive, bool bValid);
	EProjectEXEquipmentSlot GetSlot() const { return Slot; }
	bool IsSlotEnabled() const { return bEnabled; }

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;

private:

	TWeakObjectPtr<UProjectEXInventoryWidget> OwnerWidget;

	UPROPERTY(Transient)
	TObjectPtr<UBorder> Face;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> TitleText;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> NameText;

	UPROPERTY(Transient)
	TObjectPtr<UImage> IconImage;

	UPROPERTY(Transient)
	TObjectPtr<USizeBox> IconBox;

	EProjectEXEquipmentSlot Slot = EProjectEXEquipmentSlot::PrimaryWeapon;
	FText SlotLabel;
	FText OccupiedName;
	bool bEnabled = false;
	bool bHighlightActive = false;
	bool bHighlightValid = false;
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
	void SetSearchedContainer(AProjectEXLootContainer* Container);
	void SetInputHints(const FKey& InToggleKey, const FKey& InRotateKey);
	void CancelDrag();
	void RotateDraggedItem();

	/** Returns false when this press should not start a drag. */
	bool BeginItemPointer(int32 EntryId, EProjectEXDragOrigin Origin, const FVector2D& ScreenPosition, const FVector2D& LocalGrabOffset, float SourceCellSize);
	void BeginEquippedPointer(EProjectEXEquipmentSlot Slot, const FVector2D& ScreenPosition, const FVector2D& LocalGrabOffset);
	void UpdateItemPointer(const FVector2D& ScreenPosition);
	void EndItemPointer(const FVector2D& ScreenPosition);
	void QuickTransfer(int32 EntryId, EProjectEXDragOrigin Origin);
	void QuickEquip(int32 EntryId, EProjectEXDragOrigin Origin);
	void ShowItemMenu(int32 EntryId, EProjectEXDragOrigin Origin, const FVector2D& ScreenPosition);
	void ExecuteContextAction(int32 ActionId);
	void ActivateItem(int32 EntryId, EProjectEXDragOrigin Origin);
	void ActivateEquipped(EProjectEXEquipmentSlot EquipmentSlot);
	bool ConsumeDoubleClick(int32 ClickId, EProjectEXDragOrigin Origin);
	int32 GetSelectedEntryId() const { return SelectedEntryId; }
	UProjectEXInventoryComponent* GetInventory() const { return BoundInventory.Get(); }

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:

	void BuildLayout();
	void Refresh();
	void RefreshEquipment();
	void RefreshContainer();
	void QueueRefresh();
	void PerformRefresh();
	void UpdateHints();
	void UpdateDragVisual(const FVector2D& ScreenPosition);
	void ShowHighlight(UCanvasPanel* Canvas, TArray<TObjectPtr<UBorder>>& Cells, int32 OriginX, int32 OriginY, int32 Width, int32 Height, bool bValid, float InCellSize);
	void HideHighlight();
	void HideGhost();
	void CloseContextMenu();
	int32 ComputeCellSize() const;
	bool FindDragEntry(FProjectEXInventoryEntry& OutEntry) const;
	bool FindEntry(int32 InEntryId, FProjectEXInventoryEntry& OutEntry) const;
	bool FindContainerEntry(int32 InEntryId, FProjectEXInventoryEntry& OutEntry) const;
	UProjectEXInventoryItemWidget* FindItemWidget(int32 InEntryId) const;
	UProjectEXEquipmentSlotWidget* FindEquipmentSlot(EProjectEXEquipmentSlot Slot) const;
	UProjectEXEquipmentSlotWidget* EquipmentSlotUnderCursor(const FVector2D& ScreenPosition) const;
	bool PointerOverWidget(const UWidget* Widget, const FVector2D& ScreenPosition) const;
	UProjectEXLootComponent* GetLoot() const;
	void AddContextAction(int32 ActionId, const FText& Label);

	UFUNCTION()
	void HandleInventoryChanged();

	UFUNCTION()
	void HandleContainerChanged();

	UFUNCTION()
	void HandleCloseClicked();

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
	TObjectPtr<UVerticalBox> ContainerColumn;

	UPROPERTY(Transient)
	TObjectPtr<UWidget> ContainerPanel;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> ContainerTitle;

	UPROPERTY(Transient)
	TObjectPtr<USizeBox> ContainerSizeBox;

	UPROPERTY(Transient)
	TObjectPtr<UCanvasPanel> ContainerCanvas;

	UPROPERTY(Transient)
	TObjectPtr<UVerticalBox> ContextMenuBox;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UProjectEXEquipmentSlotWidget>> EquipmentRows;

	UPROPERTY(Transient)
	TObjectPtr<UProjectEXInventoryItemWidget> GhostItem;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UBorder>> CellBorders;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UBorder>> HighlightCells;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UBorder>> ContainerCells;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UBorder>> ContainerHighlights;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UProjectEXInventoryItemWidget>> ItemWidgets;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UProjectEXInventoryItemWidget>> ContainerItemWidgets;

	TWeakObjectPtr<UProjectEXInventoryComponent> BoundInventory;
	TWeakObjectPtr<AProjectEXLootContainer> SearchedContainer;

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
	int32 ContextEntryId = INDEX_NONE;
	EProjectEXDragOrigin DragOrigin = EProjectEXDragOrigin::Pockets;
	EProjectEXDragOrigin ContextOrigin = EProjectEXDragOrigin::Pockets;
	EProjectEXEquipmentSlot DragEquipmentSlot = EProjectEXEquipmentSlot::PrimaryWeapon;
	float DragCellSize = 36.0f;
	float ContainerCellSize = 40.0f;
	FVector2D DragGrabOffset = FVector2D::ZeroVector;
	FVector2D PointerStartScreen = FVector2D::ZeroVector;
	FVector2D LastScreenPosition = FVector2D::ZeroVector;
	bool bDragRotated = false;
	bool bDragPreviewValid = false;
	bool bPointerDown = false;
	bool bDragActive = false;
	bool bRefreshQueued = false;
	double LastClickSeconds = -1.0;
	int32 LastClickId = INDEX_NONE;
	EProjectEXDragOrigin LastClickOrigin = EProjectEXDragOrigin::Pockets;
};
