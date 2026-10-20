// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXInventoryWidget.h"
#include "ProjectEXInventoryComponent.h"
#include "ProjectEXItemDefinition.h"
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

void UProjectEXInventoryItemWidget::ApplyEntry(UProjectEXInventoryWidget* InOwner, const FProjectEXInventoryEntry& Entry, float InCellSize, bool bInSelected)
{
	OwnerWidget = InOwner;
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
	if (InMouseEvent.GetEffectingButton() != EKeys::LeftMouseButton || !OwnerWidget.IsValid())
	{
		return FReply::Handled();
	}

	const FVector2D LocalGrab = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	OwnerWidget->BeginItemPointer(EntryId, InMouseEvent.GetScreenSpacePosition(), LocalGrab);
	return FReply::Handled().CaptureMouse(TakeWidget());
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
	InnerBorder->SetPadding(FMargin(4.0f));
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

	NameText = MakeLabel(WidgetTree, MakeInventoryFont(11), FLinearColor(0.92f, 0.92f, 0.9f, 1.0f));
	NameText->SetJustification(ETextJustify::Left);
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
	const bool bShowName = ShownWidth * CellSize >= 96.0f;
	if (NameText)
	{
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
		if (ShortName.Len() > 4)
		{
			ShortName = ShortName.Left(3);
		}
		InitialsText->SetText(FText::FromString(ShortName.ToUpper()));
		InitialsText->SetVisibility(bHasIcon ? ESlateVisibility::Collapsed : ESlateVisibility::HitTestInvisible);
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
		QuantityText->SetText(FText::AsNumber(FMath::Max(0, Quantity)));
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
	if (!FindEntry(DragEntryId, Entry) || !Entry.Definition)
	{
		CancelDrag();
		return;
	}

	const FIntPoint OldSize = Entry.Definition->GetGridSize(bDragRotated);
	const FVector2D OldGrab = DragGrabOffset;
	bDragRotated = !bDragRotated;
	const FIntPoint NewSize = Entry.Definition->GetGridSize(bDragRotated);
	const float NewWidth = NewSize.X * CellSize;
	const float NewHeight = NewSize.Y * CellSize;
	DragGrabOffset.X = FMath::Clamp(OldGrab.Y, 0.0f, FMath::Max(1.0f, NewWidth - 1.0f));
	DragGrabOffset.Y = FMath::Clamp((OldSize.X * CellSize) - OldGrab.X, 0.0f, FMath::Max(1.0f, NewHeight - 1.0f));
	UpdateDragVisual(LastScreenPosition);
}

void UProjectEXInventoryWidget::BeginItemPointer(int32 EntryId, const FVector2D& ScreenPosition, const FVector2D& LocalGrabOffset)
{
	FProjectEXInventoryEntry Entry;
	if (!FindEntry(EntryId, Entry))
	{
		return;
	}

	DragEpochAtPointer = DragEpoch;
	DragEntryId = EntryId;
	DragGrabOffset = LocalGrabOffset;
	PointerStartScreen = ScreenPosition;
	LastScreenPosition = ScreenPosition;
	bDragRotated = Entry.bRotated;
	bPointerDown = true;
	bDragActive = false;
	bDragPreviewValid = false;
	SelectedEntryId = EntryId;
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
		SelectedEntryId = EntryId;
		for (UProjectEXInventoryItemWidget* ItemWidget : ItemWidgets)
		{
			if (ItemWidget)
			{
				ItemWidget->SetSelected(ItemWidget->GetEntryId() == SelectedEntryId);
				ItemWidget->SetRenderOpacity(1.0f);
			}
		}

		if (DropButton)
		{
			DropButton->SetIsEnabled(SelectedEntryId != INDEX_NONE);
		}
		return;
	}

	FProjectEXInventoryEntry Entry;
	const bool bFound = FindEntry(EntryId, Entry);
	const bool bOutsideInventory = !IsPointerInsideInventory(ScreenPosition);
	const bool bSamePlace = bFound && Entry.GridX == PreviewX && Entry.GridY == PreviewY && Entry.bRotated == bRotated;
	if (UProjectEXInventoryComponent* Inventory = BoundInventory.Get())
	{
		if (bFound && bOutsideInventory)
		{
			Inventory->RequestDropStack(EntryId);
		}
		else if (bFound && bValidPreview && !bSamePlace)
		{
			Inventory->RequestMoveItem(EntryId, PreviewX, PreviewY, bRotated);
		}
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

		if (DropButton)
		{
			DropButton->SetIsEnabled(false);
		}
	}

	return FReply::Handled();
}

