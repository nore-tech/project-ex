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

FIntPoint UProjectEXItemDefinition::GetGridSize(bool bRotated) const
{
	const int32 Width = FMath::Max(1, GridWidth);
	const int32 Height = FMath::Max(1, GridHeight);
	return bRotated ? FIntPoint(Height, Width) : FIntPoint(Width, Height);
}

FPrimaryAssetId UProjectEXItemDefinition::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(FPrimaryAssetType(TEXT("ProjectEXItem")), GetFName());
}
