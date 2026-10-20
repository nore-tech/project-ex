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

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	void Refresh();

	TWeakObjectPtr<UProjectEXWeaponComponent> Weapon;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> StatusText;
};
