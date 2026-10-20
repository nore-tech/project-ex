// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXLootWidgets.h"
#include "ProjectEXInventoryTypes.h"
#include "ProjectEXItemDefinition.h"
#include "ProjectEXLootContainer.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/ButtonSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Styling/CoreStyle.h"

namespace
{
	UTextBlock* MakeLootText(UWidgetTree* WidgetTree, int32 Size, const FLinearColor& Color)
	{
		UTextBlock* Text = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		Text->SetFont(FCoreStyle::GetDefaultFontStyle(TEXT("Regular"), Size));
		Text->SetColorAndOpacity(FSlateColor(Color));
		Text->SetVisibility(ESlateVisibility::HitTestInvisible);
		Text->SetAutoWrapText(true);
		return Text;
	}

	void PlaceLootWidget(UWidget* Widget, float X, float Y, float Width, float Height, int32 ZOrder)
	{
		if (UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(Widget ? Widget->Slot : nullptr))
		{
			PanelSlot->SetAutoSize(false);
			PanelSlot->SetAnchors(FAnchors(0.0f, 0.0f, 0.0f, 0.0f));
			PanelSlot->SetAlignment(FVector2D::ZeroVector);
			PanelSlot->SetPosition(FVector2D(X, Y));
			PanelSlot->SetSize(FVector2D(Width, Height));
			PanelSlot->SetZOrder(ZOrder);
		}
	}

	FLinearColor LootTint(const UProjectEXItemDefinition* Definition)
	{
		if (!Definition)
		{
			return FLinearColor(0.16f, 0.17f, 0.18f, 1.0f);
		}

		switch (Definition->EquipKind)
		{
		case EProjectEXEquipKind::Weapon:
			return FLinearColor(0.34f, 0.24f, 0.14f, 1.0f);
		case EProjectEXEquipKind::Helmet:
			return FLinearColor(0.18f, 0.24f, 0.32f, 1.0f);
		case EProjectEXEquipKind::BodyArmor:
			return FLinearColor(0.16f, 0.28f, 0.2f, 1.0f);
		case EProjectEXEquipKind::Backpack:
			return FLinearColor(0.28f, 0.22f, 0.14f, 1.0f);
		default:
			break;
		}

		if (Definition->HealAmount > 0.0f)
		{
			return FLinearColor(0.32f, 0.16f, 0.16f, 1.0f);
		}

		return FLinearColor(0.2f, 0.2f, 0.16f, 1.0f);
	}
}

void UProjectEXLootItemWidget::ApplyEntry(UProjectEXLootWidget* InOwner, const FProjectEXInventoryEntry& Entry, float InCellSize)
{
	OwnerWidget = InOwner;
	EntryId = Entry.EntryId;
	SetVisibility(ESlateVisibility::Visible);

	if (!Face)
	{
		return;
	}

	Face->SetBrushColor(LootTint(Entry.Definition));
	if (NameText)
	{
		FString Label = Entry.Definition
			? (Entry.Definition->DisplayName.IsEmpty() ? Entry.Definition->GetItemId().ToString() : Entry.Definition->DisplayName.ToString())
			: TEXT("Item");
		if (Entry.Quantity > 1)
		{
			Label += FString::Printf(TEXT(" x%d"), Entry.Quantity);
		}
		NameText->SetText(FText::FromString(Label));
	}

	const FIntPoint Size = Entry.Definition ? Entry.Definition->GetGridSize(Entry.bRotated) : FIntPoint(1, 1);
	const float Width = FMath::Max(1.0f, InCellSize) * Size.X;
	const float Height = FMath::Max(1.0f, InCellSize) * Size.Y;
	PlaceLootWidget(this, Entry.GridX * InCellSize, Entry.GridY * InCellSize, Width, Height, 2);
}

TSharedRef<SWidget> UProjectEXLootItemWidget::RebuildWidget()
{
	if (WidgetTree && !WidgetTree->RootWidget)
	{
		Face = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
		Face->SetPadding(FMargin(4.0f));
		WidgetTree->RootWidget = Face;
		NameText = MakeLootText(WidgetTree, 11, FLinearColor::White);
		Face->SetContent(NameText);
	}

	return Super::RebuildWidget();
}

FReply UProjectEXLootItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() != EKeys::LeftMouseButton)
	{
		return FReply::Handled();
	}

	const double Now = FPlatformTime::Seconds();
	const bool bDoubleClick = (Now - LastClickSeconds) <= 0.32;
	LastClickSeconds = Now;
	if (bDoubleClick)
	{
		if (UProjectEXLootWidget* Loot = OwnerWidget.Get())
		{
			Loot->NotifyTake(EntryId);
		}
	}

	return FReply::Handled();
}

void UProjectEXLootWidget::NotifyTake(int32 EntryId)
{
	OnTakeClicked.Broadcast(EntryId);
}

void UProjectEXLootWidget::Open(AProjectEXLootContainer* InContainer)
{
	if (AProjectEXLootContainer* Previous = Container.Get())
	{
		Previous->OnContentsChanged.RemoveDynamic(this, &UProjectEXLootWidget::HandleContentsChanged);
	}

	Container = InContainer;
	if (InContainer)
	{
		InContainer->OnContentsChanged.AddDynamic(this, &UProjectEXLootWidget::HandleContentsChanged);
	}

	Refresh();
}

