// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProjectEXEnemy.generated.h"

class UProjectEXHealthComponent;
class UTextRenderComponent;

/** Hostile melee NPC. The server owns detection, movement, and damage. */
UCLASS(Blueprintable)
class PROJECTEX_API AProjectEXEnemy : public ACharacter
{
	GENERATED_BODY()

public:

	AProjectEXEnemy();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/** Server only. Damages the target when the cooldown has elapsed. Returns true when a hit landed. */
	bool TryAttack(APawn* Target);

	/** Server only. Steers straight at the target when navigation cannot build a path. Null stops it. */
	void SetDirectChaseTarget(AActor* Target);

	UFUNCTION(BlueprintPure, Category="Enemy")
	bool IsDead() const;

	UFUNCTION(BlueprintPure, Category="Enemy")
	UProjectEXHealthComponent* GetHealthComponent() const { return Health; }

	float GetDetectionRange() const { return DetectionRange; }
	float GetAttackRange() const { return AttackRange; }
	float GetPatrolRadius() const { return PatrolRadius; }
	int32 GetPatrolPointCount() const { return PatrolPoints.Num(); }
	FVector GetPatrolPointWorld(int32 Index) const;

	/** Cosmetic only. Runs on every machine when an attack lands. */
	UFUNCTION(BlueprintImplementableEvent, Category="Enemy")
	void OnEnemyAttack(APawn* Target);

	/** Cosmetic only. Runs on every machine when this enemy dies. */
	UFUNCTION(BlueprintImplementableEvent, Category="Enemy")
	void OnEnemyDied();

	/**
	 * Cosmetic only. Runs on every machine that sees this enemy take damage.
	 * bLethal is true on the hit that dropped the enemy to zero health.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="Enemy")
	void OnEnemyHit(float DamageAmount, bool bLethal);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UProjectEXHealthComponent> Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UTextRenderComponent> StatusText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy", meta=(ClampMin="1.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy", meta=(ClampMin="0.0", Units="cm/s"))
	float MoveSpeed = 380.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy", meta=(ClampMin="100.0", Units="cm"))
	float DetectionRange = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy", meta=(ClampMin="50.0", Units="cm"))
	float AttackRange = 170.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy", meta=(ClampMin="0.0"))
	float AttackDamage = 8.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy", meta=(ClampMin="0.1", Units="s"))
	float AttackCooldown = 1.5f;

	/** Patrol route relative to the enemy, visited in order. Empty falls back to wandering within PatrolRadius. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy", meta=(MakeEditWidget="true"))
	TArray<FVector> PatrolPoints;

	/** Wander distance from the spawn point while no player is detected and no patrol route is set. Zero stands still. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy", meta=(ClampMin="0.0", Units="cm"))
	float PatrolRadius = 500.0f;

	/** Seconds the body stays after death. Zero keeps it. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy", meta=(ClampMin="0.0", Units="s"))
	float CorpseLifetime = 20.0f;

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastAttack(APawn* Target);

	/** Replays the cosmetic hit reaction on every client that can see this enemy. */
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastHitReaction(float DamageAmount, bool bLethal);

private:

	UFUNCTION()
	void HandleDied(AController* InstigatorController);

	UFUNCTION()
	void HandleHealthChanged(float NewHealth, float NewMaxHealth);

	void ApplyEnemyMesh();
	void UpdateStatusText();

	TWeakObjectPtr<AActor> DirectChaseTarget;
	float NextAttackTime = 0.0f;
	float AttackFlashUntil = 0.0f;
	float LastKnownHealth = -1.0f;
	bool bDeathHandled = false;
	FTransform SpawnTransform;
};
