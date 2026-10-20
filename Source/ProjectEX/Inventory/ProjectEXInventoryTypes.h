// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectEXItemDefinition.h"
#include "ProjectEXInventoryTypes.generated.h"

/**
 *  One occupied inventory slot.
 *  EntryId stays unique for the lifetime of the component so later systems can refer to a specific stack.
 *  Grid position, rotation, and container links can be added to this struct later.
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
};
