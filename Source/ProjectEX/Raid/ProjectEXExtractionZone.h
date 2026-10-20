// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectEXExtractionZone.generated.h"

class AProjectEXPlayerController;
class UStaticMeshComponent;
class UTextRenderComponent;

/** Stand inside for the countdown to extract. The server owns timing and completion. */
UCLASS(Blueprintable)
class PROJECTEX_API AProjectEXExtractionZone : public AActor
{
	GENERATED_BODY()

public:

	AProjectEXExtractionZone();

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaSeconds) override;

	/** Cosmetic. Runs on the server when a player extracts here. */
	UFUNCTION(BlueprintImplementableEvent, Category="Extraction")
	void OnPlayerExtracted(APlayerController* Player);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Pad;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Beacon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UTextRenderComponent> Label;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Extraction")
	FText DisplayName = FText::FromString(TEXT("Exfil"));

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Extraction", meta=(ClampMin="50.0", Units="cm"))
	float Radius = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Extraction", meta=(ClampMin="0.5", Units="s"))
	float Countdown = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Extraction")
	FLinearColor ZoneColor = FLinearColor(0.1f, 0.9f, 0.25f);

private:

	void ApplyVisuals();
	bool IsInside(const APawn* Pawn) const;

	TMap<TWeakObjectPtr<AProjectEXPlayerController>, float> EnterTimes;
};
