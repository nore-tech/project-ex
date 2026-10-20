// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectEXItemDefinition.h"
#include "ProjectEXWeaponItemDefinition.generated.h"

class UProjectEXWeaponData;

/** Inventory item that can be equipped as a firearm. Its stats live on a weapon data asset. */
UCLASS(Blueprintable, BlueprintType)
class PROJECTEX_API UProjectEXWeaponItemDefinition : public UProjectEXItemDefinition
{
	GENERATED_BODY()

public:

	UProjectEXWeaponItemDefinition();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	TObjectPtr<UProjectEXWeaponData> WeaponData;
};
