// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXWeaponRig.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

AProjectEXWeaponRig::AProjectEXWeaponRig()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Camera"));
	SetRootComponent(Root);

	HipFireAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("HipFireAnchor"));
	HipFireAnchor->SetupAttachment(Root);

	ADSAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("ADSAnchor"));
	ADSAnchor->SetupAttachment(Root);

	PreviewMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PreviewMesh"));
	PreviewMesh->SetupAttachment(HipFireAnchor);
	PreviewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ADSPreviewMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ADSPreviewMesh"));
	ADSPreviewMesh->SetupAttachment(ADSAnchor);
	ADSPreviewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AimMarker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AimMarker"));
	AimMarker->SetupAttachment(Root);
	AimMarker->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AimMarker->SetRelativeLocation(FVector(80.0f, 0.0f, 0.0f));
	AimMarker->SetRelativeScale3D(FVector(0.04f, 0.04f, 0.04f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (Cube.Succeeded())
	{
		AimMarker->SetStaticMesh(Cube.Object);
	}
}
