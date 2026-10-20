// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXInventoryWidget.h"
#include "ProjectEXInventoryComponent.h"
#include "ProjectEXItemDefinition.h"
#include "ProjectEXLootComponent.h"
#include "ProjectEXLootContainer.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/ButtonSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/ScaleBox.h"
#include "Components/SizeBox.h"
#include "Components/Spacer.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Engine/Texture2D.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/CoreStyle.h"
#include "TimerManager.h"

namespace
{
	FSlateFontInfo MakeInventoryFont(int32 Size)
	{
		return FCoreStyle::GetDefaultFontStyle(TEXT("Regular"), Size);
	}

	UTextBlock* MakeLabel(UWidgetTree* WidgetTree, const FSlateFontInfo& Font, const FLinearColor& Color)
	{
		UTextBlock* Text = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		Text->SetFont(Font);
		Text->SetColorAndOpacity(FSlateColor(Color));
		Text->SetShadowOffset(FVector2D(1.0f, 1.0f));
		Text->SetShadowColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.85f));
		Text->SetVisibility(ESlateVisibility::HitTestInvisible);
		return Text;
	}

	void SetCanvasRect(UWidget* Widget, float X, float Y, float Width, float Height, int32 ZOrder)
	{
		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Widget ? Widget->Slot : nullptr))
		{
			CanvasSlot->SetAutoSize(false);
			CanvasSlot->SetPosition(FVector2D(X, Y));
			CanvasSlot->SetSize(FVector2D(Width, Height));
			CanvasSlot->SetZOrder(ZOrder);
		}
	}
}

void UProjectEXInventoryItemWidget::ApplyEntry(UProjectEXInventoryWidget* InOwner, const FProjectEXInventoryEntry& Entry, float InCellSize, bool bInSelected, EProjectEXDragOrigin InOrigin)
{
	OwnerWidget = InOwner;
	Origin = InOrigin;
	EntryId = Entry.EntryId;
	Quantity = Entry.Quantity;
	bRotated = Entry.bRotated;
	bSelected = bInSelected;
	CellSize = FMath::Max(1.0f, InCellSize);
	GridWidth = 1;
	GridHeight = 1;
	bHasIcon = false;
	IconTexture = nullptr;
	ItemName = NSLOCTEXT("ProjectEX", "UnknownItem", "Unknown item");
	Tint = FLinearColor(0.16f, 0.18f, 0.17f, 1.0f);

	if (Entry.Definition)
	{
		ItemName = Entry.Definition->DisplayName.IsEmpty()
			? FText::FromName(Entry.Definition->GetItemId())
			: Entry.Definition->DisplayName;
		GridWidth = FMath::Max(1, Entry.Definition->GridWidth);
		GridHeight = FMath::Max(1, Entry.Definition->GridHeight);

		const uint32 Hash = GetTypeHash(Entry.Definition->GetItemId());
		Tint = FLinearColor::MakeFromHSV8(static_cast<uint8>(Hash % 256), 42, 38);
		Tint.A = 1.0f;
		IconTexture = Entry.Definition->Icon.LoadSynchronous();
		bHasIcon = IconTexture != nullptr;
	}

	ApplyPresentation();
}

void UProjectEXInventoryItemWidget::SetSelected(bool bInSelected)
{
	bSelected = bInSelected;
	ApplyPresentation();
}

TSharedRef<SWidget> UProjectEXInventoryItemWidget::RebuildWidget()
{
	if (WidgetTree && !WidgetTree->RootWidget)
	{
		BuildItemLayout();
	}

	ApplyPresentation();
	return Super::RebuildWidget();
}

FReply UProjectEXInventoryItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!OwnerWidget.IsValid())
	{
		return FReply::Handled();
	}

	const FVector2D ScreenPosition = InMouseEvent.GetScreenSpacePosition();
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		OwnerWidget->ShowItemMenu(EntryId, Origin, ScreenPosition);
		return FReply::Handled();
	}

	if (InMouseEvent.GetEffectingButton() != EKeys::LeftMouseButton)
	{
		return FReply::Handled();
	}

	const FModifierKeysState Modifiers = FSlateApplication::Get().GetModifierKeys();
	if (Modifiers.IsShiftDown())
	{
		OwnerWidget->QuickTransfer(EntryId, Origin);
		return FReply::Handled();
	}

	if (Modifiers.IsControlDown())
	{
		OwnerWidget->QuickEquip(EntryId, Origin);
		return FReply::Handled();
	}

	if (OwnerWidget->ConsumeDoubleClick(EntryId, Origin))
	{
		OwnerWidget->ActivateItem(EntryId, Origin);
		return FReply::Handled();
	}

	const FVector2D LocalGrab = InGeometry.AbsoluteToLocal(ScreenPosition);
	if (OwnerWidget->BeginItemPointer(EntryId, Origin, ScreenPosition, LocalGrab, CellSize))
	{
		return FReply::Handled().CaptureMouse(TakeWidget());
	}

	return FReply::Handled();
}

FReply UProjectEXInventoryItemWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!HasMouseCapture() || !OwnerWidget.IsValid())
	{
		return FReply::Unhandled();
	}

	OwnerWidget->UpdateItemPointer(InMouseEvent.GetScreenSpacePosition());
	return FReply::Handled();
}

FReply UProjectEXInventoryItemWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() != EKeys::LeftMouseButton)
	{
		return FReply::Handled();
	}

	if (OwnerWidget.IsValid())
	{
		OwnerWidget->EndItemPointer(InMouseEvent.GetScreenSpacePosition());
	}

	return FReply::Handled().ReleaseMouseCapture();
}

void UProjectEXInventoryItemWidget::NativeOnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent)
{
	Super::NativeOnMouseCaptureLost(CaptureLostEvent);

	if (OwnerWidget.IsValid())
	{
		OwnerWidget->CancelDrag();
	}
}

void UProjectEXInventoryItemWidget::BuildItemLayout()
{
	OuterBorder = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
	OuterBorder->SetPadding(FMargin(2.0f));
	OuterBorder->SetClipping(EWidgetClipping::ClipToBounds);
	WidgetTree->RootWidget = OuterBorder;

	InnerBorder = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
	InnerBorder->SetPadding(FMargin(2.0f));
	InnerBorder->SetClipping(EWidgetClipping::ClipToBounds);
	OuterBorder->SetContent(InnerBorder);

	UOverlay* Overlay = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass());
	Overlay->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	InnerBorder->SetContent(Overlay);

	IconImage = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
	IconImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	if (UOverlaySlot* IconSlot = Overlay->AddChildToOverlay(IconImage))
	{
		IconSlot->SetHorizontalAlignment(HAlign_Fill);
		IconSlot->SetVerticalAlignment(VAlign_Fill);
	}

	InitialsText = MakeLabel(WidgetTree, MakeInventoryFont(14), FLinearColor::White);
	InitialsText->SetJustification(ETextJustify::Center);
	if (UOverlaySlot* InitialsSlot = Overlay->AddChildToOverlay(InitialsText))
	{
		InitialsSlot->SetHorizontalAlignment(HAlign_Center);
		InitialsSlot->SetVerticalAlignment(VAlign_Center);
	}

	NameText = MakeLabel(WidgetTree, MakeInventoryFont(11), FLinearColor(0.95f, 0.95f, 0.93f, 1.0f));
	NameText->SetJustification(ETextJustify::Left);
	NameText->SetAutoWrapText(false);
	NameText->SetTextOverflowPolicy(ETextOverflowPolicy::Ellipsis);
	NameText->SetClipping(EWidgetClipping::ClipToBounds);
	if (UOverlaySlot* NameSlot = Overlay->AddChildToOverlay(NameText))
	{
		NameSlot->SetHorizontalAlignment(HAlign_Fill);
		NameSlot->SetVerticalAlignment(VAlign_Top);
		NameSlot->SetPadding(FMargin(2.0f, 0.0f, 2.0f, 0.0f));
	}

	QuantityText = MakeLabel(WidgetTree, MakeInventoryFont(12), FLinearColor::White);
	QuantityText->SetJustification(ETextJustify::Right);
	if (UOverlaySlot* QuantitySlot = Overlay->AddChildToOverlay(QuantityText))
	{
		QuantitySlot->SetHorizontalAlignment(HAlign_Right);
		QuantitySlot->SetVerticalAlignment(VAlign_Bottom);
	}
}

