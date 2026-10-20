// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXPickup.h"
#include "ProjectEX.h"
#include "ProjectEXInventoryComponent.h"
#include "ProjectEXItemDefinition.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

AProjectEXPickup::AProjectEXPickup()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	// The mesh is the root so simulated physics replicates through the actor.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetMobility(EComponentMobility::Movable);
	Mesh->SetRelativeScale3D(FVector(0.4f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		Mesh->SetStaticMesh(CubeMesh.Object);
	}

	ConfigureMeshCollision();

	InteractionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionVolume"));
	InteractionVolume->SetupAttachment(Mesh);
	InteractionVolume->SetBoxExtent(FVector(40.0f, 40.0f, 40.0f));
	InteractionVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionVolume->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	InteractionVolume->SetGenerateOverlapEvents(false);
	InteractionVolume->SetCanEverAffectNavigation(false);
	InteractionVolume->SetUsingAbsoluteScale(true);
	InteractionVolume->SetRelativeScale3D(FVector::OneVector);

	DisplaySkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DisplaySkeletalMesh"));
	DisplaySkeletalMesh->SetupAttachment(Mesh);
	DisplaySkeletalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DisplaySkeletalMesh->SetUsingAbsoluteScale(true);
	DisplaySkeletalMesh->SetCastShadow(true);
	DisplaySkeletalMesh->SetVisibility(false);

	InteractionPrompt = NSLOCTEXT("ProjectEX", "PickupPrompt", "Pick Up");

	SetReplicates(true);
	SetReplicateMovement(false);
}

void AProjectEXPickup::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	ApplyVisuals();
}

void AProjectEXPickup::BeginPlay()
{
	Super::BeginPlay();
	ApplyVisuals();
}

void AProjectEXPickup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!HasAuthority() || !bDropPhysicsActive || !Mesh)
	{
		return;
	}

	DropPhysicsElapsed += DeltaSeconds;

	const float LinearSpeed = Mesh->GetPhysicsLinearVelocity().Size();
	const float AngularSpeed = Mesh->GetPhysicsAngularVelocityInDegrees().Size();
	if (LinearSpeed <= DropRestSpeed && AngularSpeed <= DropRestAngularSpeed)
	{
		DropRestElapsed += DeltaSeconds;
	}
	else
	{
		DropRestElapsed = 0.0f;
	}

	if (DropRestElapsed >= DropRestTime || DropPhysicsElapsed >= MaxDropPhysicsTime)
	{
		SettleDropPhysics();
	}
}

void AProjectEXPickup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AProjectEXPickup, ItemDefinition);
	DOREPLIFETIME(AProjectEXPickup, Quantity);
	DOREPLIFETIME(AProjectEXPickup, StoredMagazine);
}

FText AProjectEXPickup::GetInteractionPrompt_Implementation() const
{
	if (ItemDefinition)
	{
		if (!ItemDefinition->DisplayName.IsEmpty())
		{
			return ItemDefinition->DisplayName;
		}

		return FText::FromName(ItemDefinition->GetItemId());
	}

	return InteractionPrompt;
}

bool AProjectEXPickup::CanInteract_Implementation(APawn* Interactor) const
{
	return Interactor != nullptr
		&& !bCollected
		&& !IsActorBeingDestroyed()
		&& ItemDefinition != nullptr
		&& Quantity > 0;
}

void AProjectEXPickup::Interact_Implementation(APawn* Interactor)
{
	if (!HasAuthority() || bCollected || !Interactor || !ItemDefinition || Quantity <= 0 || IsActorBeingDestroyed())
	{
		return;
	}

	UProjectEXInventoryComponent* Inventory = Interactor->FindComponentByClass<UProjectEXInventoryComponent>();
	if (!Inventory)
	{
		return;
	}

	bCollected = true;
	const int32 Added = Inventory->AddItem(ItemDefinition, Quantity, StoredMagazine);
	if (Added != Quantity)
	{
		bCollected = false;
		UE_LOG(LogProjectEX, Log, TEXT("%s could not collect %s. The inventory did not have room for the full stack, so the pickup was left unchanged."), *GetNameSafe(Interactor), *GetNameSafe(ItemDefinition));
		return;
	}

	Destroy();
}

void AProjectEXPickup::SetItemStack(UProjectEXItemDefinition* InDefinition, int32 InQuantity)
{
	if (HasActorBegunPlay() && !HasAuthority())
	{
		return;
	}

	ItemDefinition = InDefinition;
	Quantity = FMath::Max(0, InQuantity);
	ApplyVisuals();
}

