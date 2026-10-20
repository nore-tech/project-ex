// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXRaidWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "GameFramework/Pawn.h"
#include "ProjectEXHealthComponent.h"
#include "ProjectEXPlayerController.h"
#include "Styling/CoreStyle.h"

namespace
{
	UTextBlock* MakeText(UWidgetTree* Tree, int32 Size, const FLinearColor& Color)
	{
		UTextBlock* Text = Tree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		Text->SetFont(FCoreStyle::GetDefaultFontStyle(TEXT("Bold"), Size));
		Text->SetColorAndOpacity(FSlateColor(Color));
		Text->SetJustification(ETextJustify::Center);
		return Text;
	}

	FString FormatDuration(float Seconds)
	{
		const int32 Total = FMath::Max(0, FMath::FloorToInt(Seconds));
		return FString::Printf(TEXT("%d:%02d"), Total / 60, Total % 60);
	}
}

TSharedRef<SWidget> UProjectEXRaidWidget::RebuildWidget()
{
	if (WidgetTree && !WidgetTree->RootWidget)
	{
		UCanvasPanel* Canvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
		Canvas->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		WidgetTree->RootWidget = Canvas;

		DamageFlash = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
		DamageFlash->SetColorAndOpacity(FLinearColor(0.7f, 0.0f, 0.0f, 0.0f));
		DamageFlash->SetVisibility(ESlateVisibility::HitTestInvisible);
		Canvas->AddChild(DamageFlash);
		if (UCanvasPanelSlot* FlashSlot = Cast<UCanvasPanelSlot>(DamageFlash->Slot))
		{
			FlashSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
			FlashSlot->SetOffsets(FMargin(0.0f));
		}

		BannerText = MakeText(WidgetTree, 26, FLinearColor(0.55f, 1.0f, 0.55f));
		BannerText->SetVisibility(ESlateVisibility::HitTestInvisible);
		BannerText->SetShadowOffset(FVector2D(2.0f, 2.0f));
		BannerText->SetShadowColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.8f));
		Canvas->AddChild(BannerText);
		if (UCanvasPanelSlot* BannerSlot = Cast<UCanvasPanelSlot>(BannerText->Slot))
		{
			BannerSlot->SetAnchors(FAnchors(0.5f, 0.0f, 0.5f, 0.0f));
			BannerSlot->SetAlignment(FVector2D(0.5f, 0.0f));
			BannerSlot->SetAutoSize(true);
			BannerSlot->SetPosition(FVector2D(0.0f, 90.0f));
		}

		ResultPanel = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
		ResultPanel->SetBrushColor(FLinearColor(0.02f, 0.02f, 0.025f, 0.92f));
		ResultPanel->SetPadding(FMargin(48.0f, 36.0f));
		ResultPanel->SetVisibility(ESlateVisibility::Collapsed);
		Canvas->AddChild(ResultPanel);
		if (UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(ResultPanel->Slot))
		{
			PanelSlot->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
			PanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
			PanelSlot->SetAutoSize(true);
		}

		UVerticalBox* Column = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass());
		ResultPanel->SetContent(Column);

		ResultTitle = MakeText(WidgetTree, 40, FLinearColor::White);
		if (UVerticalBoxSlot* TitleSlot = Column->AddChildToVerticalBox(ResultTitle))
		{
			TitleSlot->SetHorizontalAlignment(HAlign_Center);
			TitleSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 16.0f));
		}

		ResultDetails = MakeText(WidgetTree, 18, FLinearColor(0.85f, 0.85f, 0.85f));
		ResultDetails->SetFont(FCoreStyle::GetDefaultFontStyle(TEXT("Regular"), 18));
		if (UVerticalBoxSlot* DetailSlot = Column->AddChildToVerticalBox(ResultDetails))
		{
			DetailSlot->SetHorizontalAlignment(HAlign_Center);
			DetailSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 28.0f));
		}

		DeployButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());
		DeployButton->SetBackgroundColor(FLinearColor(0.2f, 0.45f, 0.25f));
		DeployButton->OnClicked.AddDynamic(this, &UProjectEXRaidWidget::HandleDeployClicked);
		UTextBlock* ButtonLabel = MakeText(WidgetTree, 20, FLinearColor::White);
		ButtonLabel->SetText(FText::FromString(TEXT("DEPLOY AGAIN")));
		DeployButton->SetContent(ButtonLabel);
		if (UVerticalBoxSlot* ButtonSlot = Column->AddChildToVerticalBox(DeployButton))
		{
			ButtonSlot->SetHorizontalAlignment(HAlign_Center);
		}
	}

	return Super::RebuildWidget();
}

