// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProjectEXCombatWidgets.generated.h"

class UProjectEXWeaponComponent;
class UTextBlock;

UCLASS()
class PROJECTEX_API UProjectEXCombatHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void BindWeapon(UProjectEXWeaponComponent* InWeapon);

	/** Brief crosshair marker. Red when the hit killed the target. */
	void ShowHitMarker(bool bKilled);

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	void Refresh();

	TWeakObjectPtr<UProjectEXWeaponComponent> Weapon;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> StatusText;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> Crosshair;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> HitMarker;

	float HitMarkerTime = 0.0f;
};
