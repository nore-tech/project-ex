// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ProjectEXEnemyController.generated.h"

class AProjectEXEnemy;
class UAISenseConfig_Sight;

/** Server-side brain for AProjectEXEnemy: sight perception, chase, attack, and idle wander. */
UCLASS(Blueprintable)
class PROJECTEX_API AProjectEXEnemyController : public AAIController
{
	GENERATED_BODY()

public:

	AProjectEXEnemyController();

protected:

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UPROPERTY(VisibleAnywhere, Category="AI")
	TObjectPtr<UAISenseConfig_Sight> SightConfig;

	/** Seconds between decisions. */
	UPROPERTY(EditDefaultsOnly, Category="AI", meta=(ClampMin="0.05", Units="s"))
	float ThinkInterval = 0.2f;

	/** Players this close are detected even outside the sight cone. Fraction of the detection range. */
	UPROPERTY(EditDefaultsOnly, Category="AI", meta=(ClampMin="0.0", ClampMax="1.0"))
	float HearingFraction = 0.25f;

private:

	void Think();
	APawn* FindTarget(const AProjectEXEnemy* Enemy) const;
	void ChaseTarget(AProjectEXEnemy* Enemy, APawn* Target);
	void Wander(AProjectEXEnemy* Enemy);
	static bool IsValidTarget(const APawn* Pawn);

	FTimerHandle ThinkTimer;
	TWeakObjectPtr<APawn> CurrentTarget;
	FVector HomeLocation = FVector::ZeroVector;
	float NextWanderTime = 0.0f;
};
