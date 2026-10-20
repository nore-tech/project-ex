// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProjectEXRaidWidget.generated.h"

class UBorder;
class UButton;
class UImage;
class UTextBlock;

/** Raid banner, extraction countdown, damage flash, and the result screen with Deploy Again. */
UCLASS(Blueprintable)
class PROJECTEX_API UProjectEXRaidWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Rebuilds the result panel from the owning controller's raid status. */
	void RefreshStatus();

	/** Slate widget that should take keyboard focus on the result screen, so Enter or Space deploys. */
	TSharedPtr<SWidget> GetFocusTarget();

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	UFUNCTION()
	void HandleDeployClicked();

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> BannerText;

	UPROPERTY(Transient)
	TObjectPtr<UImage> DamageFlash;

	UPROPERTY(Transient)
	TObjectPtr<UBorder> ResultPanel;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> ResultTitle;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> ResultDetails;

	UPROPERTY(Transient)
	TObjectPtr<UButton> DeployButton;

	float LastHealth = -1.0f;
	float FlashAlpha = 0.0f;
};
