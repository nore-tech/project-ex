// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectEXDamagePad.generated.h"

class UBoxComponent;
class USceneComponent;
class UStaticMeshComponent;
class UTextRenderComponent;

/** Floor pad that damages a living player while they stand on it. */
UCLASS(Blueprintable)
class PROJECTEX_API AProjectEXDamagePad : public AActor
{
	GENERATED_BODY()

public:

	AProjectEXDamagePad();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:

	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UBoxComponent> Trigger;

	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UTextRenderComponent> Label;

	UPROPERTY(EditAnywhere, Category="Damage", meta=(ClampMin="1.0"))
	float Damage = 25.0f;

	UPROPERTY(EditAnywhere, Category="Damage", meta=(ClampMin="0.1", Units="s"))
	float DamageInterval = 0.8f;

private:

	void DamagePawn(APawn* Pawn);

	TMap<TWeakObjectPtr<APawn>, float> NextDamageTime;
};