void UProjectEXInventoryItemWidget::ApplyPresentation()
{
	if (!OuterBorder || !InnerBorder)
	{
		return;
	}

	const FLinearColor Edge = bSelected
		? FLinearColor(0.86f, 0.72f, 0.34f, 1.0f)
		: FLinearColor(0.05f, 0.05f, 0.05f, 1.0f);
	OuterBorder->SetBrushColor(Edge);
	InnerBorder->SetBrushColor(Tint);

	const int32 ShownWidth = bRotated ? GridHeight : GridWidth;
	const int32 ShownHeight = bRotated ? GridWidth : GridHeight;
	const float WidthPx = ShownWidth * CellSize;
	const float HeightPx = ShownHeight * CellSize;
	const bool bShowName = WidthPx >= 72.0f && HeightPx >= 32.0f;
	if (NameText)
	{
		NameText->SetFont(MakeInventoryFont(FMath::Clamp(FMath::FloorToInt(CellSize * 0.34f), 9, 13)));
		NameText->SetText(ItemName);
		NameText->SetVisibility(bShowName ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	}

	if (InitialsText)
	{
		FString ShortName = ItemName.ToString();
		if (ShortName.IsEmpty())
		{
			ShortName = TEXT("Item");
		}
		if (ShortName.Len() > 3)
		{
			ShortName = ShortName.Left(2);
		}
		InitialsText->SetFont(MakeInventoryFont(FMath::Clamp(FMath::FloorToInt(CellSize * 0.38f), 8, 12)));
		InitialsText->SetText(FText::FromString(ShortName.ToUpper()));
		InitialsText->SetVisibility((bHasIcon || bShowName) ? ESlateVisibility::Collapsed : ESlateVisibility::HitTestInvisible);
	}

	if (IconImage)
	{
		if (bHasIcon && IconTexture)
		{
			IconImage->SetBrushFromTexture(IconTexture, true);
		}
		IconImage->SetVisibility(bHasIcon ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
		IconImage->SetRenderTransformAngle(bRotated ? 90.0f : 0.0f);
		IconImage->SetRenderTransformPivot(FVector2D(0.5f, 0.5f));
	}

	if (QuantityText)
	{
		QuantityText->SetFont(MakeInventoryFont(FMath::Clamp(FMath::FloorToInt(CellSize * 0.34f), 8, 12)));
		QuantityText->SetText(FText::AsNumber(FMath::Max(0, Quantity)));
		QuantityText->SetVisibility(Quantity > 1 ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	}
}

void UProjectEXInventoryWidget::BindInventory(UProjectEXInventoryComponent* Inventory)
{
	if (BoundInventory.Get() != Inventory)
	{
		if (UProjectEXInventoryComponent* Previous = BoundInventory.Get())
		{
			Previous->OnInventoryChanged.RemoveDynamic(this, &UProjectEXInventoryWidget::HandleInventoryChanged);
		}

		BoundInventory = Inventory;
		if (Inventory)
		{
			Inventory->OnInventoryChanged.AddDynamic(this, &UProjectEXInventoryWidget::HandleInventoryChanged);
		}
	}

	Refresh();
}

void UProjectEXInventoryWidget::SetInputHints(const FKey& InToggleKey, const FKey& InRotateKey)
{
	ToggleKey = InToggleKey;
	RotateKey = InRotateKey;
	UpdateHints();
}

void UProjectEXInventoryWidget::CancelDrag()
{
	if (!bPointerDown && !bDragActive)
	{
		HideGhost();
		HideHighlight();
		return;
	}

	++DragEpoch;
	bPointerDown = false;
	bDragActive = false;
	HideGhost();
	HideHighlight();
	QueueRefresh();

	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().ReleaseAllPointerCapture();
	}
}

void UProjectEXInventoryWidget::RotateDraggedItem()
{
	if (!bDragActive)
	{
		return;
	}

	FProjectEXInventoryEntry Entry;
	if (!FindDragEntry(Entry) || !Entry.Definition)
	{
		CancelDrag();
		return;
	}

	const float Cell = FMath::Max(1.0f, DragCellSize);
	const FIntPoint OldSize = Entry.Definition->GetGridSize(bDragRotated);
	const FVector2D OldGrab = DragGrabOffset;
	bDragRotated = !bDragRotated;
	const FIntPoint NewSize = Entry.Definition->GetGridSize(bDragRotated);
	const float NewWidth = NewSize.X * Cell;
	const float NewHeight = NewSize.Y * Cell;
	DragGrabOffset.X = FMath::Clamp(OldGrab.Y, 0.0f, FMath::Max(1.0f, NewWidth - 1.0f));
	DragGrabOffset.Y = FMath::Clamp((OldSize.X * Cell) - OldGrab.X, 0.0f, FMath::Max(1.0f, NewHeight - 1.0f));
	UpdateDragVisual(LastScreenPosition);
}

bool UProjectEXInventoryWidget::BeginItemPointer(int32 EntryId, EProjectEXDragOrigin Origin, const FVector2D& ScreenPosition, const FVector2D& LocalGrabOffset, float SourceCellSize)
{
	FProjectEXInventoryEntry Entry;
	const bool bFound = Origin == EProjectEXDragOrigin::Container
		? FindContainerEntry(EntryId, Entry)
		: FindEntry(EntryId, Entry);
	if (!bFound || !Entry.Definition)
	{
		return false;
	}

	CloseContextMenu();
	DragOrigin = Origin;
	DragEpochAtPointer = DragEpoch;
	DragEntryId = EntryId;
	DragCellSize = FMath::Max(1.0f, SourceCellSize);
	DragGrabOffset = LocalGrabOffset;
	PointerStartScreen = ScreenPosition;
	LastScreenPosition = ScreenPosition;
	bDragRotated = Entry.bRotated;
	bPointerDown = true;
	bDragActive = false;
	bDragPreviewValid = false;
	SelectedEntryId = Origin == EProjectEXDragOrigin::Pockets ? EntryId : INDEX_NONE;
	return true;
}

void UProjectEXInventoryWidget::BeginEquippedPointer(EProjectEXEquipmentSlot EquipmentSlot, const FVector2D& ScreenPosition, const FVector2D& LocalGrabOffset)
{
	const UProjectEXInventoryComponent* Inventory = BoundInventory.Get();
	FProjectEXEquippedItem Worn;
	if (!Inventory || !Inventory->GetEquippedItem(EquipmentSlot, Worn) || !Worn.IsOccupied() || !Worn.Definition)
	{
		return;
	}

	CloseContextMenu();
	DragOrigin = EProjectEXDragOrigin::Equipment;
	DragEquipmentSlot = EquipmentSlot;
	DragEpochAtPointer = DragEpoch;
	DragEntryId = INDEX_NONE;
	DragCellSize = CellSize > 0 ? static_cast<float>(CellSize) : 36.0f;
	const FIntPoint Size = Worn.Definition->GetGridSize(false);
	DragGrabOffset.X = FMath::Clamp(LocalGrabOffset.X, 0.0f, FMath::Max(1.0f, Size.X * DragCellSize - 1.0f));
	DragGrabOffset.Y = FMath::Clamp(LocalGrabOffset.Y, 0.0f, FMath::Max(1.0f, Size.Y * DragCellSize - 1.0f));
	PointerStartScreen = ScreenPosition;
	LastScreenPosition = ScreenPosition;
	bDragRotated = false;
	bPointerDown = true;
	bDragActive = false;
	bDragPreviewValid = false;
	SelectedEntryId = INDEX_NONE;
}

void UProjectEXInventoryWidget::UpdateItemPointer(const FVector2D& ScreenPosition)
{
	if (!bPointerDown || DragEpochAtPointer != DragEpoch)
	{
		return;
	}

	LastScreenPosition = ScreenPosition;
	if (!bDragActive && FVector2D::Distance(ScreenPosition, PointerStartScreen) >= 8.0f)
	{
		bDragActive = true;
		if (UProjectEXInventoryItemWidget* SourceItem = FindItemWidget(DragEntryId))
		{
			SourceItem->SetRenderOpacity(0.35f);
		}
	}

	if (bDragActive)
	{
		UpdateDragVisual(ScreenPosition);
	}
}

void UProjectEXInventoryWidget::EndItemPointer(const FVector2D& ScreenPosition)
{
	if (!bPointerDown || DragEpochAtPointer != DragEpoch)
	{
		return;
	}

	const bool bWasDragging = bDragActive;
	const int32 EntryId = DragEntryId;
	const bool bRotated = bDragRotated;
	const EProjectEXDragOrigin Origin = DragOrigin;
	const EProjectEXEquipmentSlot FromSlot = DragEquipmentSlot;

	if (bWasDragging)
	{
		UpdateDragVisual(ScreenPosition);
	}

	if (!bPointerDown || DragEpochAtPointer != DragEpoch)
	{
		return;
	}

	const int32 PreviewX = DragPreviewX;
	const int32 PreviewY = DragPreviewY;
	const bool bValidPreview = bDragPreviewValid;
	bPointerDown = false;
	bDragActive = false;

	if (!bWasDragging)
	{
		if (Origin == EProjectEXDragOrigin::Pockets)
		{
			SelectedEntryId = EntryId;
		}

		for (UProjectEXInventoryItemWidget* ItemWidget : ItemWidgets)
		{
			if (ItemWidget)
			{
				ItemWidget->SetSelected(ItemWidget->GetEntryId() == SelectedEntryId);
				ItemWidget->SetRenderOpacity(1.0f);
			}
		}

		HideGhost();
		HideHighlight();
		return;
	}

	UProjectEXInventoryComponent* Inventory = BoundInventory.Get();
	UProjectEXLootComponent* Loot = GetLoot();
	if (UProjectEXEquipmentSlotWidget* SlotWidget = EquipmentSlotUnderCursor(ScreenPosition))
	{
		if (bValidPreview && SlotWidget->IsSlotEnabled() && Inventory)
		{
			const EProjectEXEquipmentSlot TargetSlot = SlotWidget->GetSlot();
			if (Origin == EProjectEXDragOrigin::Pockets)
			{
				Inventory->RequestEquip(EntryId, TargetSlot);
			}
			else if (Origin == EProjectEXDragOrigin::Container && Loot)
			{
				Loot->RequestEquipContainerItem(EntryId, TargetSlot);
			}
			else if (Origin == EProjectEXDragOrigin::Equipment && TargetSlot != FromSlot)
			{
				Inventory->RequestMoveEquipped(FromSlot, TargetSlot);
			}
		}

		HideGhost();
		HideHighlight();
		QueueRefresh();
		return;
	}

	FProjectEXInventoryEntry SourceEntry;
	const bool bFoundSource = FindDragEntry(SourceEntry);
	const bool bSamePocket = Origin == EProjectEXDragOrigin::Pockets && bFoundSource
		&& SourceEntry.GridX == PreviewX && SourceEntry.GridY == PreviewY && SourceEntry.bRotated == bRotated;
	const bool bSameContainer = Origin == EProjectEXDragOrigin::Container && bFoundSource
		&& SourceEntry.GridX == PreviewX && SourceEntry.GridY == PreviewY && SourceEntry.bRotated == bRotated;

	if (PointerOverWidget(GridCanvas, ScreenPosition))
	{
		if (bValidPreview && Inventory && !bSamePocket)
		{
			if (Origin == EProjectEXDragOrigin::Pockets)
			{
				Inventory->RequestMoveItem(EntryId, PreviewX, PreviewY, bRotated);
			}
			else if (Origin == EProjectEXDragOrigin::Container && Loot)
			{
				Loot->RequestTakeAt(EntryId, PreviewX, PreviewY, bRotated);
			}
			else if (Origin == EProjectEXDragOrigin::Equipment)
			{
				Inventory->RequestUnequipAt(FromSlot, PreviewX, PreviewY, bRotated);
			}
		}

		HideGhost();
		HideHighlight();
		QueueRefresh();
		return;
	}

	if (PointerOverWidget(ContainerCanvas, ScreenPosition) && SearchedContainer.IsValid())
	{
		if (bValidPreview && Loot && !bSameContainer)
		{
			if (Origin == EProjectEXDragOrigin::Pockets)
			{
				Loot->RequestDepositAt(EntryId, PreviewX, PreviewY, bRotated);
			}
			else if (Origin == EProjectEXDragOrigin::Container)
			{
				Loot->RequestMoveContainerItem(EntryId, PreviewX, PreviewY, bRotated);
			}
			else if (Origin == EProjectEXDragOrigin::Equipment)
			{
				Loot->RequestDepositEquippedAt(FromSlot, PreviewX, PreviewY, bRotated);
			}
		}

		HideGhost();
		HideHighlight();
		QueueRefresh();
		return;
	}

	if (Origin == EProjectEXDragOrigin::Pockets && Inventory && !PointerOverWidget(InventoryFrame, ScreenPosition))
	{
		Inventory->RequestDropStack(EntryId);
	}

	HideGhost();
	HideHighlight();
	QueueRefresh();
}

TSharedRef<SWidget> UProjectEXInventoryWidget::RebuildWidget()
{
	if (WidgetTree && !WidgetTree->RootWidget)
	{
		BuildLayout();
	}

	return Super::RebuildWidget();
}

void UProjectEXInventoryWidget::NativeDestruct()
{
	CancelDrag();

	if (UProjectEXInventoryComponent* Inventory = BoundInventory.Get())
	{
		Inventory->OnInventoryChanged.RemoveDynamic(this, &UProjectEXInventoryWidget::HandleInventoryChanged);
	}

	if (AProjectEXLootContainer* Container = SearchedContainer.Get())
	{
		Container->OnContentsChanged.RemoveDynamic(this, &UProjectEXInventoryWidget::HandleContainerChanged);
	}

	Super::NativeDestruct();
}

void UProjectEXInventoryWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bDragActive && FSlateApplication::IsInitialized())
	{
		UpdateDragVisual(FSlateApplication::Get().GetCursorPos());
		return;
	}

	const int32 NewCellSize = ComputeCellSize();
	if (NewCellSize != CellSize)
	{
		CellSize = NewCellSize;
		Refresh();
	}
}

