// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ProjectEXWeaponViewComponent.generated.h"

class UProjectEXWeaponComponent;
class UProjectEXWeaponData;
class UPoseableMeshComponent;
class USkeletalMeshComponent;

/** Points the weapon's barrel along the holder's hand socket and shifts it onto the grip. */
void ProjectEXAlignWeaponToHand(USkeletalMeshComponent* WeaponMesh, const USkeletalMeshComponent* Holder, FName SocketName, float GripOffset);

/**
 *  Local first-person weapon pose. Sway, bob, aim, and reload motion stay on this
 *  component and are never replicated.
 */
UCLASS(NotBlueprintable, ClassGroup=(Combat))
class PROJECTEX_API UProjectEXWeaponViewComponent : public USceneComponent
{
	GENERATED_BODY()

public:

	UProjectEXWeaponViewComponent();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetWeapon(UProjectEXWeaponData* NewWeapon);
	void NotifyFired();
	bool GetMuzzleLocation(FVector& OutLocation) const;
	float GetAimAlpha() const { return AimAlpha; }

private:

	void UpdateFirstPersonMesh();
	void EnsureArms();
	bool UsesPresentationRig() const;
	void ApplyRigPose();
	void PoseRigHands();
	void AlignArmsToCamera();
	void PlaceHeldWeapon();
	void RestoreCamera() const;

	UPROPERTY(Transient)
	TObjectPtr<UProjectEXWeaponData> Weapon;

	UPROPERTY(Transient)
	TObjectPtr<UPoseableMeshComponent> ArmsMesh;

	UPROPERTY(Transient)
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(Transient)
	TObjectPtr<UProjectEXWeaponComponent> WeaponComponent;

	float AimAlpha = 0.0f;
	float WalkSpeedReference = 600.0f;
	float RestingFieldOfView = 90.0f;
	float RestingFirstPersonFieldOfView = 70.0f;
	bool bCapturedFieldOfView = false;
	bool bHasLastLook = false;
	bool bReloadWasActive = false;
	float ReloadElapsed = 0.0f;
	float ReloadPose = 0.0f;
	float BobPhase = 0.0f;
	FVector BobOffset = FVector::ZeroVector;
	FVector KickOffset = FVector::ZeroVector;
	FRotator KickRotation = FRotator::ZeroRotator;
	FRotator SwayTarget = FRotator::ZeroRotator;
	FRotator Sway = FRotator::ZeroRotator;
	FRotator LastLook = FRotator::ZeroRotator;
	bool bHeldInHands = false;
	bool bArmsAligned = false;
	bool bHandsPosed = false;
};
