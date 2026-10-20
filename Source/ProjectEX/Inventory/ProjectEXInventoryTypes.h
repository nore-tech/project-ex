// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectEXItemDefinition.h"
#include "ProjectEXInventoryTypes.generated.h"

/**
 *  One inventory stack.
 *  EntryId stays unique for the lifetime of the component.
 *  GridX and GridY are cell indices, with the origin at the top-left.
 *  bRotated stores a 90 degree turn, which swaps the definition's width and height.
 */
USTRUCT(BlueprintType)
struct FProjectEXInventoryEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	int32 EntryId = INDEX_NONE;

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	TObjectPtr<UProjectEXItemDefinition> Definition = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	int32 Quantity = 0;

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	int32 GridX = 0;

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	int32 GridY = 0;

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	bool bRotated = false;

	/**
	 *  Rounds currently loaded in a weapon entry.
	 *  -1 means this stack has no magazine. Ammo stacks leave it at -1.
	 */
	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	int32 MagazineRounds = -1;
};

/** One worn item. State stays here while it is out of the grid. */
USTRUCT(BlueprintType)
struct FProjectEXEquippedItem
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="Equipment")
	TObjectPtr<UProjectEXItemDefinition> Definition = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Equipment")
	int32 Quantity = 0;

	UPROPERTY(BlueprintReadOnly, Category="Equipment")
	int32 MagazineRounds = -1;

	bool IsOccupied() const
	{
		return Definition != nullptr && Quantity > 0;
	}
};