FReply UProjectEXInventoryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	CloseContextMenu();
	if (!bDragActive)
	{
		SelectedEntryId = INDEX_NONE;
		for (UProjectEXInventoryItemWidget* ItemWidget : ItemWidgets)
		{
			if (ItemWidget)
			{
				ItemWidget->SetSelected(false);
			}
		}
	}

	return FReply::Handled();
}

void UProjectEXInventoryWidget::Refresh()
{
	if (!GridCanvas || !GridSizeBox || !CapacityText)
	{
		return;
	}

	const UProjectEXInventoryComponent* Inventory = BoundInventory.Get();
	const int32 Columns = Inventory ? Inventory->GetGridColumns() : 10;
	const int32 Rows = Inventory ? Inventory->GetGridRows() : 6;
	CellSize = ComputeCellSize();

	for (UBorder* Cell : CellBorders)
	{
		if (Cell)
		{
			Cell->RemoveFromParent();
		}
	}
	CellBorders.Reset();
	for (UBorder* Highlight : HighlightCells)
	{
		if (Highlight)
		{
			Highlight->RemoveFromParent();
		}
	}
	HighlightCells.Reset();

	for (int32 Y = 0; Y < Rows; ++Y)
	{
		for (int32 X = 0; X < Columns; ++X)
		{
			UBorder* Cell = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
			Cell->SetBrushColor(FLinearColor(0.055f, 0.058f, 0.064f, 1.0f));
			Cell->SetVisibility(ESlateVisibility::HitTestInvisible);
			GridCanvas->AddChild(Cell);
			SetCanvasRect(Cell, X * CellSize + 1.0f, Y * CellSize + 1.0f, CellSize - 2.0f, CellSize - 2.0f, 0);
			CellBorders.Add(Cell);
		}
	}

	LaidOutColumns = Columns;
	LaidOutRows = Rows;
	LaidOutCellSize = CellSize;
	GridSizeBox->SetWidthOverride(Columns * CellSize);
	GridSizeBox->SetHeightOverride(Rows * CellSize);

	for (UProjectEXInventoryItemWidget* ItemWidget : ItemWidgets)
	{
		if (ItemWidget)
		{
			ItemWidget->RemoveFromParent();
		}
	}
	ItemWidgets.Reset();

	const TArray<FProjectEXInventoryEntry> Entries = Inventory ? Inventory->GetEntries() : TArray<FProjectEXInventoryEntry>();
	bool bSelectionStillValid = false;
	for (const FProjectEXInventoryEntry& Entry : Entries)
	{
		if (!Entry.Definition || Entry.Quantity <= 0)
		{
			continue;
		}

		if (Entry.EntryId == SelectedEntryId)
		{
			bSelectionStillValid = true;
		}

		UProjectEXInventoryItemWidget* ItemWidget = CreateWidget<UProjectEXInventoryItemWidget>(this, UProjectEXInventoryItemWidget::StaticClass());
		if (!ItemWidget)
		{
			continue;
		}

		ItemWidget->ApplyEntry(this, Entry, CellSize, Entry.EntryId == SelectedEntryId, EProjectEXDragOrigin::Pockets);
		GridCanvas->AddChild(ItemWidget);
		const FIntPoint Size = Entry.Definition->GetGridSize(Entry.bRotated);
		SetCanvasRect(ItemWidget, Entry.GridX * CellSize, Entry.GridY * CellSize, Size.X * CellSize, Size.Y * CellSize, 2);
		ItemWidgets.Add(ItemWidget);
	}

	if (!bSelectionStillValid)
	{
		SelectedEntryId = INDEX_NONE;
	}

	const int32 UsedCells = Inventory ? Inventory->GetOccupiedCellCount() : 0;
	const int32 TotalCells = Columns * Rows;
	CapacityText->SetText(FText::Format(
		NSLOCTEXT("ProjectEX", "InventoryGridCapacity", "Pockets {0} / {1}"),
		FText::AsNumber(UsedCells),
		FText::AsNumber(TotalCells)));

	RefreshEquipment();
	RefreshContainer();
	HideHighlight();
	if (!bDragActive)
	{
		HideGhost();
	}
}

void UProjectEXInventoryWidget::QueueRefresh()
{
	if (bRefreshQueued)
	{
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		Refresh();
		return;
	}

	bRefreshQueued = true;
	World->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUObject(this, &UProjectEXInventoryWidget::PerformRefresh));
}

void UProjectEXInventoryWidget::PerformRefresh()
{
	if (bDragActive)
	{
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUObject(this, &UProjectEXInventoryWidget::PerformRefresh));
		}
		return;
	}

	bRefreshQueued = false;
	Refresh();
}

void UProjectEXInventoryWidget::UpdateHints()
{
	if (!HintText)
	{
		return;
	}

	const FText ToggleName = ToggleKey.IsValid() ? ToggleKey.GetDisplayName() : FText::FromString(TEXT("Tab"));
	const FText RotateName = RotateKey.IsValid() ? RotateKey.GetDisplayName() : FText::FromString(TEXT("R"));
	HintText->SetText(FText::Format(
		NSLOCTEXT("ProjectEX", "InventoryGridHint", "{0} closes   {1} rotates   Shift transfers   Ctrl equips   Double-click uses or equips   Right-click menu"),
		ToggleName,
		RotateName));
}