void UProjectEXInventoryWidget::BuildLayout()
{
	RootCanvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
	RootCanvas->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	WidgetTree->RootWidget = RootCanvas;

	UBorder* Dimmer = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
	Dimmer->SetBrushColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.45f));
	Dimmer->SetVisibility(ESlateVisibility::Visible);
	if (UCanvasPanelSlot* DimSlot = RootCanvas->AddChildToCanvas(Dimmer))
	{
		DimSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
		DimSlot->SetOffsets(FMargin(0.0f));
		DimSlot->SetZOrder(0);
	}

	USizeBox* PanelSize = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());
	PanelSize->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	if (UCanvasPanelSlot* PanelSlot = RootCanvas->AddChildToCanvas(PanelSize))
	{
		PanelSlot->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
		PanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
		PanelSlot->SetAutoSize(true);
		PanelSlot->SetZOrder(1);
	}

	UBorder* Frame = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
	Frame->SetBrushColor(FLinearColor(0.05f, 0.06f, 0.07f, 0.96f));
	Frame->SetPadding(FMargin(16.0f));
	Frame->SetVisibility(ESlateVisibility::Visible);
	PanelSize->SetContent(Frame);
	InventoryFrame = Frame;

	UVerticalBox* Column = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass());
	Column->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	Frame->SetContent(Column);

	UHorizontalBox* Header = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
	Header->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	if (UVerticalBoxSlot* HeaderSlot = Column->AddChildToVerticalBox(Header))
	{
		HeaderSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 10.0f));
	}

	UTextBlock* Title = MakeLabel(WidgetTree, MakeInventoryFont(22), FLinearColor(0.93f, 0.91f, 0.84f, 1.0f));
	Title->SetText(NSLOCTEXT("ProjectEX", "InventoryTitle", "INVENTORY"));
	Header->AddChildToHorizontalBox(Title);

	USpacer* HeaderSpacer = WidgetTree->ConstructWidget<USpacer>(USpacer::StaticClass());
	if (UHorizontalBoxSlot* SpacerSlot = Header->AddChildToHorizontalBox(HeaderSpacer))
	{
		SpacerSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	}

	CapacityText = MakeLabel(WidgetTree, MakeInventoryFont(14), FLinearColor(0.75f, 0.75f, 0.72f, 1.0f));
	if (UHorizontalBoxSlot* CapacitySlot = Header->AddChildToHorizontalBox(CapacityText))
	{
		CapacitySlot->SetVerticalAlignment(VAlign_Center);
		CapacitySlot->SetPadding(FMargin(16.0f, 0.0f, 12.0f, 0.0f));
	}

	UProjectEXInventoryButton* CloseButton = WidgetTree->ConstructWidget<UProjectEXInventoryButton>(UProjectEXInventoryButton::StaticClass());
	CloseButton->SetBackgroundColor(FLinearColor(0.16f, 0.17f, 0.18f, 1.0f));
	CloseButton->OnClicked.AddDynamic(this, &UProjectEXInventoryWidget::HandleCloseClicked);
	UTextBlock* CloseLabel = MakeLabel(WidgetTree, MakeInventoryFont(14), FLinearColor::White);
	CloseLabel->SetText(NSLOCTEXT("ProjectEX", "InventoryClose", "Close"));
	CloseLabel->SetVisibility(ESlateVisibility::HitTestInvisible);
	if (UButtonSlot* CloseSlot = Cast<UButtonSlot>(CloseButton->AddChild(CloseLabel)))
	{
		CloseSlot->SetPadding(FMargin(12.0f, 6.0f));
	}
	Header->AddChildToHorizontalBox(CloseButton);

	GridSizeBox = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());
	GridSizeBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	if (UVerticalBoxSlot* GridSlot = Column->AddChildToVerticalBox(GridSizeBox))
	{
		GridSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 10.0f));
	}

	GridCanvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
	GridCanvas->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	GridSizeBox->SetContent(GridCanvas);

	UHorizontalBox* Footer = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
	Footer->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	Column->AddChildToVerticalBox(Footer);

	HintText = MakeLabel(WidgetTree, MakeInventoryFont(12), FLinearColor(0.68f, 0.68f, 0.64f, 1.0f));
	HintText->SetAutoWrapText(true);
	if (UHorizontalBoxSlot* HintSlot = Footer->AddChildToHorizontalBox(HintText))
	{
		HintSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
		HintSlot->SetVerticalAlignment(VAlign_Center);
		HintSlot->SetPadding(FMargin(0.0f, 0.0f, 12.0f, 0.0f));
	}

	DropButton = WidgetTree->ConstructWidget<UProjectEXInventoryButton>(UProjectEXInventoryButton::StaticClass());
	DropButton->SetBackgroundColor(FLinearColor(0.28f, 0.2f, 0.12f, 1.0f));
	DropButton->OnClicked.AddDynamic(this, &UProjectEXInventoryWidget::HandleDropClicked);
	DropButton->SetIsEnabled(false);
	UTextBlock* DropLabel = MakeLabel(WidgetTree, MakeInventoryFont(14), FLinearColor::White);
	DropLabel->SetText(NSLOCTEXT("ProjectEX", "InventoryDropOne", "Drop one"));
	DropLabel->SetVisibility(ESlateVisibility::HitTestInvisible);
	if (UButtonSlot* DropSlot = Cast<UButtonSlot>(DropButton->AddChild(DropLabel)))
	{
		DropSlot->SetPadding(FMargin(12.0f, 6.0f));
	}
	Footer->AddChildToHorizontalBox(DropButton);

	GhostItem = CreateWidget<UProjectEXInventoryItemWidget>(this, UProjectEXInventoryItemWidget::StaticClass());
	if (GhostItem)
	{
		GhostItem->SetVisibility(ESlateVisibility::Collapsed);
		if (UCanvasPanelSlot* GhostSlot = RootCanvas->AddChildToCanvas(GhostItem))
		{
			GhostSlot->SetAutoSize(false);
			GhostSlot->SetZOrder(10);
		}
	}

	SetIsFocusable(false);
	UpdateHints();
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

	if (LaidOutColumns != Columns || LaidOutRows != Rows || LaidOutCellSize != CellSize)
	{
		for (UBorder* Cell : CellBorders)
		{
			if (Cell)
			{
				Cell->RemoveFromParent();
			}
		}
		CellBorders.Reset();

		for (int32 Y = 0; Y < Rows; ++Y)
		{
			for (int32 X = 0; X < Columns; ++X)
			{
				UBorder* Cell = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
				Cell->SetBrushColor(FLinearColor(0.11f, 0.12f, 0.13f, 1.0f));
				Cell->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				GridCanvas->AddChild(Cell);
				SetCanvasRect(Cell, X * CellSize + 1.0f, Y * CellSize + 1.0f, CellSize - 2.0f, CellSize - 2.0f, 0);
				CellBorders.Add(Cell);
			}
		}

		LaidOutColumns = Columns;
		LaidOutRows = Rows;
		LaidOutCellSize = CellSize;
	}

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

		ItemWidget->ApplyEntry(this, Entry, CellSize, Entry.EntryId == SelectedEntryId);
		GridCanvas->AddChild(ItemWidget);
		const FIntPoint Size = Entry.Definition->GetGridSize(Entry.bRotated);
		SetCanvasRect(ItemWidget, Entry.GridX * CellSize, Entry.GridY * CellSize, Size.X * CellSize, Size.Y * CellSize, 2);
		ItemWidgets.Add(ItemWidget);
	}

	if (!bSelectionStillValid)
	{
		SelectedEntryId = INDEX_NONE;
	}

	if (DropButton)
	{
		DropButton->SetIsEnabled(SelectedEntryId != INDEX_NONE);
	}

	const int32 UsedCells = Inventory ? Inventory->GetOccupiedCellCount() : 0;
	const int32 TotalCells = Columns * Rows;
	CapacityText->SetText(FText::Format(
		NSLOCTEXT("ProjectEX", "InventoryGridCapacity", "{0} / {1}"),
		FText::AsNumber(UsedCells),
		FText::AsNumber(TotalCells)));

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
		NSLOCTEXT("ProjectEX", "InventoryGridHint", "{0} closes. {1} rotates. Drag an item off the inventory to drop the stack."),
		ToggleName,
		RotateName));
}

