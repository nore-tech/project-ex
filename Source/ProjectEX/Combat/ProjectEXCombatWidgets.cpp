// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXCombatWidgets.h"
#include "ProjectEXHealthComponent.h"
#include "ProjectEXWeaponComponent.h"
#include "ProjectEXWeaponData.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "GameFramework/Pawn.h"
#include "Styling/CoreStyle.h"

void UProjectEXCombatHudWidget::BindWeapon(UProjectEXWeaponComponent* InWeapon)
{
	Weapon = InWeapon;
	Refresh();
}

TSharedRef<SWidget> UProjectEXCombatHudWidget::RebuildWidget()
{
	if (WidgetTree && !WidgetTree->RootWidget)
	{
		UCanvasPanel* Canvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
		WidgetTree->RootWidget = Canvas;

		StatusText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		StatusText->SetFont(FCoreStyle::GetDefaultFontStyle(TEXT("Regular"), 18));
		StatusText->SetColorAndOpacity(FSlateColor(FLinearColor::White));
		StatusText->SetVisibility(ESlateVisibility::HitTestInvisible);
		Canvas->AddChild(StatusText);
		if (UCanvasPanelSlot* TextSlot = Cast<UCanvasPanelSlot>(StatusText->Slot))
		{
			TextSlot->SetAnchors(FAnchors(0.0f, 1.0f, 0.0f, 1.0f));
			TextSlot->SetAlignment(FVector2D(0.0f, 1.0f));
			TextSlot->SetAutoSize(true);
			TextSlot->SetPosition(FVector2D(28.0f, -28.0f));
		}

		auto AddCentered = [this, Canvas](const TCHAR* Glyph, int32 Size, const FLinearColor& Color)
		{
			UTextBlock* Text = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
			Text->SetFont(FCoreStyle::GetDefaultFontStyle(TEXT("Bold"), Size));
			Text->SetColorAndOpacity(FSlateColor(Color));
			Text->SetText(FText::FromString(Glyph));
			Text->SetVisibility(ESlateVisibility::HitTestInvisible);
			Canvas->AddChild(Text);
			if (UCanvasPanelSlot* CenterSlot = Cast<UCanvasPanelSlot>(Text->Slot))
			{
				CenterSlot->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
				CenterSlot->SetAlignment(FVector2D(0.5f, 0.5f));
				CenterSlot->SetAutoSize(true);
			}
			return Text;
		};

		Crosshair = AddCentered(TEXT("+"), 14, FLinearColor(1.0f, 1.0f, 1.0f, 0.6f));
		HitMarker = AddCentered(TEXT("X"), 22, FLinearColor::White);
		HitMarker->SetRenderOpacity(0.0f);
	}

	return Super::RebuildWidget();
}

void UProjectEXCombatHudWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	Refresh();

	if (HitMarker && HitMarkerTime > 0.0f)
	{
		HitMarkerTime = FMath::Max(0.0f, HitMarkerTime - InDeltaTime);
		HitMarker->SetRenderOpacity(FMath::Clamp(HitMarkerTime / 0.25f, 0.0f, 1.0f));
	}
}

void UProjectEXCombatHudWidget::ShowHitMarker(bool bKilled)
{
	if (!HitMarker)
	{
		return;
	}
	HitMarker->SetColorAndOpacity(FSlateColor(bKilled ? FLinearColor(1.0f, 0.2f, 0.15f) : FLinearColor::White));
	HitMarkerTime = bKilled ? 0.6f : 0.25f;
	HitMarker->SetRenderOpacity(1.0f);
}

void UProjectEXCombatHudWidget::Refresh()
{
	if (!StatusText)
	{
		return;
	}

	UProjectEXWeaponComponent* WeaponComponent = Weapon.Get();
	APawn* Pawn = WeaponComponent ? Cast<APawn>(WeaponComponent->GetOwner()) : nullptr;
	const UProjectEXHealthComponent* Health = Pawn ? Pawn->FindComponentByClass<UProjectEXHealthComponent>() : nullptr;
	const UProjectEXWeaponData* WeaponData = WeaponComponent ? WeaponComponent->GetEquippedWeapon() : nullptr;

	FString Line = Health
		? FString::Printf(TEXT("Health %.0f / %.0f"), Health->GetHealth(), Health->GetMaxHealth())
		: TEXT("Health --");

	if (Health && Health->IsDead())
	{
		Line += TEXT("  DEAD");
	}
	else if (!WeaponData)
	{
		Line += TEXT("\nNo weapon  [1] cycle");
	}
	else
	{
		const FString Name = WeaponData->DisplayName.IsEmpty() ? WeaponData->GetName() : WeaponData->DisplayName.ToString();
		Line += FString::Printf(TEXT("\n%s  %d / %d"), *Name, WeaponComponent->GetMagazine(), WeaponData->MagazineSize);
		Line += FString::Printf(TEXT("\nReserve %d"), WeaponComponent->GetReserveAmmo());
		if (WeaponComponent->IsReloading())
		{
			Line += TEXT("\nReloading");
		}
	}

	StatusText->SetText(FText::FromString(Line));
}