void UProjectEXInventoryWidget::UpdateDragVisual(const FVector2D& ScreenPosition)
{
	LastScreenPosition = ScreenPosition;
	HideHighlight();
	if (!bDragActive || !RootCanvas || !GhostItem)
	{
		return;
	}

	FProjectEXInventoryEntry Entry;
	if (!FindDragEntry(Entry) || !Entry.Definition)
	{
		CancelDrag();
		return;
	}

	FProjectEXInventoryEntry GhostEntry = Entry;
	GhostEntry.bRotated = bDragRotated;
	GhostItem->ApplyEntry(this, GhostEntry, DragCellSize, false, DragOrigin);
	GhostItem->SetVisibility(ESlateVisibility::HitTestInvisible);

	const FIntPoint Size = Entry.Definition->GetGridSize(bDragRotated);
	const FVector2D GhostSize(Size.X * DragCellSize, Size.Y * DragCellSize);
	const FVector2D RootLocal = RootCanvas->GetCachedGeometry().AbsoluteToLocal(ScreenPosition);
	SetCanvasRect(GhostItem, RootLocal.X - DragGrabOffset.X, RootLocal.Y - DragGrabOffset.Y, GhostSize.X, GhostSize.Y, 20);

	bDragPreviewValid = false;
	UProjectEXInventoryComponent* Inventory = BoundInventory.Get();
	if (UProjectEXEquipmentSlotWidget* SlotWidget = EquipmentSlotUnderCursor(ScreenPosition))
	{
		FProjectEXEquippedItem Worn;
		const bool bEmpty = Inventory && Inventory->GetEquippedItem(SlotWidget->GetSlot(), Worn) && !Worn.IsOccupied();
		const bool bSameSlot = DragOrigin == EProjectEXDragOrigin::Equipment && SlotWidget->GetSlot() == DragEquipmentSlot;
		const bool bCompatible = UProjectEXInventoryComponent::SlotAcceptsItem(SlotWidget->GetSlot(), Entry.Definition);
		bDragPreviewValid = SlotWidget->IsSlotEnabled() && bEmpty && bCompatible && !bSameSlot;
		SlotWidget->SetDropHighlight(true, bDragPreviewValid);
		return;
	}

	auto PreviewOnGrid = [&](UCanvasPanel* Canvas, TArray<TObjectPtr<UBorder>>& Cells, float InCellSize, TFunctionRef<bool(int32, int32)> CanPlace)
	{
		if (!PointerOverWidget(Canvas, ScreenPosition) || InCellSize <= 0.0f)
		{
			return false;
		}

		const float Scale = InCellSize / FMath::Max(1.0f, DragCellSize);
		const FVector2D GridLocal = Canvas->GetCachedGeometry().AbsoluteToLocal(ScreenPosition);
		const FVector2D TopLeft = GridLocal - (DragGrabOffset * Scale);
		DragPreviewX = FMath::FloorToInt((TopLeft.X + 0.01f) / InCellSize);
		DragPreviewY = FMath::FloorToInt((TopLeft.Y + 0.01f) / InCellSize);
		bDragPreviewValid = CanPlace(DragPreviewX, DragPreviewY);
		ShowHighlight(Canvas, Cells, DragPreviewX, DragPreviewY, Size.X, Size.Y, bDragPreviewValid, InCellSize);
		return true;
	};

	if (Inventory && PreviewOnGrid(GridCanvas, HighlightCells, static_cast<float>(CellSize), [&](int32 X, int32 Y)
	{
		return DragOrigin == EProjectEXDragOrigin::Pockets
			? Inventory->CanPlaceEntry(DragEntryId, X, Y, bDragRotated)
			: Inventory->CanAcceptItem(Entry.Definition, Entry.Quantity, Entry.MagazineRounds, X, Y, bDragRotated);
	}))
	{
		return;
	}

	if (const AProjectEXLootContainer* Container = SearchedContainer.Get())
	{
		const int32 IgnoreEntryId = DragOrigin == EProjectEXDragOrigin::Container ? DragEntryId : INDEX_NONE;
		PreviewOnGrid(ContainerCanvas, ContainerHighlights, ContainerCellSize, [&](int32 X, int32 Y)
		{
			return Container->CanPlaceItem(Entry.Definition, Entry.Quantity, Entry.MagazineRounds, X, Y, bDragRotated, IgnoreEntryId);
		});
	}
}

