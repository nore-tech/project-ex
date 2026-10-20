// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "ProjectEXItemDefinition.h"
#include "ProjectEXWeaponComponent.generated.h"

class UInputAction;
class UInputMappingContext;
class UProjectEXCombatHudWidget;
class UProjectEXWeaponData;
class UProjectEXWeaponViewComponent;
class USkeletalMeshComponent;
class UStaticMeshComponent;

/** Equips a weapon item from the inventory and fires it with server-authoritative hits. */
UCLASS(Blueprintable, ClassGroup=(Combat), meta=(BlueprintSpawnableComponent))
class PROJECTEX_API UProjectEXWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UProjectEXWeaponComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void BindInput(class UEnhancedInputComponent* EnhancedInput);

	UFUNCTION(BlueprintPure, Category="Weapon")
	UProjectEXWeaponData* GetEquippedWeapon() const { return EquippedWeapon; }

	UFUNCTION(BlueprintPure, Category="Weapon")
	int32 GetMagazine() const;

	UFUNCTION(BlueprintPure, Category="Weapon")
	int32 GetReserveAmmo() const;

	UFUNCTION(BlueprintPure, Category="Weapon")
	bool IsReloading() const { return bReloading || bPredictReloading; }

	UFUNCTION(BlueprintPure, Category="Weapon")
	bool IsAiming() const;

	/** Cosmetic only. Runs after the server accepts a shot and multicasts the shot effect. */
	UFUNCTION(BlueprintImplementableEvent, Category="Weapon|Presentation")
	void OnWeaponFired();

	/** Cosmetic only. Runs after a reload consumes reserve ammunition. */
	UFUNCTION(BlueprintImplementableEvent, Category="Weapon|Presentation")
	void OnWeaponReloaded();

	/** Look input added by gameplay recoil this frame, so the viewmodel does not sway from it. */
	float ConsumeRecoilPitch();
	float ConsumeRecoilYaw();

protected:

	UPROPERTY(ReplicatedUsing=OnRep_EquippedWeapon)
	TObjectPtr<UProjectEXWeaponData> EquippedWeapon;

	UPROPERTY(Replicated)
	EProjectEXEquipmentSlot ActiveWeaponSlot = EProjectEXEquipmentSlot::PrimaryWeapon;

	UPROPERTY(ReplicatedUsing=OnRep_Reloading)
	bool bReloading = false;

	UFUNCTION(Server, Reliable)
	void ServerFire();

	UFUNCTION(Server, Reliable)
	void ServerReload();

	UFUNCTION(Server, Reliable)
	void ServerCycleWeapon();

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastFireFX(FVector TraceStart, FVector TraceEnd);

	UFUNCTION(Client, Reliable)
	void ClientSetReloading(bool bNewReloading);

	/** Hit marker for the shooter. */
	UFUNCTION(Client, Unreliable)
	void ClientConfirmHit(bool bKilled);

	UFUNCTION()
	void OnRep_EquippedWeapon();

	UFUNCTION()
	void OnRep_Reloading();

private:

	void TryFire();
	void FirePressed();
	void FireHeld();
	void AimPressed();
	void AimReleased();
	void TryReload();
	void TryCycle();
	bool CanUseWeapon() const;
	bool IsSemiAutomatic() const;
	void ApplyLocalRecoil();
	void EnsureEquippedMagazine();
	void SyncEquippedWeapon();
	void ClearEquipped();
	void FinishReload();
	void RefreshMeshes();
	void ClearMeshes();
	void EnsureView();
	void PlayPredictedFireFX();
	void PlayShotFlash(const FVector& Location) const;
	void PlayShotSound(const FVector& Location) const;
	FVector GetMuzzleLocation(const FVector& Fallback) const;
	USkeletalMeshComponent* CreateWorldMesh();

	UFUNCTION()
	void HandleInventoryChanged();

	UPROPERTY(Transient)
	TObjectPtr<UInputAction> FireAction;

	UPROPERTY(Transient)
	TObjectPtr<UInputAction> AimAction;

	UPROPERTY(Transient)
	TObjectPtr<UInputAction> ReloadAction;

	UPROPERTY(Transient)
	TObjectPtr<UInputAction> CycleAction;

	UPROPERTY(Transient)
	TObjectPtr<UInputMappingContext> WeaponMappingContext;

	UPROPERTY(Transient)
	TObjectPtr<UProjectEXWeaponViewComponent> View;

	UPROPERTY(Transient)
	TObjectPtr<USkeletalMeshComponent> WorldMesh;

	TObjectPtr<UProjectEXWeaponData> MeshWeapon;

	UPROPERTY(Transient)
	TObjectPtr<UProjectEXCombatHudWidget> HudWidget;

	FTimerHandle ReloadTimer;
	FTimerHandle MeshTimer;
	float LocalNextFireTime = 0.0f;
	float ServerNextFireTime = 0.0f;
	float PendingRecoilPitch = 0.0f;
	float PendingRecoilYaw = 0.0f;
	int32 TracerCounter = 0;
	bool bMappingRegistered = false;
	bool bPredictReloading = false;
	bool bAimHeld = false;
};

/** Thin hitscan streak. Cosmetic only, and not replicated. */
UCLASS()
class PROJECTEX_API AProjectEXTracer : public AActor
{
	GENERATED_BODY()

public:

	AProjectEXTracer();

	void SetSegment(const FVector& Start, const FVector& End);

private:

	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> Beam;
};

/** Short-lived light used as a muzzle flash. */
UCLASS()
class PROJECTEX_API AProjectEXShotFlash : public AActor
{
	GENERATED_BODY()

public:

	AProjectEXShotFlash();
};
