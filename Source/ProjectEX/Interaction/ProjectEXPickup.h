// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectEXInteractable.h"
#include "ProjectEXPickup.generated.h"

class UStaticMeshComponent;

/**
 *  Placeable world pickup. Interaction does not grant an item yet.
 *  The server destroys the actor, which replicates to other clients.
 */
UCLASS(Blueprintable)
class PROJECTEX_API AProjectEXPickup : public AActor, public IProjectEXInteractable
{
	GENERATED_BODY()

	/** Visible mesh. Line traces hit this component. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

protected:

	/** Verb shown in the interaction prompt. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	FText InteractionPrompt;

public:

	AProjectEXPickup();

	virtual FText GetInteractionPrompt_Implementation() const override;
	virtual bool CanInteract_Implementation(APawn* Interactor) const override;
	virtual void Interact_Implementation(APawn* Interactor) override;

	UStaticMeshComponent* GetMesh() const { return Mesh; }
};
