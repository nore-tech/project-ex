// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ProjectEXInteractable.generated.h"

class APawn;

/**
 *  Implemented by actors the player can use by looking at them and pressing interact.
 *  Doors, containers, and other interactions should implement this rather than a new trace.
 *  Interact is executed on the server after UProjectEXInteractionComponent validates the request.
 */
UINTERFACE(MinimalAPI, BlueprintType)
class UProjectEXInteractable : public UInterface
{
	GENERATED_BODY()
};

class PROJECTEX_API IProjectEXInteractable
{
	GENERATED_BODY()

public:

	/** Short verb shown after the key label, such as "Pick Up" or "Open". */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	FText GetInteractionPrompt() const;

	/** Server and local focus both ask this before offering or executing an interaction. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	bool CanInteract(APawn* Interactor) const;

	/** Called on the server after range and line-of-sight checks succeed. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void Interact(APawn* Interactor);

	virtual FText GetInteractionPrompt_Implementation() const
	{
		return NSLOCTEXT("ProjectEX", "DefaultInteractPrompt", "Interact");
	}

	virtual bool CanInteract_Implementation(APawn* Interactor) const
	{
		return Interactor != nullptr;
	}

	virtual void Interact_Implementation(APawn* Interactor)
	{
	}
};