void AProjectEXPickup::SetStoredMagazine(int32 InMagazineRounds)
{
	if (HasActorBegunPlay() && !HasAuthority())
	{
		return;
	}

	StoredMagazine = InMagazineRounds;
}

void AProjectEXPickup::OnRep_ItemStack()
{
	ApplyVisuals();
}

void AProjectEXPickup::ApplyVisuals()
{
	if (!Mesh || !ItemDefinition)
	{
		return;
	}

	if (UStaticMesh* WorldMesh = ItemDefinition->WorldMesh.LoadSynchronous())
	{
		const bool bWasSimulating = Mesh->IsSimulatingPhysics();
		Mesh->SetStaticMesh(WorldMesh);
		const float ScaledExtent = (WorldMesh->GetBounds().BoxExtent * Mesh->GetRelativeScale3D()).GetAbsMax();
		if (ScaledExtent > 45.0f)
		{
			Mesh->SetRelativeScale3D(Mesh->GetRelativeScale3D() * (45.0f / ScaledExtent));
		}
		else if (ScaledExtent > KINDA_SMALL_NUMBER && ScaledExtent < 18.0f)
		{
			Mesh->SetRelativeScale3D(Mesh->GetRelativeScale3D() * (22.0f / ScaledExtent));
		}
		ConfigureMeshCollision();
		if (bWasSimulating)
		{
			Mesh->SetSimulatePhysics(true);
		}
	}

	USkeletalMesh* SkeletalMesh = ItemDefinition->WorldMesh.IsNull()
		? ItemDefinition->DisplaySkeletalMesh.LoadSynchronous()
		: nullptr;
	if (SkeletalMesh && DisplaySkeletalMesh)
	{
		DisplaySkeletalMesh->SetSkeletalMeshAsset(SkeletalMesh);
		DisplaySkeletalMesh->SetWorldScale3D(FVector(ItemDefinition->DisplaySkeletalScale));
		DisplaySkeletalMesh->SetRelativeRotation(ItemDefinition->DisplaySkeletalRotation);
		DisplaySkeletalMesh->SetVisibility(true);
		Mesh->SetVisibility(false);
	}
	else
	{
		Mesh->SetVisibility(true);
		if (DisplaySkeletalMesh)
		{
			DisplaySkeletalMesh->SetVisibility(false);
		}
	}

	if (InteractionVolume)
	{
		InteractionVolume->SetUsingAbsoluteScale(true);
		InteractionVolume->SetRelativeScale3D(FVector::OneVector);
	}
}

void AProjectEXPickup::ConfigureMeshCollision()
{
	if (!Mesh)
	{
		return;
	}

	Mesh->SetCollisionProfileName(FName("BlockAllDynamic"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AProjectEXPickup::StartDropPhysics()
{
	if (!HasAuthority() || !Mesh || bCollected)
	{
		return;
	}

	SetReplicateMovement(true);
	SetPhysicsReplicationMode(EPhysicsReplicationMode::Default);
	ConfigureMeshCollision();
	Mesh->SetEnableGravity(true);
	Mesh->SetUseCCD(true);
	Mesh->SetLinearDamping(0.5f);
	Mesh->SetAngularDamping(0.8f);
	Mesh->SetSimulatePhysics(true);
	Mesh->WakeAllRigidBodies();

	if (!Mesh->IsSimulatingPhysics())
	{
		UE_LOG(LogProjectEX, Warning, TEXT("Dropped %s could not start physics, so it will stay where it spawned."), *GetName());
		return;
	}

	UE_LOG(LogProjectEX, Log, TEXT("Drop physics started for %s."), *GetName());

	bDropPhysicsActive = true;
	DropRestElapsed = 0.0f;
	DropPhysicsElapsed = 0.0f;
	SetActorTickEnabled(true);

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUObject(this, &AProjectEXPickup::ApplyDropImpulse));
	}
}

void AProjectEXPickup::ApplyDropImpulse()
{
	if (!bDropPhysicsActive || !Mesh || !Mesh->IsSimulatingPhysics())
	{
		return;
	}

	const FVector TossDirection = GetActorForwardVector().GetSafeNormal();
	if (!TossDirection.IsNearlyZero())
	{
		Mesh->AddImpulse(TossDirection * DropImpulseSpeed, NAME_None, true);
	}
}

void AProjectEXPickup::SettleDropPhysics()
{
	bDropPhysicsActive = false;
	SetActorTickEnabled(false);

	if (Mesh)
	{
		Mesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
		Mesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
		Mesh->SetSimulatePhysics(false);
		ConfigureMeshCollision();
	}

	ForceNetUpdate();
}
