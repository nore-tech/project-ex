// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXInteractionPromptWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Styling/CoreStyle.h"

void UProjectEXInteractionPromptWidget::SetPromptText(const FText& InPromptText)
{
	PromptText = InPromptText;

	if (PromptTextBlock)
	{
		PromptTextBlock->SetText(PromptText);
	}
}

TSharedRef<SWidget> UProjectEXInteractionPromptWidget::RebuildWidget()
{
	if (WidgetTree && !WidgetTree->RootWidget)
	{
		BuildLayout();
	}

	return Super::RebuildWidget();
}

void UProjectEXInteractionPromptWidget::BuildLayout()
{
	UCanvasPanel* Canvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("Canvas"));
	WidgetTree->RootWidget = Canvas;

	PromptTextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("PromptText"));
	PromptTextBlock->SetText(PromptText);
	PromptTextBlock->SetJustification(ETextJustify::Center);
	PromptTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	PromptTextBlock->SetShadowOffset(FVector2D(1.0f, 1.0f));
	PromptTextBlock->SetShadowColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.85f));

	FSlateFontInfo FontInfo = FCoreStyle::GetDefaultFontStyle(TEXT("Regular"), 22);
	PromptTextBlock->SetFont(FontInfo);
	PromptTextBlock->SetVisibility(ESlateVisibility::HitTestInvisible);

	if (UCanvasPanelSlot* CanvasSlot = Canvas->AddChildToCanvas(PromptTextBlock))
	{
		CanvasSlot->SetAnchors(FAnchors(0.5f, 0.58f, 0.5f, 0.58f));
		CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
		CanvasSlot->SetAutoSize(true);
	}

	SetIsFocusable(false);
}