void UProjectEXInventoryWidget::UpdateDragVisual(const FVector2D& ScreenPosition)
{
	LastScreenPosition = ScreenPosition;
	if (!bDragActive || !GridCanvas || !RootCanvas || !GhostItem || CellSize <= 0)
	{
		return;
	}

	FProjectEXInventoryEntry Entry;
	if (!FindEntry(DragEntryId, Entry) || !Entry.Definition)
	{
		CancelDrag();
		return;
	}

	FProjectEXInventoryEntry GhostEntry = Entry;
	GhostEntry.bRotated = bDragRotated;
	GhostItem->ApplyEntry(this, GhostEntry, CellSize, false);
	GhostItem->SetVisibility(ESlateVisibility::HitTestInvisible);

	const FIntPoint Size = Entry.Definition->GetGridSize(bDragRotated);
	const FVector2D GhostSize(Size.X * CellSize, Size.Y * CellSize);
	const FVector2D RootLocal = RootCanvas->GetCachedGeometry().AbsoluteToLocal(ScreenPosition);
	SetCanvasRect(GhostItem, RootLocal.X - DragGrabOffset.X, RootLocal.Y - DragGrabOffset.Y, GhostSize.X, GhostSize.Y, 10);

	if (!IsPointerInsideInventory(ScreenPosition))
	{
		bDragPreviewValid = false;
		HideHighlight();
		return;
	}

	const FVector2D GridLocal = GridCanvas->GetCachedGeometry().AbsoluteToLocal(ScreenPosition);
	const FVector2D TopLeft = GridLocal - DragGrabOffset;
	DragPreviewX = FMath::FloorToInt((TopLeft.X + 0.01f) / CellSize);
	DragPreviewY = FMath::FloorToInt((TopLeft.Y + 0.01f) / CellSize);

	const UProjectEXInventoryComponent* Inventory = BoundInventory.Get();
	bDragPreviewValid = Inventory && Inventory->CanPlaceEntry(DragEntryId, DragPreviewX, DragPreviewY, bDragRotated);
	ShowHighlight(DragPreviewX, DragPreviewY, Size.X, Size.Y, bDragPreviewValid);
}

