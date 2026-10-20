// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StaticMesh.h"
#include "Engine/Texture2D.h"
#include "ProjectEXPickup.h"
#include "ProjectEXItemDefinition.generated.h"

/** Which worn slot an item can occupy. Weapons fit either weapon slot. */
UENUM(BlueprintType)
enum class EProjectEXEquipKind : uint8
{
	None,
	Weapon,
	Helmet,
	BodyArmor,
	Backpack
};

/** The five worn slots. */
UENUM(BlueprintType)
enum class EProjectEXEquipmentSlot : uint8
{
	PrimaryWeapon,
	SecondaryWeapon,
	Helmet,
	BodyArmor,
	Backpack
};

/**
 *  Data asset that describes one item type.
 *  Create assets in the editor instead of adding item classes in C++.
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTEX_API UProjectEXItemDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UProjectEXItemDefinition();

	/** Gameplay id. When None, the asset name is used. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	FName ItemId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item", meta=(MultiLine="true"))
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	TSoftObjectPtr<UTexture2D> Icon;

	/** Units that fit in one inventory entry. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item", meta=(ClampMin="1"))
	int32 MaxStackSize = 1;

	/** Cells occupied across the inventory grid. Rotation swaps these. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item", meta=(ClampMin="1"))
	int32 GridWidth = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item", meta=(ClampMin="1"))
	int32 GridHeight = 1;

	/** Stored for later weight limits. Not enforced yet. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item", meta=(ClampMin="0.0", Units="kg"))
	float Weight = 0.0f;

	/** Actor spawned when this item is dropped. Defaults to AProjectEXPickup. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	TSubclassOf<AProjectEXPickup> PickupClass;

	/** Optional mesh applied to the world pickup. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	TSoftObjectPtr<UStaticMesh> WorldMesh;

	/** Shown on the pickup when no static world mesh is set. Used for skeletal weapons. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	TSoftObjectPtr<USkeletalMesh> DisplaySkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	FRotator DisplaySkeletalRotation = FRotator(0.0f, -90.0f, 0.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item", meta=(ClampMin="0.01"))
	float DisplaySkeletalScale = 1.0f;

	/** None keeps the item in the grid only. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	EProjectEXEquipKind EquipKind = EProjectEXEquipKind::None;

	/** Health restored when one of this item is used. Zero means it is not a medical item. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item", meta=(ClampMin="0.0"))
	float HealAmount = 0.0f;

	UFUNCTION(BlueprintPure, Category="Item")
	FName GetItemId() const;

	/** Occupied cells. X is width and Y is height. A 90 degree rotation swaps them. */
	UFUNCTION(BlueprintPure, Category="Item")
	FIntPoint GetGridSize(bool bRotated) const;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
