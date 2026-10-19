// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputCoreTypes.h"
#include "ProjectEXInteractionComponent.generated.h"

class APawn;
class UEnhancedInputComponent;
class UInputAction;
class UInputMappingContext;
class UProjectEXInteractionPromptWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FProjectEXInteractionFocusChanged, AActor*, NewFocus, FText, Prompt);

/**
 *  Local camera trace that finds an interactable, plus a server request that re-traces before executing.
 *  Focus and the prompt are local. The interaction itself always runs through server validation.
 */
UCLASS(ClassGroup=(Interaction), meta=(BlueprintSpawnableComponent))
class PROJECTEX_API UProjectEXInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UProjectEXInteractionComponent();

	/** Binds interact. When no input action is assigned, creates a runtime mapping for InteractKey. */
	void BindInput(UEnhancedInputComponent* EnhancedInput);

	/** Uses the current focus, or a fresh trace, then asks the server to validate and execute. */
	UFUNCTION(BlueprintCallable, Category="Interaction")
	void RequestInteract();

	UFUNCTION(BlueprintPure, Category="Interaction")
	AActor* GetFocusedActor() const { return FocusedActor.Get(); }

	/** Fired on the owning client when the looked-at actor or prompt changes. */
	UPROPERTY(BlueprintAssignable, Category="Interaction")
	FProjectEXInteractionFocusChanged OnFocusChanged;

protected:

	/** Distance from the view point to the trace end. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction", meta=(ClampMin="0.0", Units="cm"))
	float InteractionRange = 250.0f;

	/** Channel used by the look trace. Interactables must block this channel. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

	/** Optional asset. When empty, a runtime action is created and mapped to InteractKey. */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> InteractAction;

	/** Key used by the automatic binding and by the prompt label. */
	UPROPERTY(EditAnywhere, Category="Input")
	FKey InteractKey;

	/** Widget class used for the prompt. Defaults to the native prompt widget. */
	UPROPERTY(EditAnywhere, Category="Interaction")
	TSubclassOf<UProjectEXInteractionPromptWidget> PromptWidgetClass;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Re-traces on the server and executes only when the hit actor is the requested target. */
	UFUNCTION(Server, Reliable)
	void ServerRequestInteract(AActor* Target);

private:

	void EnsureInteractAction();
	void RegisterMappingContext(const APawn* Pawn);
	void EnsurePromptWidget();
	void UpdateFocusedActor();
	void ApplyFocus(AActor* NewFocus);

	/** Camera trace for the local player. Remote server checks use the replicated view. */
	bool GetTraceView(FVector& OutLocation, FRotator& OutRotation) const;
	AActor* TraceInteractable() const;
	FText MakePrompt(const AActor* Interactable) const;

	UPROPERTY(Transient)
	TObjectPtr<UInputMappingContext> InteractMappingContext;

	UPROPERTY(Transient)
	TObjectPtr<UProjectEXInteractionPromptWidget> PromptWidget;

	TWeakObjectPtr<AActor> FocusedActor;

	bool bRegisteredMappingContext = false;
};