void UProjectEXInventoryWidget::ShowHighlight(UCanvasPanel* Canvas, TArray<TObjectPtr<UBorder>>& Cells, int32 OriginX, int32 OriginY, int32 Width, int32 Height, bool bValid, float InCellSize)
{
	if (!Canvas || !WidgetTree || InCellSize <= 0.0f)
	{
		return;
	}

	int32 Columns = LaidOutColumns;
	int32 Rows = LaidOutRows;
	if (Canvas == ContainerCanvas)
	{
		if (const AProjectEXLootContainer* Container = SearchedContainer.Get())
		{
			Columns = Container->GetGridColumns();
			Rows = Container->GetGridRows();
		}
	}
	else if (const UProjectEXInventoryComponent* Inventory = BoundInventory.Get())
	{
		Columns = Inventory->GetGridColumns();
		Rows = Inventory->GetGridRows();
	}

	const FLinearColor Color = bValid
		? FLinearColor(0.16f, 0.72f, 0.28f, 0.45f)
		: FLinearColor(0.78f, 0.16f, 0.12f, 0.5f);

	int32 Used = 0;
	for (int32 Y = OriginY; Y < OriginY + Height; ++Y)
	{
		for (int32 X = OriginX; X < OriginX + Width; ++X)
		{
			if (X < 0 || Y < 0 || X >= Columns || Y >= Rows)
			{
				continue;
			}

			while (Cells.Num() <= Used)
			{
				UBorder* Highlight = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
				Highlight->SetVisibility(ESlateVisibility::Collapsed);
				Canvas->AddChild(Highlight);
				Cells.Add(Highlight);
			}

			if (UBorder* Highlight = Cells[Used])
			{
				Highlight->SetBrushColor(Color);
				Highlight->SetVisibility(ESlateVisibility::HitTestInvisible);
				SetCanvasRect(Highlight, X * InCellSize, Y * InCellSize, InCellSize, InCellSize, 4);
			}
			++Used;
		}
	}

	for (int32 Index = Used; Index < Cells.Num(); ++Index)
	{
		if (Cells[Index])
		{
			Cells[Index]->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UProjectEXInventoryWidget::HideHighlight()
{
	for (UBorder* Highlight : HighlightCells)
	{
		if (Highlight)
		{
			Highlight->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	for (UBorder* Highlight : ContainerHighlights)
	{
		if (Highlight)
		{
			Highlight->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	for (UProjectEXEquipmentSlotWidget* SlotWidget : EquipmentRows)
	{
		if (SlotWidget)
		{
			SlotWidget->SetDropHighlight(false, false);
		}
	}
}

void UProjectEXInventoryWidget::HideGhost()
{
	if (GhostItem)
	{
		GhostItem->SetVisibility(ESlateVisibility::Collapsed);
	}
}

int32 UProjectEXInventoryWidget::ComputeCellSize() const
{
	const UProjectEXInventoryComponent* Inventory = BoundInventory.Get();
	const int32 Columns = FMath::Max(1, Inventory ? Inventory->GetGridColumns() : 10);
	const int32 Rows = FMath::Max(1, Inventory ? Inventory->GetGridRows() : 6);
	const float Fit = FMath::Min(320.0f / Columns, 192.0f / Rows);
	return FMath::Clamp(FMath::FloorToInt(Fit), 24, 32);
}

bool UProjectEXInventoryWidget::FindEntry(int32 InEntryId, FProjectEXInventoryEntry& OutEntry) const
{
	const UProjectEXInventoryComponent* Inventory = BoundInventory.Get();
	if (!Inventory)
	{
		return false;
	}

	for (const FProjectEXInventoryEntry& Entry : Inventory->GetEntries())
	{
		if (Entry.EntryId == InEntryId)
		{
			OutEntry = Entry;
			return true;
		}
	}

	return false;
}

UProjectEXInventoryItemWidget* UProjectEXInventoryWidget::FindItemWidget(int32 InEntryId) const
{
	for (UProjectEXInventoryItemWidget* ItemWidget : ItemWidgets)
	{
		if (ItemWidget && ItemWidget->GetEntryId() == InEntryId)
		{
			return ItemWidget;
		}
	}

	for (UProjectEXInventoryItemWidget* ItemWidget : ContainerItemWidgets)
	{
		if (ItemWidget && ItemWidget->GetEntryId() == InEntryId)
		{
			return ItemWidget;
		}
	}

	return nullptr;
}

void UProjectEXInventoryWidget::HandleInventoryChanged()
{
	QueueRefresh();
}

void UProjectEXInventoryWidget::HandleCloseClicked()
{
	if (UProjectEXInventoryComponent* Inventory = BoundInventory.Get())
	{
		Inventory->ToggleInventory();
	}
}


void UProjectEXInventoryWidget::BuildLayout()
{
	RootCanvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
	RootCanvas->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	WidgetTree->RootWidget = RootCanvas;

	UBorder* Dimmer = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
	Dimmer->SetBrushColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.78f));
	Dimmer->SetVisibility(ESlateVisibility::Visible);
	if (UCanvasPanelSlot* DimSlot = RootCanvas->AddChildToCanvas(Dimmer))
	{
		DimSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
		DimSlot->SetOffsets(FMargin(0.0f));
		DimSlot->SetZOrder(0);
	}

	UScaleBox* Scale = WidgetTree->ConstructWidget<UScaleBox>(UScaleBox::StaticClass());
	Scale->SetStretch(EStretch::ScaleToFit);
	Scale->SetStretchDirection(EStretchDirection::Both);
	Scale->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	if (UCanvasPanelSlot* ScaleSlot = RootCanvas->AddChildToCanvas(Scale))
	{
		ScaleSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
		ScaleSlot->SetOffsets(FMargin(48.0f, 36.0f));
		ScaleSlot->SetZOrder(1);
	}

	USizeBox* Design = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());
	Design->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	Scale->SetContent(Design);

	UBorder* Frame = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
	Frame->SetBrushColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
	Frame->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	Design->SetContent(Frame);
	InventoryFrame = Frame;

	UVerticalBox* Outer = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass());
	Outer->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	Frame->SetContent(Outer);

	UHorizontalBox* Columns = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
	Columns->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	if (UVerticalBoxSlot* ColumnSlot = Outer->AddChildToVerticalBox(Columns))
	{
		ColumnSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	}

	auto AddPanel = [this, Columns](float Width, float Height) -> UCanvasPanel*
	{
		USizeBox* PanelRoot = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());
		PanelRoot->SetWidthOverride(Width);
		PanelRoot->SetHeightOverride(Height);
		PanelRoot->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		if (UHorizontalBoxSlot* PanelSlot = Columns->AddChildToHorizontalBox(PanelRoot))
		{
			PanelSlot->SetPadding(FMargin(8.0f, 0.0f));
			PanelSlot->SetVerticalAlignment(VAlign_Top);
		}

		UBorder* Stroke = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
		Stroke->SetBrushColor(FLinearColor(0.78f, 0.8f, 0.84f, 0.9f));
		Stroke->SetPadding(FMargin(1.0f));
		Stroke->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		PanelRoot->SetContent(Stroke);

		UBorder* Fill = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
		Fill->SetBrushColor(FLinearColor(0.012f, 0.013f, 0.015f, 0.94f));
		Fill->SetPadding(FMargin(0.0f));
		Fill->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Stroke->SetContent(Fill);

		UCanvasPanel* Canvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
		Canvas->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Fill->SetContent(Canvas);
		return Canvas;
	};

	auto PlaceLabel = [this](UCanvasPanel* Canvas, const FText& Label, float X, float Y, float Width, float Height)
	{
		UBorder* Stroke = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
		Stroke->SetBrushColor(FLinearColor(0.62f, 0.64f, 0.68f, 0.75f));
		Stroke->SetPadding(FMargin(1.0f));
		Stroke->SetClipping(EWidgetClipping::ClipToBounds);
		Stroke->SetVisibility(ESlateVisibility::HitTestInvisible);

		UBorder* Fill = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
		Fill->SetBrushColor(FLinearColor(0.03f, 0.032f, 0.036f, 1.0f));
		Fill->SetPadding(FMargin(4.0f));
		Fill->SetClipping(EWidgetClipping::ClipToBounds);
		Fill->SetVisibility(ESlateVisibility::HitTestInvisible);
		Stroke->SetContent(Fill);

		UTextBlock* Text = MakeLabel(WidgetTree, MakeInventoryFont(12), FLinearColor(0.9f, 0.9f, 0.92f, 1.0f));
		Text->SetText(Label);
		Text->SetJustification(ETextJustify::Center);
		Text->SetAutoWrapText(true);
		Text->SetTextOverflowPolicy(ETextOverflowPolicy::Ellipsis);
		Fill->SetContent(Text);

		Canvas->AddChild(Stroke);
		SetCanvasRect(Stroke, X, Y, Width, Height, 1);
	};

	auto PlaceEquipment = [this](UCanvasPanel* Canvas, EProjectEXEquipmentSlot EquipmentSlot, const FText& Label, float X, float Y, float Width, float Height)
	{
		UProjectEXEquipmentSlotWidget* SlotWidget = CreateWidget<UProjectEXEquipmentSlotWidget>(this, UProjectEXEquipmentSlotWidget::StaticClass());
		if (!SlotWidget)
		{
			return;
		}

		SlotWidget->InitializeSlot(this, EquipmentSlot, Label, true);
		Canvas->AddChild(SlotWidget);
		SetCanvasRect(SlotWidget, X, Y, Width, Height, 2);
		EquipmentRows.Add(SlotWidget);
	};

	UCanvasPanel* Character = AddPanel(468.0f, 700.0f);
	UTextBlock* CharacterTitle = MakeLabel(WidgetTree, MakeInventoryFont(18), FLinearColor(0.94f, 0.94f, 0.96f, 1.0f));
	CharacterTitle->SetText(NSLOCTEXT("ProjectEX", "CharacterColumn", "Character"));
	CharacterTitle->SetJustification(ETextJustify::Center);
	Character->AddChild(CharacterTitle);
	SetCanvasRect(CharacterTitle, 0.0f, 14.0f, 468.0f, 26.0f, 1);

	PlaceLabel(Character, NSLOCTEXT("ProjectEX", "SlotFace", "Face mask"), 28.0f, 58.0f, 78.0f, 86.0f);
	PlaceEquipment(Character, EProjectEXEquipmentSlot::Helmet, NSLOCTEXT("ProjectEX", "SlotHelmet", "Helmet"), 122.0f, 50.0f, 82.0f, 90.0f);
	PlaceLabel(Character, NSLOCTEXT("ProjectEX", "SlotGlasses", "Glasses"), 222.0f, 74.0f, 96.0f, 44.0f);
	PlaceLabel(Character, NSLOCTEXT("ProjectEX", "SlotBadge", "Badge"), 28.0f, 160.0f, 100.0f, 44.0f);
	PlaceEquipment(Character, EProjectEXEquipmentSlot::BodyArmor, NSLOCTEXT("ProjectEX", "SlotArmor", "Armor"), 132.0f, 156.0f, 82.0f, 90.0f);

	PlaceEquipment(Character, EProjectEXEquipmentSlot::PrimaryWeapon, NSLOCTEXT("ProjectEX", "SlotPrimary1", "Primary 1"), 28.0f, 300.0f, 292.0f, 108.0f);
	PlaceLabel(Character, NSLOCTEXT("ProjectEX", "SlotSidearm", "Sidearm"), 336.0f, 314.0f, 96.0f, 80.0f);
	PlaceEquipment(Character, EProjectEXEquipmentSlot::SecondaryWeapon, NSLOCTEXT("ProjectEX", "SlotPrimary2", "Primary 2"), 28.0f, 428.0f, 292.0f, 108.0f);
	PlaceLabel(Character, NSLOCTEXT("ProjectEX", "SlotMelee", "Melee"), 336.0f, 442.0f, 96.0f, 80.0f);

	const float GadgetY = 612.0f;
	const float GadgetSize = 34.0f;
	float GadgetX = 36.0f;
	for (int32 Index = 0; Index < 3; ++Index)
	{
		PlaceLabel(Character, FText::GetEmpty(), GadgetX, GadgetY, GadgetSize, GadgetSize);
		GadgetX += GadgetSize + 6.0f;
	}
	UTextBlock* GadgetLabel = MakeLabel(WidgetTree, MakeInventoryFont(12), FLinearColor(0.9f, 0.9f, 0.92f, 1.0f));
	GadgetLabel->SetText(NSLOCTEXT("ProjectEX", "SlotGadgets", "Gadget/Tools"));
	GadgetLabel->SetJustification(ETextJustify::Center);
	Character->AddChild(GadgetLabel);
	SetCanvasRect(GadgetLabel, GadgetX, GadgetY, 132.0f, GadgetSize, 2);
	GadgetX += 138.0f;
	for (int32 Index = 0; Index < 3; ++Index)
	{
		PlaceLabel(Character, FText::GetEmpty(), GadgetX, GadgetY, GadgetSize, GadgetSize);
		GadgetX += GadgetSize + 6.0f;
	}

	UCanvasPanel* Storage = AddPanel(520.0f, 700.0f);
	PlaceEquipment(Storage, EProjectEXEquipmentSlot::BodyArmor, NSLOCTEXT("ProjectEX", "SlotVest", "Vest"), 18.0f, 48.0f, 88.0f, 96.0f);

	GridSizeBox = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());
	GridSizeBox->SetWidthOverride(320.0f);
	GridSizeBox->SetHeightOverride(192.0f);
	GridSizeBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	GridCanvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
	GridCanvas->SetVisibility(ESlateVisibility::Visible);
	GridSizeBox->SetContent(GridCanvas);
	Storage->AddChild(GridSizeBox);
	SetCanvasRect(GridSizeBox, 122.0f, 36.0f, 320.0f, 192.0f, 1);

	PlaceEquipment(Storage, EProjectEXEquipmentSlot::Backpack, NSLOCTEXT("ProjectEX", "SlotBackpack", "Backpack"), 18.0f, 168.0f, 88.0f, 88.0f);

	CapacityText = MakeLabel(WidgetTree, MakeInventoryFont(12), FLinearColor(0.75f, 0.76f, 0.8f, 1.0f));
	CapacityText->SetJustification(ETextJustify::Left);
	Storage->AddChild(CapacityText);
	SetCanvasRect(CapacityText, 122.0f, 234.0f, 320.0f, 20.0f, 1);

	USizeBox* ContainerRoot = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());
	ContainerRoot->SetWidthOverride(460.0f);
	ContainerRoot->SetHeightOverride(700.0f);
	ContainerRoot->SetVisibility(ESlateVisibility::Collapsed);
	ContainerPanel = ContainerRoot;
	if (UHorizontalBoxSlot* ContainerSlot = Columns->AddChildToHorizontalBox(ContainerRoot))
	{
		ContainerSlot->SetPadding(FMargin(8.0f, 0.0f));
		ContainerSlot->SetVerticalAlignment(VAlign_Top);
	}

	UCanvasPanel* ContainerFrame = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
	ContainerFrame->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	ContainerRoot->SetContent(ContainerFrame);

	UBorder* ContainerStroke = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
	ContainerStroke->SetBrushColor(FLinearColor(0.78f, 0.8f, 0.84f, 0.9f));
	ContainerStroke->SetPadding(FMargin(1.0f));
	ContainerStroke->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	UBorder* ContainerFill = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
	ContainerFill->SetBrushColor(FLinearColor(0.012f, 0.013f, 0.015f, 0.94f));
	ContainerFill->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	ContainerStroke->SetContent(ContainerFill);
	UCanvasPanel* ContainerBody = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
	ContainerBody->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	ContainerFill->SetContent(ContainerBody);
	ContainerFrame->AddChild(ContainerStroke);
	SetCanvasRect(ContainerStroke, 0.0f, 16.0f, 460.0f, 684.0f, 0);

	UBorder* NameStroke = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
	NameStroke->SetBrushColor(FLinearColor(0.78f, 0.8f, 0.84f, 0.95f));
	NameStroke->SetPadding(FMargin(1.0f));
	NameStroke->SetVisibility(ESlateVisibility::HitTestInvisible);
	UBorder* NameFill = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
	NameFill->SetBrushColor(FLinearColor(0.02f, 0.022f, 0.026f, 1.0f));
	NameFill->SetPadding(FMargin(12.0f, 4.0f));
	NameFill->SetVisibility(ESlateVisibility::HitTestInvisible);
	NameStroke->SetContent(NameFill);
	ContainerTitle = MakeLabel(WidgetTree, MakeInventoryFont(14), FLinearColor(0.94f, 0.94f, 0.96f, 1.0f));
	ContainerTitle->SetText(NSLOCTEXT("ProjectEX", "DefaultContainerName", "Searched Container"));
	ContainerTitle->SetJustification(ETextJustify::Center);
	ContainerTitle->SetTextOverflowPolicy(ETextOverflowPolicy::Ellipsis);
	NameFill->SetContent(ContainerTitle);
	ContainerFrame->AddChild(NameStroke);
	SetCanvasRect(NameStroke, 70.0f, 0.0f, 320.0f, 32.0f, 3);

	ContainerSizeBox = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());
	ContainerSizeBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	ContainerCanvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
	ContainerCanvas->SetVisibility(ESlateVisibility::Visible);
	ContainerSizeBox->SetContent(ContainerCanvas);
	ContainerBody->AddChild(ContainerSizeBox);
	SetCanvasRect(ContainerSizeBox, 36.0f, 48.0f, 388.0f, 220.0f, 1);

	ContainerColumn = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass());

	HintText = MakeLabel(WidgetTree, MakeInventoryFont(12), FLinearColor(0.72f, 0.74f, 0.78f, 1.0f));
	HintText->SetAutoWrapText(false);
	HintText->SetJustification(ETextJustify::Center);
	if (UVerticalBoxSlot* HintSlot = Outer->AddChildToVerticalBox(HintText))
	{
		HintSlot->SetPadding(FMargin(8.0f, 14.0f, 8.0f, 0.0f));
	}

	GhostItem = CreateWidget<UProjectEXInventoryItemWidget>(this, UProjectEXInventoryItemWidget::StaticClass());
	if (GhostItem)
	{
		GhostItem->SetVisibility(ESlateVisibility::Collapsed);
		if (UCanvasPanelSlot* GhostSlot = RootCanvas->AddChildToCanvas(GhostItem))
		{
			GhostSlot->SetAutoSize(false);
			GhostSlot->SetZOrder(20);
		}
	}

	ContextMenuBox = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass());
	ContextMenuBox->SetVisibility(ESlateVisibility::Collapsed);
	if (UCanvasPanelSlot* MenuSlot = RootCanvas->AddChildToCanvas(ContextMenuBox))
	{
		MenuSlot->SetAutoSize(true);
		MenuSlot->SetZOrder(30);
	}

	SetIsFocusable(false);
	UpdateHints();
}
void UProjectEXInventoryWidget::SetSearchedContainer(AProjectEXLootContainer* Container)
{
	if (AProjectEXLootContainer* Previous = SearchedContainer.Get())
	{
		Previous->OnContentsChanged.RemoveDynamic(this, &UProjectEXInventoryWidget::HandleContainerChanged);
	}

	SearchedContainer = Container;
	if (Container)
	{
		Container->OnContentsChanged.AddDynamic(this, &UProjectEXInventoryWidget::HandleContainerChanged);
	}

	if (ContainerPanel)
	{
		ContainerPanel->SetVisibility(Container ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
	}

	if (ContainerTitle)
	{
		ContainerTitle->SetText(Container ? Container->GetContainerName() : NSLOCTEXT("ProjectEX", "DefaultContainerName", "Container"));
	}

	RefreshContainer();
}

void UProjectEXInventoryWidget::RefreshContainer()
{
	if (!ContainerCanvas || !ContainerSizeBox)
	{
		return;
	}

	for (UBorder* Cell : ContainerCells)
	{
		if (Cell)
		{
			Cell->RemoveFromParent();
		}
	}
	ContainerCells.Reset();

	for (UProjectEXInventoryItemWidget* ItemWidget : ContainerItemWidgets)
	{
		if (ItemWidget)
		{
			ItemWidget->RemoveFromParent();
		}
	}
	ContainerItemWidgets.Reset();

	const AProjectEXLootContainer* Container = SearchedContainer.Get();
	if (!Container)
	{
		return;
	}

	const int32 Columns = Container->GetGridColumns();
	const int32 Rows = Container->GetGridRows();
	ContainerCellSize = FMath::Clamp(FMath::Min(380.0f / Columns, 210.0f / Rows), 28.0f, 46.0f);
	ContainerSizeBox->SetWidthOverride(Columns * ContainerCellSize);
	ContainerSizeBox->SetHeightOverride(Rows * ContainerCellSize);
	for (int32 Y = 0; Y < Rows; ++Y)
	{
		for (int32 X = 0; X < Columns; ++X)
		{
			UBorder* Cell = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
			Cell->SetBrushColor(FLinearColor(0.055f, 0.058f, 0.064f, 1.0f));
			Cell->SetVisibility(ESlateVisibility::HitTestInvisible);
			ContainerCanvas->AddChild(Cell);
			SetCanvasRect(Cell, X * ContainerCellSize + 1.0f, Y * ContainerCellSize + 1.0f, ContainerCellSize - 2.0f, ContainerCellSize - 2.0f, 0);
			ContainerCells.Add(Cell);
		}
	}

	for (const FProjectEXInventoryEntry& Entry : Container->GetEntries())
	{
		if (!Entry.Definition || Entry.Quantity <= 0)
		{
			continue;
		}

		UProjectEXInventoryItemWidget* ItemWidget = CreateWidget<UProjectEXInventoryItemWidget>(this, UProjectEXInventoryItemWidget::StaticClass());
		if (!ItemWidget)
		{
			continue;
		}

		ItemWidget->ApplyEntry(this, Entry, ContainerCellSize, false, EProjectEXDragOrigin::Container);
		ContainerCanvas->AddChild(ItemWidget);
		const FIntPoint Size = Entry.Definition->GetGridSize(Entry.bRotated);
		SetCanvasRect(ItemWidget, Entry.GridX * ContainerCellSize, Entry.GridY * ContainerCellSize, Size.X * ContainerCellSize, Size.Y * ContainerCellSize, 2);
		ContainerItemWidgets.Add(ItemWidget);
	}
}

void UProjectEXInventoryWidget::QuickTransfer(int32 EntryId, EProjectEXDragOrigin Origin)
{
	UProjectEXLootComponent* Loot = GetLoot();
	if (!Loot || !SearchedContainer.IsValid())
	{
		return;
	}

	if (Origin == EProjectEXDragOrigin::Pockets)
	{
		Loot->RequestDeposit(EntryId);
	}
	else if (Origin == EProjectEXDragOrigin::Container)
	{
		Loot->RequestTake(EntryId);
	}
}

void UProjectEXInventoryWidget::QuickEquip(int32 EntryId, EProjectEXDragOrigin Origin)
{
	if (Origin == EProjectEXDragOrigin::Pockets)
	{
		if (UProjectEXInventoryComponent* Inventory = BoundInventory.Get())
		{
			Inventory->RequestAutoEquip(EntryId);
		}
	}
	else if (Origin == EProjectEXDragOrigin::Container)
	{
		FProjectEXInventoryEntry Entry;
		UProjectEXInventoryComponent* Inventory = BoundInventory.Get();
		UProjectEXLootComponent* Loot = GetLoot();
		if (!Inventory || !Loot || !FindContainerEntry(EntryId, Entry) || !Entry.Definition)
		{
			return;
		}

		EProjectEXEquipmentSlot TargetSlot = EProjectEXEquipmentSlot::PrimaryWeapon;
		bool bFound = false;
		auto TrySlot = [&](EProjectEXEquipmentSlot Candidate, EProjectEXEquipKind Kind)
		{
			if (bFound || Entry.Definition->EquipKind != Kind)
			{
				return;
			}

			FProjectEXEquippedItem Worn;
			if (Inventory->GetEquippedItem(Candidate, Worn) && !Worn.IsOccupied())
			{
				TargetSlot = Candidate;
				bFound = true;
			}
		};

		TrySlot(EProjectEXEquipmentSlot::PrimaryWeapon, EProjectEXEquipKind::Weapon);
		TrySlot(EProjectEXEquipmentSlot::SecondaryWeapon, EProjectEXEquipKind::Weapon);
		TrySlot(EProjectEXEquipmentSlot::Helmet, EProjectEXEquipKind::Helmet);
		TrySlot(EProjectEXEquipmentSlot::BodyArmor, EProjectEXEquipKind::BodyArmor);
		TrySlot(EProjectEXEquipmentSlot::Backpack, EProjectEXEquipKind::Backpack);
		if (bFound)
		{
			Loot->RequestEquipContainerItem(EntryId, TargetSlot);
		}
	}
}

bool UProjectEXInventoryWidget::ConsumeDoubleClick(int32 ClickId, EProjectEXDragOrigin Origin)
{
	const double Now = FPlatformTime::Seconds();
	const bool bDouble = ClickId == LastClickId && Origin == LastClickOrigin && LastClickSeconds >= 0.0 && (Now - LastClickSeconds) <= 0.35;
	LastClickSeconds = bDouble ? -1.0 : Now;
	LastClickId = bDouble ? INDEX_NONE : ClickId;
	LastClickOrigin = Origin;
	return bDouble;
}

void UProjectEXInventoryWidget::ActivateItem(int32 EntryId, EProjectEXDragOrigin Origin)
{
	FProjectEXInventoryEntry Entry;
	const bool bFound = Origin == EProjectEXDragOrigin::Container ? FindContainerEntry(EntryId, Entry) : FindEntry(EntryId, Entry);
	if (!bFound || !Entry.Definition)
	{
		return;
	}

	if (Origin == EProjectEXDragOrigin::Pockets && Entry.Definition->HealAmount > 0.0f)
	{
		if (UProjectEXInventoryComponent* Inventory = BoundInventory.Get())
		{
			Inventory->RequestUseItem(EntryId);
		}
		return;
	}

	const UProjectEXInventoryComponent* Inventory = BoundInventory.Get();
	auto EmptySlot = [&](EProjectEXEquipmentSlot EquipmentSlot) -> bool
	{
		FProjectEXEquippedItem Worn;
		return Inventory && Inventory->GetEquippedItem(EquipmentSlot, Worn) && !Worn.IsOccupied();
	};

	bool bCanEquip = false;
	switch (Entry.Definition->EquipKind)
	{
	case EProjectEXEquipKind::Weapon:
		bCanEquip = EmptySlot(EProjectEXEquipmentSlot::PrimaryWeapon) || EmptySlot(EProjectEXEquipmentSlot::SecondaryWeapon);
		break;
	case EProjectEXEquipKind::Helmet:
		bCanEquip = EmptySlot(EProjectEXEquipmentSlot::Helmet);
		break;
	case EProjectEXEquipKind::BodyArmor:
		bCanEquip = EmptySlot(EProjectEXEquipmentSlot::BodyArmor);
		break;
	case EProjectEXEquipKind::Backpack:
		bCanEquip = EmptySlot(EProjectEXEquipmentSlot::Backpack);
		break;
	default:
		break;
	}

	if (bCanEquip)
	{
		QuickEquip(EntryId, Origin);
		return;
	}

	if (SearchedContainer.IsValid())
	{
		QuickTransfer(EntryId, Origin);
	}
}

void UProjectEXInventoryWidget::ActivateEquipped(EProjectEXEquipmentSlot EquipmentSlot)
{
	if (UProjectEXInventoryComponent* Inventory = BoundInventory.Get())
	{
		Inventory->RequestUnequip(EquipmentSlot);
	}
}

void UProjectEXInventoryWidget::ShowItemMenu(int32 EntryId, EProjectEXDragOrigin Origin, const FVector2D& ScreenPosition)
{
	CloseContextMenu();
	if (!ContextMenuBox || !RootCanvas || Origin == EProjectEXDragOrigin::Equipment)
	{
		return;
	}

	FProjectEXInventoryEntry Entry;
	const bool bFound = Origin == EProjectEXDragOrigin::Container ? FindContainerEntry(EntryId, Entry) : FindEntry(EntryId, Entry);
	if (!bFound || !Entry.Definition)
	{
		return;
	}

	ContextEntryId = EntryId;
	ContextOrigin = Origin;
	const UProjectEXInventoryComponent* Inventory = BoundInventory.Get();
	auto HasEmptySlot = [&](EProjectEXEquipKind Kind) -> bool
	{
		if (!Inventory)
		{
			return false;
		}

		auto Empty = [&](EProjectEXEquipmentSlot CandidateSlot) -> bool
		{
			FProjectEXEquippedItem Worn;
			return Inventory->GetEquippedItem(CandidateSlot, Worn) && !Worn.IsOccupied();
		};

		switch (Kind)
		{
		case EProjectEXEquipKind::Weapon:
			return Empty(EProjectEXEquipmentSlot::PrimaryWeapon) || Empty(EProjectEXEquipmentSlot::SecondaryWeapon);
		case EProjectEXEquipKind::Helmet:
			return Empty(EProjectEXEquipmentSlot::Helmet);
		case EProjectEXEquipKind::BodyArmor:
			return Empty(EProjectEXEquipmentSlot::BodyArmor);
		case EProjectEXEquipKind::Backpack:
			return Empty(EProjectEXEquipmentSlot::Backpack);
		default:
			return false;
		}
	};

	if (Origin == EProjectEXDragOrigin::Pockets && Entry.Definition->HealAmount > 0.0f)
	{
		AddContextAction(1, NSLOCTEXT("ProjectEX", "MenuUse", "Use"));
	}
	if (HasEmptySlot(Entry.Definition->EquipKind))
	{
		AddContextAction(2, NSLOCTEXT("ProjectEX", "MenuEquip", "Equip"));
	}
	if (Origin == EProjectEXDragOrigin::Pockets)
	{
		AddContextAction(3, NSLOCTEXT("ProjectEX", "MenuDrop", "Drop"));
	}

	if (ContextMenuBox->GetChildrenCount() == 0)
	{
		return;
	}

	const FVector2D Local = RootCanvas->GetCachedGeometry().AbsoluteToLocal(ScreenPosition);
	if (UCanvasPanelSlot* MenuSlot = Cast<UCanvasPanelSlot>(ContextMenuBox->Slot))
	{
		MenuSlot->SetPosition(Local);
		MenuSlot->SetAutoSize(true);
		MenuSlot->SetZOrder(30);
	}
	ContextMenuBox->SetVisibility(ESlateVisibility::Visible);
}

void UProjectEXInventoryWidget::ExecuteContextAction(int32 ActionId)
{
	const int32 EntryId = ContextEntryId;
	const EProjectEXDragOrigin Origin = ContextOrigin;
	CloseContextMenu();

	if (ActionId == 1 && Origin == EProjectEXDragOrigin::Pockets)
	{
		if (UProjectEXInventoryComponent* Inventory = BoundInventory.Get())
		{
			Inventory->RequestUseItem(EntryId);
		}
	}
	else if (ActionId == 2)
	{
		QuickEquip(EntryId, Origin);
	}
	else if (ActionId == 3 && Origin == EProjectEXDragOrigin::Pockets)
	{
		if (UProjectEXInventoryComponent* Inventory = BoundInventory.Get())
		{
			Inventory->RequestDropStack(EntryId);
		}
	}
}

void UProjectEXInventoryWidget::AddContextAction(int32 ActionId, const FText& Label)
{
	if (!ContextMenuBox)
	{
		return;
	}

	UBorder* Row = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
	Row->SetBrushColor(FLinearColor(0.08f, 0.07f, 0.06f, 0.98f));
	Row->SetPadding(FMargin(1.0f));
	UProjectEXContextActionButton* Button = WidgetTree->ConstructWidget<UProjectEXContextActionButton>(UProjectEXContextActionButton::StaticClass());
	Button->ActionId = ActionId;
	Button->OwnerWidget = this;
	Button->SetBackgroundColor(FLinearColor(0.2f, 0.17f, 0.13f, 1.0f));
	Button->OnClicked.AddDynamic(Button, &UProjectEXContextActionButton::HandleClicked);
	UTextBlock* Text = MakeLabel(WidgetTree, MakeInventoryFont(13), FLinearColor(0.92f, 0.9f, 0.82f, 1.0f));
	Text->SetText(Label);
	if (UButtonSlot* TextSlot = Cast<UButtonSlot>(Button->AddChild(Text)))
	{
		TextSlot->SetPadding(FMargin(12.0f, 6.0f));
	}
	Row->SetContent(Button);
	if (UVerticalBoxSlot* RowSlot = ContextMenuBox->AddChildToVerticalBox(Row))
	{
		RowSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 1.0f));
	}
}

