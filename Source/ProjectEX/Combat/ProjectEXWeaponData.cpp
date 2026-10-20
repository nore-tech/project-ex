// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXWeaponData.h"

FPrimaryAssetId UProjectEXWeaponData::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(FPrimaryAssetType(TEXT("ProjectEXWeapon")), GetFName());
}
