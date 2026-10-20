// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXDamagePad.h"
#include "ProjectEXHealthComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

AProjectEXDamagePad::AProjectEXDamagePad()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	bReplicates = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SceneRoot);
	Mesh->SetRelativeScale3D(FVector(1.4f, 1.4f, 0.12f));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (Cube.Succeeded())
	{
		Mesh->SetStaticMesh(Cube.Object);
	}

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(SceneRoot);
	Trigger->SetBoxExtent(FVector(70.0f, 70.0f, 60.0f));
	Trigger->SetCollisionProfileName(FName("OverlapAllDynamic"));
	Trigger->SetGenerateOverlapEvents(true);

	Label = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Label"));
	Label->SetupAttachment(SceneRoot);
	Label->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
	Label->SetHorizontalAlignment(EHTA_Center);
	Label->SetWorldSize(22.0f);
	Label->SetText(NSLOCTEXT("ProjectEX", "DamagePadLabel", "DAMAGE"));
}

void AProjectEXDamagePad::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(HasAuthority());

	if (UMaterialInterface* BaseMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial")))
	{
		if (UMaterialInstanceDynamic* Material = UMaterialInstanceDynamic::Create(BaseMaterial, this))
		{
			Material->SetVectorParameterValue(TEXT("Color"), FLinearColor(0.75f, 0.12f, 0.1f));
			Mesh->SetMaterial(0, Material);
		}
	}
}

void AProjectEXDamagePad::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!HasAuthority() || !Trigger || !GetWorld())
	{
		return;
	}

	const float Now = GetWorld()->GetTimeSeconds();
	TArray<AActor*> Overlapping;
	Trigger->GetOverlappingActors(Overlapping, APawn::StaticClass());
	for (AActor* Actor : Overlapping)
	{
		APawn* Pawn = Cast<APawn>(Actor);
		if (!Pawn || !Pawn->IsPlayerControlled())
		{
			continue;
		}

		float& NextTime = NextDamageTime.FindOrAdd(Pawn);
		if (Now >= NextTime)
		{
			DamagePawn(Pawn);
			NextTime = Now + DamageInterval;
		}
	}
}

void AProjectEXDamagePad::DamagePawn(APawn* Pawn)
{
	UProjectEXHealthComponent* Health = Pawn ? Pawn->FindComponentByClass<UProjectEXHealthComponent>() : nullptr;
	if (!Health || Health->IsDead())
	{
		return;
	}

	FProjectEXDamageSpec Spec;
	Spec.Damage = Damage;
	Health->ApplyDamage(Spec, nullptr);
}