void UProjectEXInventoryWidget::CloseContextMenu()
{
	if (!ContextMenuBox)
	{
		return;
	}

	ContextMenuBox->ClearChildren();
	ContextMenuBox->SetVisibility(ESlateVisibility::Collapsed);
}

bool UProjectEXInventoryWidget::FindDragEntry(FProjectEXInventoryEntry& OutEntry) const
{
	if (DragOrigin == EProjectEXDragOrigin::Container)
	{
		return FindContainerEntry(DragEntryId, OutEntry);
	}

	if (DragOrigin == EProjectEXDragOrigin::Equipment)
	{
		const UProjectEXInventoryComponent* Inventory = BoundInventory.Get();
		FProjectEXEquippedItem Item;
		if (!Inventory || !Inventory->GetEquippedItem(DragEquipmentSlot, Item) || !Item.IsOccupied() || !Item.Definition)
		{
			return false;
		}

		OutEntry = FProjectEXInventoryEntry();
		OutEntry.Definition = Item.Definition;
		OutEntry.Quantity = Item.Quantity;
		OutEntry.MagazineRounds = Item.MagazineRounds;
		return true;
	}

	return FindEntry(DragEntryId, OutEntry);
}

bool UProjectEXInventoryWidget::FindContainerEntry(int32 InEntryId, FProjectEXInventoryEntry& OutEntry) const
{
	const AProjectEXLootContainer* Container = SearchedContainer.Get();
	if (!Container)
	{
		return false;
	}

	for (const FProjectEXInventoryEntry& Entry : Container->GetEntries())
	{
		if (Entry.EntryId == InEntryId)
		{
			OutEntry = Entry;
			return true;
		}
	}

	return false;
}

