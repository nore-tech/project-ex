// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXTargetDummy.h"
#include "ProjectEXHealthComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"

AProjectEXTargetDummy::AProjectEXTargetDummy()
{
	bReplicates = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	SetRootComponent(Body);
	Body->SetRelativeScale3D(FVector(0.45f, 0.45f, 1.7f));

	Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	Head->SetupAttachment(Body);
	Head->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.22f));
	Head->SetRelativeLocation(FVector(0.0f, 0.0f, 58.0f));
	Head->ComponentTags.Add(TEXT("Head"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cylinder(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (Cylinder.Succeeded())
	{
		Body->SetStaticMesh(Cylinder.Object);
	}
	if (Sphere.Succeeded())
	{
		Head->SetStaticMesh(Sphere.Object);
	}

	Health = CreateDefaultSubobject<UProjectEXHealthComponent>(TEXT("Health"));
	Health->SetMaxHealth(100.0f);

	FeedbackText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Feedback"));
	FeedbackText->SetupAttachment(Body);
	FeedbackText->SetRelativeLocation(FVector(0.0f, 40.0f, 70.0f));
	FeedbackText->SetHorizontalAlignment(EHTA_Center);
	FeedbackText->SetWorldSize(18.0f);
	FeedbackText->SetText(NSLOCTEXT("ProjectEX", "DummyReady", "HP 100"));
}

void AProjectEXTargetDummy::BeginPlay()
{
	Super::BeginPlay();

	if (Health)
	{
		Health->OnDamageApplied.AddDynamic(this, &AProjectEXTargetDummy::HandleDamage);
	}

	if (UMaterialInterface* BaseMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial")))
	{
		if (UMaterialInstanceDynamic* BodyMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this))
		{
			BodyMaterial->SetVectorParameterValue(TEXT("Color"), FLinearColor(0.75f, 0.72f, 0.62f));
			Body->SetMaterial(0, BodyMaterial);
		}

		if (UMaterialInstanceDynamic* HeadMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this))
		{
			HeadMaterial->SetVectorParameterValue(TEXT("Color"), FLinearColor(0.75f, 0.28f, 0.2f));
			Head->SetMaterial(0, HeadMaterial);
		}
	}
}

FText AProjectEXTargetDummy::GetInteractionPrompt_Implementation() const
{
	return NSLOCTEXT("ProjectEX", "ResetDummy", "Reset Target");
}

bool AProjectEXTargetDummy::CanInteract_Implementation(APawn* Interactor) const
{
	return Interactor != nullptr;
}

void AProjectEXTargetDummy::Interact_Implementation(APawn* Interactor)
{
	if (!HasAuthority() || !Health)
	{
		return;
	}

	Health->RestoreFullHealth();
	UpdateFeedback(TEXT("Reset\nHP 100"));
}

void AProjectEXTargetDummy::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AProjectEXTargetDummy, Feedback);
}

void AProjectEXTargetDummy::OnRep_Feedback()
{
	if (FeedbackText)
	{
		FeedbackText->SetText(FText::FromString(Feedback));
	}
}

void AProjectEXTargetDummy::HandleDamage(float AppliedDamage, bool bHeadshot)
{
	const float Current = Health ? Health->GetHealth() : 0.0f;
	const FString Hit = bHeadshot ? TEXT("HEAD") : TEXT("BODY");
	UpdateFeedback(FString::Printf(TEXT("%s  %.0f\nHP %.0f"), *Hit, AppliedDamage, Current));
}

void AProjectEXTargetDummy::UpdateFeedback(const FString& Message)
{
	Feedback = Message;
	if (FeedbackText)
	{
		FeedbackText->SetText(FText::FromString(Feedback));
	}

	if (HasAuthority())
	{
		ForceNetUpdate();
	}
}
