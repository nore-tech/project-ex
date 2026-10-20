// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectEXHealthComponent.generated.h"

class AController;

/** Incoming hit. Armor and medical items can later read DamageType and the hit bone. */
USTRUCT(BlueprintType)
struct FProjectEXDamageSpec
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	float Damage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	bool bHeadshot = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	FName HitBone = NAME_None;

	/** Item id of the ammunition, when the hit came from a firearm. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	FName DamageType = NAME_None;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FProjectEXHealthChanged, float, Health, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FProjectEXDamageApplied, float, AppliedDamage, bool, bHeadshot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FProjectEXDied, AController*, InstigatorController);

UCLASS(ClassGroup=(Combat), meta=(BlueprintSpawnableComponent))
class PROJECTEX_API UProjectEXHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UProjectEXHealthComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintPure, Category="Health")
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintPure, Category="Health")
	float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintPure, Category="Health")
	bool IsDead() const { return bDead; }

	UFUNCTION(BlueprintCallable, Category="Health")
	void SetMaxHealth(float InMaxHealth);

	/** Server only. Returns the health actually removed after the headshot multiplier. */
	float ApplyDamage(const FProjectEXDamageSpec& Spec, AController* InstigatorController);

	/** Server only. Restores health without reloading the level. */
	UFUNCTION(BlueprintCallable, Category="Health")
	void RestoreFullHealth();

	/** Server only. Adds health up to the maximum. Dead players are not revived. Returns the amount restored. */
	UFUNCTION(BlueprintCallable, Category="Health")
	float Heal(float Amount);

	UPROPERTY(BlueprintAssignable, Category="Health")
	FProjectEXHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="Health")
	FProjectEXDamageApplied OnDamageApplied;

	UPROPERTY(BlueprintAssignable, Category="Health")
	FProjectEXDied OnDied;

protected:

	/** Override point for armor, limb modifiers, or medical effects. */
	virtual float ModifyIncomingDamage(float InDamage, const FProjectEXDamageSpec& Spec) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Health", meta=(ClampMin="1.0"))
	float MaxHealth = 100.0f;

	/** Applied when the damage spec marks a headshot. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Health", meta=(ClampMin="1.0"))
	float HeadshotMultiplier = 2.0f;

	UPROPERTY(ReplicatedUsing=OnRep_Status)
	float Health = 100.0f;

	UPROPERTY(ReplicatedUsing=OnRep_Status)
	bool bDead = false;

	UFUNCTION()
	void OnRep_Status();

private:

	void BroadcastStatus();

	bool bDeathDispatched = false;
};