UProjectEXEquipmentSlotWidget* UProjectEXInventoryWidget::FindEquipmentSlot(EProjectEXEquipmentSlot EquipmentSlot) const
{
	for (UProjectEXEquipmentSlotWidget* SlotWidget : EquipmentRows)
	{
		if (SlotWidget && SlotWidget->IsSlotEnabled() && SlotWidget->GetSlot() == EquipmentSlot)
		{
			return SlotWidget;
		}
	}

	return nullptr;
}

UProjectEXEquipmentSlotWidget* UProjectEXInventoryWidget::EquipmentSlotUnderCursor(const FVector2D& ScreenPosition) const
{
	for (UProjectEXEquipmentSlotWidget* SlotWidget : EquipmentRows)
	{
		if (SlotWidget && PointerOverWidget(SlotWidget, ScreenPosition))
		{
			return SlotWidget;
		}
	}

	return nullptr;
}

bool UProjectEXInventoryWidget::PointerOverWidget(const UWidget* Widget, const FVector2D& ScreenPosition) const
{
	if (!Widget)
	{
		return false;
	}

	const FGeometry& Geometry = Widget->GetCachedGeometry();
	const FVector2D Size = Geometry.GetLocalSize();
	return Size.X > 1.0f && Size.Y > 1.0f && Geometry.IsUnderLocation(ScreenPosition);
}

