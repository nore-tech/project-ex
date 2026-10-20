// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXEnemyController.h"
#include "Navigation/PathFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "ProjectEXEnemy.h"
#include "ProjectEXHealthComponent.h"
#include "ProjectEXPlayerController.h"
#include "ProjectEX.h"
#include "TimerManager.h"

AProjectEXEnemyController::AProjectEXEnemyController()
{
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception")));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1500.0f;
	SightConfig->LoseSightRadius = 1875.0f;
	SightConfig->PeripheralVisionAngleDegrees = 70.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	GetPerceptionComponent()->SetDominantSense(UAISense_Sight::StaticClass());
}

void AProjectEXEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (const AProjectEXEnemy* Enemy = Cast<AProjectEXEnemy>(InPawn))
	{
		SightConfig->SightRadius = Enemy->GetDetectionRange();
		SightConfig->LoseSightRadius = Enemy->GetDetectionRange() * 1.25f;
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
		HomeLocation = Enemy->GetActorLocation();
	}

	GetWorldTimerManager().SetTimer(ThinkTimer, this, &AProjectEXEnemyController::Think, ThinkInterval, true, FMath::FRandRange(0.0f, ThinkInterval));
}

void AProjectEXEnemyController::OnUnPossess()
{
	GetWorldTimerManager().ClearTimer(ThinkTimer);
	ClearFocus(EAIFocusPriority::Gameplay);
	CurrentTarget.Reset();
	Super::OnUnPossess();
}

void AProjectEXEnemyController::Think()
{
	AProjectEXEnemy* Enemy = Cast<AProjectEXEnemy>(GetPawn());
	if (!Enemy || Enemy->IsDead())
	{
		StopMovement();
		ClearFocus(EAIFocusPriority::Gameplay);
		GetWorldTimerManager().ClearTimer(ThinkTimer);
		return;
	}

	APawn* Target = FindTarget(Enemy);
	if (Target != CurrentTarget.Get())
	{
		CurrentTarget = Target;
		StopMovement();
		Enemy->SetDirectChaseTarget(nullptr);
	}

	if (Target)
	{
		ChaseTarget(Enemy, Target);
	}
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		Wander(Enemy);
	}
}

bool AProjectEXEnemyController::IsValidTarget(const APawn* Pawn)
{
	if (!Pawn || !Pawn->IsPlayerControlled())
	{
		return false;
	}
	if (const AProjectEXPlayerController* RaidController = Cast<AProjectEXPlayerController>(Pawn->GetController()))
	{
		if (!RaidController->IsInRaid())
		{
			return false;
		}
	}
	const UProjectEXHealthComponent* TargetHealth = Pawn->FindComponentByClass<UProjectEXHealthComponent>();
	return TargetHealth && !TargetHealth->IsDead();
}

APawn* AProjectEXEnemyController::FindTarget(const AProjectEXEnemy* Enemy) const
{
	const FVector Origin = Enemy->GetActorLocation();
	APawn* Best = nullptr;
	float BestDistSq = TNumericLimits<float>::Max();

	auto Consider = [&](APawn* Candidate)
	{
		if (!IsValidTarget(Candidate))
		{
			return;
		}
		const float DistSq = FVector::DistSquared(Origin, Candidate->GetActorLocation());
		if (DistSq < BestDistSq)
		{
			BestDistSq = DistSq;
			Best = Candidate;
		}
	};

	TArray<AActor*> Known;
	if (const UAIPerceptionComponent* Perception = PerceptionComponent.Get())
	{
		Perception->GetKnownPerceivedActors(UAISense_Sight::StaticClass(), Known);
	}
	for (AActor* Actor : Known)
	{
		Consider(Cast<APawn>(Actor));
	}

	const float NearRange = Enemy->GetDetectionRange() * HearingFraction;
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		if (const APlayerController* PlayerController = It->Get())
		{
			APawn* PlayerPawn = PlayerController->GetPawn();
			if (PlayerPawn && FVector::Dist(Origin, PlayerPawn->GetActorLocation()) <= NearRange)
			{
				Consider(PlayerPawn);
			}
		}
	}

	return Best;
}

void AProjectEXEnemyController::ChaseTarget(AProjectEXEnemy* Enemy, APawn* Target)
{
	SetFocus(Target, EAIFocusPriority::Gameplay);

	const float AttackRange = Enemy->GetAttackRange();
	const float Distance = FVector::Dist2D(Enemy->GetActorLocation(), Target->GetActorLocation());
	const bool bInRange = Distance <= AttackRange;

	if (bInRange && LineOfSightTo(Target))
	{
		StopMovement();
		Enemy->SetDirectChaseTarget(nullptr);
		Enemy->TryAttack(Target);
		return;
	}

	if (GetMoveStatus() == EPathFollowingStatus::Moving)
	{
		return;
	}

	// In range without line of sight: close in further so the enemy steps around the blocker.
	const float Acceptance = bInRange ? 30.0f : AttackRange * 0.6f;
	EPathFollowingRequestResult::Type Result = MoveToActor(Target, Acceptance, false, true, true, nullptr, true);
	if (Result == EPathFollowingRequestResult::Failed)
	{
		UE_LOG(LogProjectEX, Verbose, TEXT("%s: no navmesh path to %s, moving directly"), *GetNameSafe(Enemy), *GetNameSafe(Target));
		Result = MoveToActor(Target, Acceptance, false, false, true, nullptr, true);
	}
	Enemy->SetDirectChaseTarget(Result == EPathFollowingRequestResult::Failed ? Target : nullptr);
}

void AProjectEXEnemyController::Wander(AProjectEXEnemy* Enemy)
{
	const float Radius = Enemy->GetPatrolRadius();
	const int32 PointCount = Enemy->GetPatrolPointCount();
	const float Now = GetWorld()->GetTimeSeconds();
	if ((PointCount == 0 && Radius <= 0.0f) || GetMoveStatus() == EPathFollowingStatus::Moving || Now < NextWanderTime)
	{
		return;
	}

	NextWanderTime = Now + FMath::FRandRange(1.5f, 3.0f);

	FVector Destination;
	if (PointCount > 0)
	{
		Destination = Enemy->GetPatrolPointWorld(PatrolIndex % PointCount);
		PatrolIndex = (PatrolIndex + 1) % PointCount;
	}
	else
	{
		const FVector2D Offset = FVector2D(FMath::VRand()).GetSafeNormal() * FMath::FRandRange(Radius * 0.3f, Radius);
		Destination = HomeLocation + FVector(Offset.X, Offset.Y, 0.0f);
	}
	if (MoveToLocation(Destination, 50.0f, true, true) == EPathFollowingRequestResult::Failed)
	{
		MoveToLocation(Destination, 50.0f, true, false);
	}
}
