// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectEXWeaponRig.generated.h"

class USkeletalMeshComponent;
class UStaticMeshComponent;

/**
 * Editor rig for one weapon's first-person pose. It is not spawned in a level.
 * The root is the camera. Gameplay reads these component transforms.
 */
UCLASS(Blueprintable)
class PROJECTEX_API AProjectEXWeaponRig : public AActor
{
	GENERATED_BODY()

public:

	AProjectEXWeaponRig();

	USceneComponent* GetHipFireAnchor() const { return HipFireAnchor; }
	USceneComponent* GetADSAnchor() const { return ADSAnchor; }
	USkeletalMeshComponent* GetPreviewMesh() const { return PreviewMesh; }

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon|Presentation")
	TObjectPtr<USceneComponent> HipFireAnchor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon|Presentation")
	TObjectPtr<USceneComponent> ADSAnchor;

	/** The rifle. It is attached to HipFireAnchor, so moving that anchor moves the gun. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon|Presentation")
	TObjectPtr<USkeletalMeshComponent> PreviewMesh;

	/** Same mesh on the ADS anchor, so both poses are visible in this Blueprint. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon|Presentation")
	TObjectPtr<USkeletalMeshComponent> ADSPreviewMesh;

	/** Sits on the camera aim line. Line the sights up with it. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon|Presentation")
	TObjectPtr<UStaticMeshComponent> AimMarker;
};