void UProjectEXInventoryWidget::ShowHighlight(int32 OriginX, int32 OriginY, int32 Width, int32 Height, bool bValid)
{
	const UProjectEXInventoryComponent* Inventory = BoundInventory.Get();
	const int32 Columns = Inventory ? Inventory->GetGridColumns() : LaidOutColumns;
	const int32 Rows = Inventory ? Inventory->GetGridRows() : LaidOutRows;
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

			UBorder* Highlight = GetHighlightCell(Used);
			++Used;
			if (!Highlight)
			{
				continue;
			}

			Highlight->SetBrushColor(Color);
			Highlight->SetVisibility(ESlateVisibility::HitTestInvisible);
			SetCanvasRect(Highlight, X * CellSize, Y * CellSize, CellSize, CellSize, 4);
		}
	}

	for (int32 Index = Used; Index < HighlightCells.Num(); ++Index)
	{
		if (HighlightCells[Index])
		{
			HighlightCells[Index]->SetVisibility(ESlateVisibility::Collapsed);
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
}

void UProjectEXInventoryWidget::HideGhost()
{
	if (GhostItem)
	{
		GhostItem->SetVisibility(ESlateVisibility::Collapsed);
	}
}

bool UProjectEXInventoryWidget::IsPointerInsideInventory(const FVector2D& ScreenPosition) const
{
	if (!InventoryFrame)
	{
		return true;
	}

	const FGeometry& FrameGeometry = InventoryFrame->GetCachedGeometry();
	const FVector2D FrameSize = FrameGeometry.GetLocalSize();
	if (FrameSize.X < 1.0f || FrameSize.Y < 1.0f)
	{
		return true;
	}

	return FrameGeometry.IsUnderLocation(ScreenPosition);
}

int32 UProjectEXInventoryWidget::ComputeCellSize() const
{
	const UProjectEXInventoryComponent* Inventory = BoundInventory.Get();
	const int32 Columns = FMath::Max(1, Inventory ? Inventory->GetGridColumns() : 10);
	const int32 Rows = FMath::Max(1, Inventory ? Inventory->GetGridRows() : 6);

	FVector2D Viewport = UWidgetLayoutLibrary::GetViewportWidgetGeometry(this).GetLocalSize();
	if (Viewport.X < 64.0f || Viewport.Y < 64.0f)
	{
		if (const APlayerController* PlayerController = GetOwningPlayer())
		{
			int32 SizeX = 0;
			int32 SizeY = 0;
			PlayerController->GetViewportSize(SizeX, SizeY);
			const float Scale = FMath::Max(UWidgetLayoutLibrary::GetViewportScale(this), 0.01f);
			Viewport = FVector2D(SizeX / Scale, SizeY / Scale);
		}
	}

	if (Viewport.X < 64.0f || Viewport.Y < 64.0f)
	{
		Viewport = FVector2D(1920.0f, 1080.0f);
	}

	const float Fit = FMath::Min((Viewport.X * 0.52f) / Columns, (Viewport.Y * 0.62f) / Rows);
	return FMath::Clamp(FMath::FloorToInt(Fit), 36, 112);
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

	return nullptr;
}

UBorder* UProjectEXInventoryWidget::GetHighlightCell(int32 Index)
{
	if (!GridCanvas || !WidgetTree)
	{
		return nullptr;
	}

	while (HighlightCells.Num() <= Index)
	{
		UBorder* Highlight = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
		Highlight->SetVisibility(ESlateVisibility::Collapsed);
		GridCanvas->AddChild(Highlight);
		HighlightCells.Add(Highlight);
	}

	return HighlightCells[Index];
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

void UProjectEXInventoryWidget::HandleDropClicked()
{
	if (SelectedEntryId == INDEX_NONE)
	{
		return;
	}

	if (UProjectEXInventoryComponent* Inventory = BoundInventory.Get())
	{
		Inventory->RequestDrop(SelectedEntryId);
	}
}
