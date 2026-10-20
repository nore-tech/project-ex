// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXInventoryWidget.h"
#include "ProjectEXInventoryComponent.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Styling/CoreStyle.h"
#include "TimerManager.h"

namespace
{
	FSlateFontInfo MakeInventoryFont(int32 Size)
	{
		return FCoreStyle::GetDefaultFontStyle(TEXT("Regular"), Size);
	}
}

void UProjectEXInventorySlotWidget::Setup(int32 InEntryId, const FText& InLabel, bool bInSelected)
{
	EntryId = InEntryId;
	Label = InLabel;
	bSelected = bInSelected;
	ApplyPresentation();
}

void UProjectEXInventorySlotWidget::SetSelected(bool bInSelected)
{
	bSelected = bInSelected;
	ApplyPresentation();
}

TSharedRef<SWidget> UProjectEXInventorySlotWidget::RebuildWidget()
{
	if (WidgetTree && !WidgetTree->RootWidget)
	{
		Button = WidgetTree->ConstructWidget<UProjectEXInventoryButton>(UProjectEXInventoryButton::StaticClass(), TEXT("SlotButton"));
		Button->OnClicked.AddDynamic(this, &UProjectEXInventorySlotWidget::HandleClicked);
		WidgetTree->RootWidget = Button;

		LabelText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("SlotLabel"));
		LabelText->SetFont(MakeInventoryFont(16));
		LabelText->SetColorAndOpacity(FSlateColor(FLinearColor::White));
		LabelText->SetJustification(ETextJustify::Left);

		if (UButtonSlot* ButtonSlot = Cast<UButtonSlot>(Button->AddChild(LabelText)))
		{
			ButtonSlot->SetHorizontalAlignment(HAlign_Left);
			ButtonSlot->SetVerticalAlignment(VAlign_Center);
			ButtonSlot->SetPadding(FMargin(8.0f, 6.0f));
		}

		ApplyPresentation();
	}

	return Super::RebuildWidget();
}

void UProjectEXInventorySlotWidget::ApplyPresentation()
{
	if (LabelText)
	{
		LabelText->SetText(Label);
	}

	if (Button)
	{
		const FLinearColor Color = bSelected
			? FLinearColor(0.22f, 0.42f, 0.26f, 1.0f)
			: FLinearColor(0.14f, 0.14f, 0.14f, 1.0f);
		Button->SetBackgroundColor(Color);
	}
}

void UProjectEXInventorySlotWidget::HandleClicked()
{
	OnSlotClicked.Broadcast(EntryId);
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

void UProjectEXInventoryWidget::SetToggleKey(const FKey& InKey)
{
	ToggleKey = InKey;

	if (HintText)
	{
		HintText->SetText(FText::Format(
			NSLOCTEXT("ProjectEX", "InventoryHint", "{0} closes inventory"),
			ToggleKey.GetDisplayName()));
	}
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
	if (UProjectEXInventoryComponent* Inventory = BoundInventory.Get())
	{
		Inventory->OnInventoryChanged.RemoveDynamic(this, &UProjectEXInventoryWidget::HandleInventoryChanged);
	}

	Super::NativeDestruct();
}

void UProjectEXInventoryWidget::BuildLayout()
{
	UCanvasPanel* Canvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("Canvas"));
	Canvas->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	WidgetTree->RootWidget = Canvas;

	USizeBox* PanelSize = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass(), TEXT("PanelSize"));
	PanelSize->SetWidthOverride(380.0f);
	PanelSize->SetHeightOverride(460.0f);

	if (UCanvasPanelSlot* PanelSlot = Canvas->AddChildToCanvas(PanelSize))
	{
		PanelSlot->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
		PanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
		PanelSlot->SetAutoSize(true);
	}

	UBorder* Frame = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass(), TEXT("Frame"));
	Frame->SetBrushColor(FLinearColor(0.03f, 0.03f, 0.03f, 0.92f));
	Frame->SetPadding(FMargin(12.0f));
	PanelSize->SetContent(Frame);

	UVerticalBox* Column = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass(), TEXT("Column"));
	Frame->SetContent(Column);

	UTextBlock* Title = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("Title"));
	Title->SetText(NSLOCTEXT("ProjectEX", "InventoryTitle", "Inventory"));
	Title->SetFont(MakeInventoryFont(24));
	Title->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	Column->AddChildToVerticalBox(Title);

	CapacityText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("Capacity"));
	CapacityText->SetFont(MakeInventoryFont(14));
	CapacityText->SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.8f, 0.8f)));
	if (UVerticalBoxSlot* CapacitySlot = Column->AddChildToVerticalBox(CapacityText))
	{
		CapacitySlot->SetPadding(FMargin(0.0f, 4.0f, 0.0f, 8.0f));
	}

	ItemList = WidgetTree->ConstructWidget<UScrollBox>(UScrollBox::StaticClass(), TEXT("ItemList"));
	if (UVerticalBoxSlot* ListSlot = Column->AddChildToVerticalBox(ItemList))
	{
		ListSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
		ListSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 8.0f));
	}

	DropButton = WidgetTree->ConstructWidget<UProjectEXInventoryButton>(UProjectEXInventoryButton::StaticClass(), TEXT("DropButton"));
	DropButton->OnClicked.AddDynamic(this, &UProjectEXInventoryWidget::HandleDropClicked);

	UTextBlock* DropLabel = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("DropLabel"));
	DropLabel->SetText(NSLOCTEXT("ProjectEX", "InventoryDrop", "Drop"));
	DropLabel->SetFont(MakeInventoryFont(16));
	DropLabel->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	DropLabel->SetJustification(ETextJustify::Center);
	if (UButtonSlot* DropSlot = Cast<UButtonSlot>(DropButton->AddChild(DropLabel)))
	{
		DropSlot->SetPadding(FMargin(8.0f, 6.0f));
	}
	Column->AddChildToVerticalBox(DropButton);

	HintText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("Hint"));
	HintText->SetFont(MakeInventoryFont(12));
	HintText->SetColorAndOpacity(FSlateColor(FLinearColor(0.7f, 0.7f, 0.7f)));
	if (UVerticalBoxSlot* HintSlot = Column->AddChildToVerticalBox(HintText))
	{
		HintSlot->SetPadding(FMargin(0.0f, 8.0f, 0.0f, 0.0f));
	}

	SetIsFocusable(false);
	SetToggleKey(ToggleKey);
}

