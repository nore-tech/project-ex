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
 *  Grid size, equipment, and containers can be added here later.
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

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
