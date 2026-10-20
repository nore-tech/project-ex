// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXExtractionZone.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "ProjectEX.h"
#include "ProjectEXHealthComponent.h"
#include "ProjectEXPlayerController.h"
#include "UObject/ConstructorHelpers.h"

namespace
{
	constexpr float PadHeight = 6.0f;
	constexpr float BeaconHeight = 600.0f;
	constexpr float BeaconRadius = 18.0f;
	constexpr float VerticalTolerance = 250.0f;
}

AProjectEXExtractionZone::AProjectEXExtractionZone()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.1f;
	bReplicates = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> ShapeMaterial(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Pad = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pad"));
	Pad->SetupAttachment(Root);
	Pad->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Pad->SetCanEverAffectNavigation(false);
	Pad->SetCastShadow(false);

	Beacon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Beacon"));
	Beacon->SetupAttachment(Root);
	Beacon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Beacon->SetCanEverAffectNavigation(false);
	Beacon->SetCastShadow(false);

	if (CylinderMesh.Succeeded())
	{
		Pad->SetStaticMesh(CylinderMesh.Object);
		Beacon->SetStaticMesh(CylinderMesh.Object);
	}
	if (ShapeMaterial.Succeeded())
	{
		Pad->SetMaterial(0, ShapeMaterial.Object);
		Beacon->SetMaterial(0, ShapeMaterial.Object);
	}

	Label = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Label"));
	Label->SetupAttachment(Root);
	Label->SetHorizontalAlignment(EHTA_Center);
	Label->SetWorldSize(48.0f);
	Label->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Label->SetAbsolute(false, true, false);
}

void AProjectEXExtractionZone::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	ApplyVisuals();
}

void AProjectEXExtractionZone::ApplyVisuals()
{
	// The engine cylinder is 100 cm wide and 100 cm tall with its pivot at the center.
	Pad->SetRelativeScale3D(FVector(Radius / 50.0f, Radius / 50.0f, PadHeight / 100.0f));
	Pad->SetRelativeLocation(FVector(0.0f, 0.0f, PadHeight * 0.5f));
	Beacon->SetRelativeScale3D(FVector(BeaconRadius / 50.0f, BeaconRadius / 50.0f, BeaconHeight / 100.0f));
	Beacon->SetRelativeLocation(FVector(0.0f, 0.0f, BeaconHeight * 0.5f));
	Label->SetRelativeLocation(FVector(0.0f, 0.0f, BeaconHeight + 60.0f));
	Label->SetText(FText::FromString(FString::Printf(TEXT("EXTRACT: %s"), *DisplayName.ToString())));
	Label->SetTextRenderColor(ZoneColor.ToFColor(true));

	for (UStaticMeshComponent* Part : { Pad.Get(), Beacon.Get() })
	{
		if (Part && Part->GetMaterial(0))
		{
			UMaterialInstanceDynamic* Material = Part->CreateDynamicMaterialInstance(0, Part->GetMaterial(0));
			if (Material)
			{
				Material->SetVectorParameterValue(TEXT("Color"), ZoneColor);
			}
		}
	}
}

bool AProjectEXExtractionZone::IsInside(const APawn* Pawn) const
{
	if (!Pawn)
	{
		return false;
	}
	const FVector Offset = Pawn->GetActorLocation() - GetActorLocation();
	return FVector2D(Offset).SizeSquared() <= FMath::Square(Radius) && FMath::Abs(Offset.Z) <= VerticalTolerance;
}

void AProjectEXExtractionZone::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (const APlayerController* LocalPlayer = GetWorld()->GetFirstPlayerController())
	{
		if (LocalPlayer->PlayerCameraManager && Label)
		{
			const FVector ToCamera = LocalPlayer->PlayerCameraManager->GetCameraLocation() - Label->GetComponentLocation();
			Label->SetWorldRotation(FRotator(0.0f, ToCamera.Rotation().Yaw, 0.0f));
		}
	}

	if (!HasAuthority())
	{
		return;
	}

	const float Now = GetWorld()->GetTimeSeconds();
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AProjectEXPlayerController* PC = Cast<AProjectEXPlayerController>(It->Get());
		if (!PC)
		{
			continue;
		}

		const APawn* Pawn = PC->GetPawn();
		const UProjectEXHealthComponent* Health = Pawn ? Pawn->FindComponentByClass<UProjectEXHealthComponent>() : nullptr;
		const bool bEligible = PC->IsInRaid() && Health && !Health->IsDead() && IsInside(Pawn);

		if (!bEligible)
		{
			if (EnterTimes.Remove(PC) > 0)
			{
				PC->SetExtractionProgress(-1, DisplayName);
				UE_LOG(LogProjectEX, Log, TEXT("Extraction cancelled for %s at %s"), *PC->GetName(), *DisplayName.ToString());
			}
			continue;
		}

		if (!EnterTimes.Contains(PC))
		{
			UE_LOG(LogProjectEX, Log, TEXT("Extraction started for %s at %s"), *PC->GetName(), *DisplayName.ToString());
		}
		const float EnterTime = EnterTimes.FindOrAdd(PC, Now);
		const float Remaining = Countdown - (Now - EnterTime);
		if (Remaining <= 0.0f)
		{
			EnterTimes.Remove(PC);
			PC->CompleteExtraction(DisplayName);
			OnPlayerExtracted(PC);
			continue;
		}
		PC->SetExtractionProgress(FMath::CeilToInt(Remaining), DisplayName);
	}
}