UProjectEXLootComponent* UProjectEXInventoryWidget::GetLoot() const
{
	const UProjectEXInventoryComponent* Inventory = BoundInventory.Get();
	const AActor* Owner = Inventory ? Inventory->GetOwner() : nullptr;
	return Owner ? Owner->FindComponentByClass<UProjectEXLootComponent>() : nullptr;
}

void UProjectEXInventoryWidget::HandleContainerChanged()
{
	RefreshContainer();
}

void UProjectEXInventoryWidget::RefreshEquipment()
{
	const UProjectEXInventoryComponent* Inventory = BoundInventory.Get();
	for (UProjectEXEquipmentSlotWidget* Row : EquipmentRows)
	{
		if (!Row)
		{
			continue;
		}

		FText Name;
		UTexture2D* Icon = nullptr;
		FProjectEXEquippedItem Item;
		if (Row->IsSlotEnabled() && Inventory && Inventory->GetEquippedItem(Row->GetSlot(), Item) && Item.IsOccupied() && Item.Definition)
		{
			Name = Item.Definition->DisplayName.IsEmpty() ? FText::FromName(Item.Definition->GetItemId()) : Item.Definition->DisplayName;
			if (Item.MagazineRounds >= 0)
			{
				Name = FText::Format(NSLOCTEXT("ProjectEX", "EquippedMagazine", "{0}  {1}"), Name, FText::AsNumber(Item.MagazineRounds));
			}
			Icon = Item.Definition->Icon.LoadSynchronous();
		}

		Row->SetOccupiedName(Name);
		Row->SetOccupiedIcon(Icon);
	}
}

void UProjectEXEquipmentSlotWidget::InitializeSlot(UProjectEXInventoryWidget* InOwner, EProjectEXEquipmentSlot InSlot, const FText& InLabel, bool bInEnabled)
{
	OwnerWidget = InOwner;
	Slot = InSlot;
	SlotLabel = InLabel;
	bEnabled = bInEnabled;
	OccupiedName = FText::GetEmpty();
	if (TitleText)
	{
		TitleText->SetText(SlotLabel);
	}
	if (NameText)
	{
		NameText->SetText(OccupiedName);
		NameText->SetVisibility(ESlateVisibility::Collapsed);
	}
	SetOccupiedIcon(nullptr);
	SetDropHighlight(false, false);
}

void UProjectEXEquipmentSlotWidget::SetOccupiedName(const FText& InName)
{
	OccupiedName = InName;
	if (NameText)
	{
		NameText->SetText(OccupiedName);
		NameText->SetVisibility(OccupiedName.IsEmpty() ? ESlateVisibility::Collapsed : ESlateVisibility::HitTestInvisible);
	}
}

void UProjectEXEquipmentSlotWidget::SetOccupiedIcon(UTexture2D* Texture)
{
	if (!IconImage || !IconBox)
	{
		return;
	}

	if (Texture)
	{
		IconImage->SetBrushFromTexture(Texture, true);
		IconBox->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		IconBox->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (NameText)
	{
		if (UWidget* Column = NameText->GetParent())
		{
			if (UOverlaySlot* TextSlot = Cast<UOverlaySlot>(Column->Slot))
			{
				TextSlot->SetPadding(Texture ? FMargin(2.0f, 2.0f, 28.0f, 2.0f) : FMargin(2.0f));
			}
		}
	}
}

void UProjectEXEquipmentSlotWidget::SetDropHighlight(bool bActive, bool bValid)
{
	bHighlightActive = bActive;
	bHighlightValid = bValid;
	if (!Face)
	{
		return;
	}

	if (!bEnabled)
	{
		Face->SetBrushColor(FLinearColor(0.07f, 0.07f, 0.07f, 0.8f));
		return;
	}

	if (bHighlightActive)
	{
		Face->SetBrushColor(bValid
			? FLinearColor(0.16f, 0.42f, 0.2f, 1.0f)
			: FLinearColor(0.5f, 0.14f, 0.12f, 1.0f));
		return;
	}

	Face->SetBrushColor(FLinearColor(0.03f, 0.032f, 0.036f, 1.0f));
}

TSharedRef<SWidget> UProjectEXEquipmentSlotWidget::RebuildWidget()
{
	if (WidgetTree && !WidgetTree->RootWidget)
	{
		UBorder* Stroke = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
		Stroke->SetPadding(FMargin(1.0f));
		Stroke->SetClipping(EWidgetClipping::ClipToBounds);
		Stroke->SetBrushColor(FLinearColor(0.72f, 0.74f, 0.78f, 0.9f));
		WidgetTree->RootWidget = Stroke;

		Face = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
		Face->SetPadding(FMargin(6.0f, 4.0f));
		Face->SetClipping(EWidgetClipping::ClipToBounds);
		Face->SetBrushColor(FLinearColor(0.03f, 0.032f, 0.036f, 1.0f));
		Stroke->SetContent(Face);

		UOverlay* Overlay = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass());
		Overlay->SetVisibility(ESlateVisibility::HitTestInvisible);
		Face->SetContent(Overlay);

		UVerticalBox* Column = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass());
		Column->SetVisibility(ESlateVisibility::HitTestInvisible);
		if (UOverlaySlot* TextSlot = Overlay->AddChildToOverlay(Column))
		{
			TextSlot->SetHorizontalAlignment(HAlign_Fill);
			TextSlot->SetVerticalAlignment(VAlign_Center);
			TextSlot->SetPadding(FMargin(2.0f));
		}

		TitleText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		TitleText->SetFont(FCoreStyle::GetDefaultFontStyle(TEXT("Regular"), 11));
		TitleText->SetColorAndOpacity(FSlateColor(FLinearColor(0.9f, 0.9f, 0.92f, 1.0f)));
		TitleText->SetText(SlotLabel);
		TitleText->SetJustification(ETextJustify::Center);
		TitleText->SetAutoWrapText(true);
		TitleText->SetTextOverflowPolicy(ETextOverflowPolicy::Ellipsis);
		TitleText->SetClipping(EWidgetClipping::ClipToBounds);
		TitleText->SetVisibility(ESlateVisibility::HitTestInvisible);
		Column->AddChildToVerticalBox(TitleText);

		NameText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		NameText->SetFont(FCoreStyle::GetDefaultFontStyle(TEXT("Regular"), 10));
		NameText->SetColorAndOpacity(FSlateColor(FLinearColor(0.78f, 0.84f, 0.74f, 1.0f)));
		NameText->SetText(OccupiedName);
		NameText->SetJustification(ETextJustify::Center);
		NameText->SetAutoWrapText(false);
		NameText->SetTextOverflowPolicy(ETextOverflowPolicy::Ellipsis);
		NameText->SetClipping(EWidgetClipping::ClipToBounds);
		NameText->SetVisibility(OccupiedName.IsEmpty() ? ESlateVisibility::Collapsed : ESlateVisibility::HitTestInvisible);
		Column->AddChildToVerticalBox(NameText);

		IconBox = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());
		IconBox->SetWidthOverride(26.0f);
		IconBox->SetHeightOverride(26.0f);
		IconBox->SetVisibility(ESlateVisibility::Collapsed);
		IconImage = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
		IconImage->SetVisibility(ESlateVisibility::HitTestInvisible);
		IconBox->SetContent(IconImage);
		if (UOverlaySlot* IconSlot = Overlay->AddChildToOverlay(IconBox))
		{
			IconSlot->SetHorizontalAlignment(HAlign_Right);
			IconSlot->SetVerticalAlignment(VAlign_Center);
		}

		SetVisibility(ESlateVisibility::Visible);
	}

	SetDropHighlight(bHighlightActive, bHighlightValid);
	return Super::RebuildWidget();
}

FReply UProjectEXEquipmentSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!bEnabled || !OwnerWidget.IsValid() || InMouseEvent.GetEffectingButton() != EKeys::LeftMouseButton)
	{
		return FReply::Handled();
	}

	const FModifierKeysState Modifiers = FSlateApplication::Get().GetModifierKeys();
	if (Modifiers.IsShiftDown() || Modifiers.IsControlDown())
	{
		return FReply::Handled();
	}

	if (OwnerWidget->ConsumeDoubleClick(1000 + static_cast<int32>(Slot), EProjectEXDragOrigin::Equipment))
	{
		OwnerWidget->ActivateEquipped(Slot);
		return FReply::Handled();
	}

	OwnerWidget->BeginEquippedPointer(Slot, InMouseEvent.GetScreenSpacePosition(), InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition()));
	return FReply::Handled().CaptureMouse(TakeWidget());
}

FReply UProjectEXEquipmentSlotWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (HasMouseCapture() && OwnerWidget.IsValid())
	{
		OwnerWidget->UpdateItemPointer(InMouseEvent.GetScreenSpacePosition());
		return FReply::Handled();
	}

	return FReply::Unhandled();
}

FReply UProjectEXEquipmentSlotWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && OwnerWidget.IsValid())
	{
		OwnerWidget->EndItemPointer(InMouseEvent.GetScreenSpacePosition());
	}

	return FReply::Handled().ReleaseMouseCapture();
}

void UProjectEXEquipmentSlotWidget::NativeOnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent)
{
	Super::NativeOnMouseCaptureLost(CaptureLostEvent);
	if (OwnerWidget.IsValid())
	{
		OwnerWidget->CancelDrag();
	}
}

void UProjectEXContextActionButton::HandleClicked()
{
	if (UProjectEXInventoryWidget* Owner = OwnerWidget.Get())
	{
		Owner->ExecuteContextAction(ActionId);
	}
}

