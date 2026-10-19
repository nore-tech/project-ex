// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXPickup.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AProjectEXPickup::AProjectEXPickup()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneRoot);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SceneRoot);
	Mesh->SetRelativeScale3D(FVector(0.4f));
	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		Mesh->SetStaticMesh(CubeMesh.Object);
	}

	Mesh->SetCollisionProfileName(FName("BlockAllDynamic"));
	Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	InteractionPrompt = NSLOCTEXT("ProjectEX", "PickupPrompt", "Pick Up");

	SetReplicates(true);
	SetReplicateMovement(false);
}

FText AProjectEXPickup::GetInteractionPrompt_Implementation() const
{
	return InteractionPrompt;
}

bool AProjectEXPickup::CanInteract_Implementation(APawn* Interactor) const
{
	return Interactor != nullptr && !IsActorBeingDestroyed();
}

void AProjectEXPickup::Interact_Implementation(APawn* Interactor)
{
	if (HasAuthority())
	{
		Destroy();
	}
}
