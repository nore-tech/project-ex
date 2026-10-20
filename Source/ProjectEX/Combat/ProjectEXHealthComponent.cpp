// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXHealthComponent.h"
#include "Net/UnrealNetwork.h"

UProjectEXHealthComponent::UProjectEXHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	Health = MaxHealth;
}

void UProjectEXHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UProjectEXHealthComponent, Health);
	DOREPLIFETIME(UProjectEXHealthComponent, bDead);
}

void UProjectEXHealthComponent::SetMaxHealth(float InMaxHealth)
{
	MaxHealth = FMath::Max(1.0f, InMaxHealth);
	if (Health > MaxHealth)
	{
		Health = MaxHealth;
	}
}

float UProjectEXHealthComponent::ModifyIncomingDamage(float InDamage, const FProjectEXDamageSpec& Spec) const
{
	float Scaled = InDamage;
	if (Spec.bHeadshot)
	{
		Scaled *= FMath::Max(1.0f, HeadshotMultiplier);
	}

	return Scaled;
}

float UProjectEXHealthComponent::ApplyDamage(const FProjectEXDamageSpec& Spec, AController* InstigatorController)
{
	AActor* Owner = GetOwner();
	if (!Owner || !Owner->HasAuthority() || bDead || Spec.Damage <= 0.0f)
	{
		return 0.0f;
	}

	const float Applied = FMath::Max(0.0f, ModifyIncomingDamage(Spec.Damage, Spec));
	if (Applied <= 0.0f)
	{
		return 0.0f;
	}

	Health = FMath::Max(0.0f, Health - Applied);
	OnDamageApplied.Broadcast(Applied, Spec.bHeadshot);

	if (Health <= 0.0f && !bDeathDispatched)
	{
		bDead = true;
		bDeathDispatched = true;
		OnDied.Broadcast(InstigatorController);
	}

	BroadcastStatus();
	Owner->ForceNetUpdate();
	return Applied;
}

float UProjectEXHealthComponent::Heal(float Amount)
{
	AActor* Owner = GetOwner();
	if (!Owner || !Owner->HasAuthority() || bDead || Amount <= 0.0f || Health >= MaxHealth)
	{
		return 0.0f;
	}

	const float Before = Health;
	Health = FMath::Min(MaxHealth, Health + Amount);
	BroadcastStatus();
	Owner->ForceNetUpdate();
	return Health - Before;
}

void UProjectEXHealthComponent::RestoreFullHealth()
{
	AActor* Owner = GetOwner();
	if (!Owner || !Owner->HasAuthority())
	{
		return;
	}

	Health = MaxHealth;
	bDead = false;
	bDeathDispatched = false;
	BroadcastStatus();
	Owner->ForceNetUpdate();
}

void UProjectEXHealthComponent::OnRep_Status()
{
	const bool bAnnounceDeath = bDead && !bDeathDispatched;
	if (bDead)
	{
		bDeathDispatched = true;
	}

	BroadcastStatus();
	if (bAnnounceDeath)
	{
		OnDied.Broadcast(nullptr);
	}
}

void UProjectEXHealthComponent::BroadcastStatus()
{
	OnHealthChanged.Broadcast(Health, MaxHealth);
}