void UProjectEXRaidWidget::RefreshStatus()
{
	const AProjectEXPlayerController* PC = Cast<AProjectEXPlayerController>(GetOwningPlayer());
	if (!PC || !ResultPanel)
	{
		return;
	}

	const EProjectEXRaidStatus Status = PC->GetRaidStatus();
	if (Status != EProjectEXRaidStatus::Extracted && Status != EProjectEXRaidStatus::Dead)
	{
		ResultPanel->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	const bool bExtracted = Status == EProjectEXRaidStatus::Extracted;
	ResultTitle->SetText(FText::FromString(bExtracted ? TEXT("EXTRACTED") : TEXT("KILLED IN ACTION")));
	ResultTitle->SetColorAndOpacity(FSlateColor(bExtracted ? FLinearColor(0.4f, 1.0f, 0.45f) : FLinearColor(1.0f, 0.3f, 0.25f)));

	FString Details = bExtracted
		? FString::Printf(TEXT("Raid successful via %s"), *PC->GetExtractionName().ToString())
		: FString(TEXT("Raid failed"));
	Details += FString::Printf(TEXT("\nEnemies killed: %d\nRaid time: %s"), PC->GetRaidKills(), *FormatDuration(PC->GetRaidDuration()));
	ResultDetails->SetText(FText::FromString(Details));

	ResultPanel->SetVisibility(ESlateVisibility::Visible);
	BannerText->SetText(FText::GetEmpty());
}

void UProjectEXRaidWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	const AProjectEXPlayerController* PC = Cast<AProjectEXPlayerController>(GetOwningPlayer());
	if (!PC || !BannerText)
	{
		return;
	}

	FString Banner;
	FLinearColor BannerColor(0.55f, 1.0f, 0.55f);
	switch (PC->GetRaidStatus())
	{
	case EProjectEXRaidStatus::Preparing:
		Banner = TEXT("DEPLOYING...");
		BannerColor = FLinearColor(0.9f, 0.9f, 0.9f);
		break;
	case EProjectEXRaidStatus::InRaid:
		if (PC->GetExtractionSecondsLeft() >= 0)
		{
			Banner = FString::Printf(TEXT("EXTRACTING - %s\n%d"), *PC->GetExtractionName().ToString(), PC->GetExtractionSecondsLeft());
		}
		break;
	default:
		break;
	}
	BannerText->SetText(FText::FromString(Banner));
	BannerText->SetColorAndOpacity(FSlateColor(BannerColor));

	const APawn* Pawn = PC->GetPawn();
	const UProjectEXHealthComponent* Health = Pawn ? Pawn->FindComponentByClass<UProjectEXHealthComponent>() : nullptr;
	const float CurrentHealth = Health ? Health->GetHealth() : -1.0f;
	if (LastHealth >= 0.0f && CurrentHealth >= 0.0f && CurrentHealth < LastHealth)
	{
		FlashAlpha = 0.35f;
	}
	LastHealth = CurrentHealth;

	FlashAlpha = FMath::Max(0.0f, FlashAlpha - InDeltaTime * 0.9f);
	DamageFlash->SetColorAndOpacity(FLinearColor(0.7f, 0.0f, 0.0f, FlashAlpha));
}

TSharedPtr<SWidget> UProjectEXRaidWidget::GetFocusTarget()
{
	TSharedRef<SWidget> Root = TakeWidget();
	return DeployButton ? DeployButton->TakeWidget() : Root;
}

void UProjectEXRaidWidget::HandleDeployClicked()
{
	if (AProjectEXPlayerController* PC = Cast<AProjectEXPlayerController>(GetOwningPlayer()))
	{
		DeployButton->SetIsEnabled(false);
		PC->RequestDeployAgain();
	}
}
