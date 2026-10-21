// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectEXWeaponData.generated.h"

class AProjectEXWeaponRig;
class UProjectEXItemDefinition;
class USkeletalMesh;
class USoundBase;

UENUM(BlueprintType)
enum class EProjectEXFireMode : uint8
{
	Semi,
	Automatic
};

/** How both hands meet the weapon. Rifle and pistol are different holds. */
UENUM(BlueprintType)
enum class EProjectEXGripStyle : uint8
{
	/** Right hand on the grip, left hand forward on the handguard, elbow down. */
	Rifle,
	/** Both hands together. The left hand wraps the right, thumbs toward the target. */
	Pistol
};

/**
 *  Configurable firearm. Create one data asset per weapon instead of a new C++ class.
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTEX_API UProjectEXWeaponData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	EProjectEXFireMode FireMode = EProjectEXFireMode::Semi;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon", meta=(ClampMin="0.0"))
	float Damage = 20.0f;

	/** Seconds between shots. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon", meta=(ClampMin="0.02", Units="s"))
	float FireInterval = 0.15f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon", meta=(ClampMin="1"))
	int32 MagazineSize = 15;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon", meta=(ClampMin="0.05", Units="s"))
	float ReloadDuration = 1.6f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon", meta=(ClampMin="0.0"))
	float RecoilPitch = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon", meta=(ClampMin="0.0"))
	float RecoilYaw = 0.2f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon", meta=(ClampMin="100.0", Units="cm"))
	float Range = 8000.0f;

	/** Inventory item removed from reserve stacks when reloading. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	TObjectPtr<UProjectEXItemDefinition> AmmoType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual")
	TSoftObjectPtr<USkeletalMesh> ViewMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual")
	FVector ViewOffset = FVector(36.0f, 12.0f, -12.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual")
	FRotator ViewRotation = FRotator(0.0f, -90.0f, 0.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual", meta=(ClampMin="0.01"))
	float ViewScale = 0.85f;

	/** Camera-space pose while aiming. Used when the weapon is not held in the viewmodel hands. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual")
	FVector AdsOffset = FVector(30.0f, 0.0f, -4.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual")
	FRotator AdsRotation = FRotator(0.0f, -90.0f, 0.0f);

	/** Point the sights should meet, in weapon-mesh space. Y runs along the barrel and Z is up. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual")
	FVector SightOffset = FVector(0.0f, -12.0f, 10.0f);

	/** Muzzle position in weapon-mesh space. Tracers and the flash start here. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual")
	FVector MuzzleOffset = FVector(0.0f, 40.0f, 1.0f);

	/** Moves the mesh forward so the hand sits on the grip instead of the mesh center. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual", meta=(Units="cm"))
	float GripOffset = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual")
	EProjectEXGripStyle GripStyle = EProjectEXGripStyle::Rifle;

	/**
	 * Where the right palm meets the weapon, in mesh space.
	 * Y runs along the barrel, Z is up, and positive X is to the shooter's left.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual")
	FVector RightHandOffset = FVector(-3.0f, -18.0f, -9.0f);

	/** Left hand contact. Forward of the grip for a rifle, beside the firing hand for a pistol. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual")
	FVector LeftHandOffset = FVector(7.0f, 14.0f, -6.0f);

	/**
	 * Blueprint whose HipFireAnchor and ADSAnchor place this weapon on the camera.
	 * When set, those transforms drive the gun you see. The rig actor is not spawned.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Presentation")
	TSubclassOf<AProjectEXWeaponRig> PresentationRig;

	/** World camera field of view while fully aimed. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Presentation|ADS", meta=(ClampMin="40.0", ClampMax="120.0", Units="deg"))
	float AdsFOV = 75.0f;

	/** Seconds to move between hip-fire and aimed, in either direction. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Presentation|ADS", meta=(ClampMin="0.01", Units="s"))
	float AdsTransitionDuration = 0.18f;

	/** Look sensitivity while fully aimed. 1 keeps the hip-fire sensitivity. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Presentation|ADS", meta=(ClampMin="0.05", ClampMax="1.0"))
	float AdsLookScale = 0.75f;

	/** Unused by the blend. Kept so existing assets still load. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual", meta=(ClampMin="0.1"))
	float AdsSpeed = 10.0f;

	/** Largest look sway, in degrees. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual", meta=(ClampMin="0.0", Units="deg"))
	float SwayDegrees = 2.2f;

	/** How quickly sway follows the mouse and returns to rest. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual", meta=(ClampMin="0.1"))
	float SwaySpeed = 12.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual", meta=(ClampMin="0.0", Units="cm"))
	float BobHorizontal = 0.85f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual", meta=(ClampMin="0.0", Units="cm"))
	float BobVertical = 0.55f;

	/** Bob cycles per second while moving at normal walk speed. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual", meta=(ClampMin="0.0"))
	float BobSpeed = 1.7f;

	/** Extra bob once movement is faster than the pawn's normal walk speed. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual", meta=(ClampMin="1.0"))
	float SprintBobMultiplier = 1.8f;

	/** Fraction of sway kept while fully aimed. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual", meta=(ClampMin="0.0", ClampMax="1.0"))
	float AimSwayScale = 0.25f;

	/** Fraction of bob kept while fully aimed. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual", meta=(ClampMin="0.0", ClampMax="1.0"))
	float AimBobScale = 0.2f;

	/** Backward mesh kick. Does not change the player's aim. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual", meta=(ClampMin="0.0", Units="cm"))
	float VisualKickDistance = 2.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual", meta=(ClampMin="0.0", Units="deg"))
	float VisualKickPitch = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual", meta=(ClampMin="0.1"))
	float VisualKickRecovery = 16.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual", meta=(ClampMin="0.0", Units="cm"))
	float ReloadDropDistance = 12.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual", meta=(ClampMin="0.0", Units="deg"))
	float ReloadDropPitch = 16.0f;

	/** 0 hides tracers. 1 shows one on every shot. 3 shows every third shot. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual", meta=(ClampMin="0"))
	int32 TracerInterval = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual")
	TSoftObjectPtr<USoundBase> FireSound;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