TSharedRef<SWidget> UProjectEXLootWidget::RebuildWidget()
{
	if (WidgetTree && !WidgetTree->RootWidget)
	{
		BuildLayout();
	}

	return Super::RebuildWidget();
}

void UProjectEXLootWidget::BuildLayout()
{
	UCanvasPanel* Canvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
	WidgetTree->RootWidget = Canvas;

	UBorder* Panel = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
	Panel->SetBrushColor(FLinearColor(0.05f, 0.06f, 0.07f, 0.94f));
	Panel->SetPadding(FMargin(16.0f));
	Canvas->AddChild(Panel);
	if (UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(Panel->Slot))
	{
		PanelSlot->SetAnchors(FAnchors(0.0f, 0.5f, 0.0f, 0.5f));
		PanelSlot->SetAlignment(FVector2D(0.0f, 0.5f));
		PanelSlot->SetAutoSize(true);
		PanelSlot->SetPosition(FVector2D(24.0f, 0.0f));
	}

	UVerticalBox* Column = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass());
	Panel->SetContent(Column);

	UTextBlock* Title = MakeLootText(WidgetTree, 20, FLinearColor(0.93f, 0.9f, 0.78f));
	Title->SetText(NSLOCTEXT("ProjectEX", "LootTitle", "CONTAINER"));
	Column->AddChildToVerticalBox(Title);

	HintText = MakeLootText(WidgetTree, 12, FLinearColor(0.7f, 0.7f, 0.66f));
	HintText->SetText(NSLOCTEXT("ProjectEX", "LootHint", "Double-click takes an item. Weapons fill Primary, then Secondary. Helmet, armor, and backpack fill their slot."));
	if (UVerticalBoxSlot* HintSlot = Column->AddChildToVerticalBox(HintText))
	{
		HintSlot->SetPadding(FMargin(0.0f, 6.0f, 0.0f, 8.0f));
	}

	GridSizeBox = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());
	GridCanvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
	GridSizeBox->SetContent(GridCanvas);
	Column->AddChildToVerticalBox(GridSizeBox);

	UProjectEXLootSilentButton* CloseButton = WidgetTree->ConstructWidget<UProjectEXLootSilentButton>(UProjectEXLootSilentButton::StaticClass());
	CloseButton->SetBackgroundColor(FLinearColor(0.16f, 0.17f, 0.18f));
	CloseButton->OnClicked.AddDynamic(this, &UProjectEXLootWidget::HandleCloseClicked);
	UTextBlock* CloseLabel = MakeLootText(WidgetTree, 14, FLinearColor::White);
	CloseLabel->SetText(NSLOCTEXT("ProjectEX", "LootClose", "Close"));
	if (UButtonSlot* CloseSlot = Cast<UButtonSlot>(CloseButton->AddChild(CloseLabel)))
	{
		CloseSlot->SetPadding(FMargin(10.0f, 6.0f));
	}
	if (UVerticalBoxSlot* CloseBoxSlot = Column->AddChildToVerticalBox(CloseButton))
	{
		CloseBoxSlot->SetPadding(FMargin(0.0f, 10.0f, 0.0f, 0.0f));
	}

	SetIsFocusable(false);
}

void UProjectEXLootWidget::Refresh()
{
	if (!GridCanvas || !GridSizeBox)
	{
		return;
	}

	GridCanvas->ClearChildren();
	const AProjectEXLootContainer* LootContainer = Container.Get();
	const int32 Columns = LootContainer ? LootContainer->GetGridColumns() : 6;
	const int32 Rows = LootContainer ? LootContainer->GetGridRows() : 4;
	GridSizeBox->SetWidthOverride(Columns * CellSize);
	GridSizeBox->SetHeightOverride(Rows * CellSize);

	for (int32 Y = 0; Y < Rows; ++Y)
	{
		for (int32 X = 0; X < Columns; ++X)
		{
			UBorder* Cell = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
			Cell->SetBrushColor(FLinearColor(0.11f, 0.12f, 0.13f, 1.0f));
			Cell->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			GridCanvas->AddChild(Cell);
			PlaceLootWidget(Cell, X * CellSize + 1.0f, Y * CellSize + 1.0f, CellSize - 2.0f, CellSize - 2.0f, 0);
		}
	}

	if (!LootContainer)
	{
		return;
	}

	for (const FProjectEXInventoryEntry& Entry : LootContainer->GetEntries())
	{
		if (!Entry.Definition || Entry.Quantity <= 0)
		{
			continue;
		}

		UProjectEXLootItemWidget* ItemWidget = CreateWidget<UProjectEXLootItemWidget>(this, UProjectEXLootItemWidget::StaticClass());
		if (!ItemWidget)
		{
			continue;
		}

		GridCanvas->AddChild(ItemWidget);
		ItemWidget->ApplyEntry(this, Entry, CellSize);
	}
}

void UProjectEXLootWidget::HandleContentsChanged()
{
	Refresh();
}

void UProjectEXLootWidget::HandleCloseClicked()
{
	OnClosed.Broadcast();
}
