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

	/** Cosmetic only. Runs on every machine when an attack lands. */
	UFUNCTION(BlueprintImplementableEvent, Category="Enemy")
	void OnEnemyAttack(APawn* Target);

	/** Cosmetic only. Runs on every machine when this enemy dies. */
	UFUNCTION(BlueprintImplementableEvent, Category="Enemy")
	void OnEnemyDied();

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
	float DetectionRange = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy", meta=(ClampMin="50.0", Units="cm"))
	float AttackRange = 170.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy", meta=(ClampMin="0.0"))
	float AttackDamage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy", meta=(ClampMin="0.1", Units="s"))
	float AttackCooldown = 1.2f;

	/** Wander distance from the spawn point while no player is detected. Zero stands still. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy", meta=(ClampMin="0.0", Units="cm"))
	float PatrolRadius = 500.0f;

	/** Seconds the body stays after death. Zero keeps it. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy", meta=(ClampMin="0.0", Units="s"))
	float CorpseLifetime = 20.0f;

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastAttack(APawn* Target);

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
	bool bDeathHandled = false;
};