void UProjectEXInventoryWidget::Refresh()
{
	if (!ItemList || !CapacityText)
	{
		return;
	}

	const UProjectEXInventoryComponent* Inventory = BoundInventory.Get();
	const TArray<FProjectEXInventoryEntry> Entries = Inventory ? Inventory->GetEntries() : TArray<FProjectEXInventoryEntry>();

	bool bSelectionStillValid = false;
	for (const FProjectEXInventoryEntry& Entry : Entries)
	{
		if (Entry.EntryId == SelectedEntryId)
		{
			bSelectionStillValid = true;
			break;
		}
	}

	if (!bSelectionStillValid)
	{
		SelectedEntryId = INDEX_NONE;
	}

	CapacityText->SetText(FText::Format(
		NSLOCTEXT("ProjectEX", "InventoryCapacity", "Slots {0} / {1}"),
		FText::AsNumber(Inventory ? Inventory->GetUsedSlotCount() : 0),
		FText::AsNumber(Inventory ? Inventory->GetMaxSlotCount() : 0)));

	ItemList->ClearChildren();

	if (Entries.Num() == 0)
	{
		UTextBlock* EmptyText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("EmptyText"));
		EmptyText->SetText(NSLOCTEXT("ProjectEX", "InventoryEmpty", "No items"));
		EmptyText->SetFont(MakeInventoryFont(16));
		EmptyText->SetColorAndOpacity(FSlateColor(FLinearColor(0.75f, 0.75f, 0.75f)));
		ItemList->AddChild(EmptyText);
	}

	for (const FProjectEXInventoryEntry& Entry : Entries)
	{
		FText ItemName = NSLOCTEXT("ProjectEX", "UnknownItem", "Unknown item");
		if (Entry.Definition)
		{
			ItemName = Entry.Definition->DisplayName.IsEmpty()
				? FText::FromName(Entry.Definition->GetItemId())
				: Entry.Definition->DisplayName;
		}

		const FText RowLabel = FText::Format(
			NSLOCTEXT("ProjectEX", "InventoryRow", "{0} x{1}"),
			ItemName,
			FText::AsNumber(Entry.Quantity));

		UProjectEXInventorySlotWidget* Row = CreateWidget<UProjectEXInventorySlotWidget>(this, UProjectEXInventorySlotWidget::StaticClass());
		if (!Row)
		{
			continue;
		}

		Row->Setup(Entry.EntryId, RowLabel, Entry.EntryId == SelectedEntryId);
		Row->OnSlotClicked.AddDynamic(this, &UProjectEXInventoryWidget::HandleSlotClicked);

		if (UScrollBoxSlot* RowSlot = Cast<UScrollBoxSlot>(ItemList->AddChild(Row)))
		{
			RowSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 4.0f));
		}
	}

	UpdateSelectionVisuals();
}

void UProjectEXInventoryWidget::UpdateSelectionVisuals()
{
	if (DropButton)
	{
		DropButton->SetIsEnabled(SelectedEntryId != INDEX_NONE);
	}

	if (!ItemList)
	{
		return;
	}

	for (int32 Index = 0; Index < ItemList->GetChildrenCount(); ++Index)
	{
		if (UProjectEXInventorySlotWidget* RowWidget = Cast<UProjectEXInventorySlotWidget>(ItemList->GetChildAt(Index)))
		{
			RowWidget->SetSelected(RowWidget->GetEntryId() == SelectedEntryId);
		}
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
	bRefreshQueued = false;
	Refresh();
}

void UProjectEXInventoryWidget::HandleInventoryChanged()
{
	QueueRefresh();
}

void UProjectEXInventoryWidget::HandleSlotClicked(int32 ClickedEntryId)
{
	SelectedEntryId = ClickedEntryId;
	UpdateSelectionVisuals();
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
