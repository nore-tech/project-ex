// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/StaticMesh.h"
#include "Engine/Texture2D.h"
#include "ProjectEXPickup.h"
#include "ProjectEXItemDefinition.generated.h"

/**
 *  Data asset that describes one item type.
 *  Create assets in the editor instead of adding item classes in C++.
 */
UCLASS(BlueprintType)
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

	UFUNCTION(BlueprintPure, Category="Item")
	FName GetItemId() const;

	/** Occupied cells. X is width and Y is height. A 90 degree rotation swaps them. */
	UFUNCTION(BlueprintPure, Category="Item")
	FIntPoint GetGridSize(bool bRotated) const;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
