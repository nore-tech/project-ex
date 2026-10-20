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
};
