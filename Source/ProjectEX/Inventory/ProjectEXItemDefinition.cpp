// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXItemDefinition.h"

UProjectEXItemDefinition::UProjectEXItemDefinition()
{
	PickupClass = AProjectEXPickup::StaticClass();
}

FName UProjectEXItemDefinition::GetItemId() const
{
	return ItemId.IsNone() ? GetFName() : ItemId;
}

FPrimaryAssetId UProjectEXItemDefinition::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(FPrimaryAssetType(TEXT("ProjectEXItem")), GetFName());
}
