// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectEXInteractable.h"
#include "ProjectEXTargetDummy.generated.h"

class UProjectEXHealthComponent;
class UStaticMeshComponent;
class UTextRenderComponent;

/** Placeable practice target. It has no AI and can be reset in place. */
UCLASS(Blueprintable)
class PROJECTEX_API AProjectEXTargetDummy : public AActor, public IProjectEXInteractable
{
	GENERATED_BODY()

public:

	AProjectEXTargetDummy();

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual FText GetInteractionPrompt_Implementation() const override;
	virtual bool CanInteract_Implementation(APawn* Interactor) const override;
	virtual void Interact_Implementation(APawn* Interactor) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> Head;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UProjectEXHealthComponent> Health;

	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UTextRenderComponent> FeedbackText;

	UPROPERTY(ReplicatedUsing=OnRep_Feedback)
	FString Feedback;

	UFUNCTION()
	void OnRep_Feedback();

	UFUNCTION()
	void HandleDamage(float AppliedDamage, bool bHeadshot);

private:

	void UpdateFeedback(const FString& Message);
};
