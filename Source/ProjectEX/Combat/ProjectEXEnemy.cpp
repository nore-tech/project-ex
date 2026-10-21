// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXEnemy.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PhysicsEngine/PhysicsAsset.h"
#include "ProjectEXEnemyController.h"
#include "ProjectEXHealthComponent.h"
#include "ProjectEXPlayerController.h"
#include "ProjectEX.h"

namespace
{
	const TCHAR* EnemyBodyMeshPath = TEXT("/Game/PolygonPrototype/Meshes/CharacterUE4Mannequin/SK_Character_Dummy_Male_01.SK_Character_Dummy_Male_01");
	const TCHAR* EnemyBodyAnimPath = TEXT("/Game/PolygonPrototype/EpicContent/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C");
	const FColor HostileColor(220, 40, 30);
	const FColor AttackColor(255, 200, 40);
	const FColor DeadColor(120, 120, 120);
}

AProjectEXEnemy::AProjectEXEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(34.0f, 96.0f);
	// Player weapons hitscan on Visibility, which the default Pawn profile ignores.
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -96.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

	Health = CreateDefaultSubobject<UProjectEXHealthComponent>(TEXT("Health"));

	StatusText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("StatusText"));
	StatusText->SetupAttachment(GetCapsuleComponent());
	StatusText->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
	StatusText->SetHorizontalAlignment(EHTA_Center);
	StatusText->SetWorldSize(22.0f);
	StatusText->SetTextRenderColor(HostileColor);
	StatusText->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StatusText->SetAbsolute(false, true, false);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->AvoidanceConsiderationRadius = 300.0f;

	AIControllerClass = AProjectEXEnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AProjectEXEnemy::BeginPlay()
{
	ApplyEnemyMesh();
	SpawnTransform = GetActorTransform();
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

	if (Health)
	{
		Health->SetMaxHealth(MaxHealth);
		if (HasAuthority())
		{
			Health->RestoreFullHealth();
		}
		Health->OnDied.AddDynamic(this, &AProjectEXEnemy::HandleDied);
		Health->OnHealthChanged.AddDynamic(this, &AProjectEXEnemy::HandleHealthChanged);
	}

	UpdateStatusText();
}

void AProjectEXEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (StatusText && !IsDead())
	{
		if (const APlayerController* LocalPlayer = GetWorld()->GetFirstPlayerController())
		{
			if (LocalPlayer->PlayerCameraManager)
			{
				const FVector ToCamera = LocalPlayer->PlayerCameraManager->GetCameraLocation() - StatusText->GetComponentLocation();
				StatusText->SetWorldRotation(FRotator(0.0f, ToCamera.Rotation().Yaw, 0.0f));
			}
		}

		if (AttackFlashUntil > 0.0f && GetWorld()->GetTimeSeconds() >= AttackFlashUntil)
		{
			AttackFlashUntil = 0.0f;
			StatusText->SetTextRenderColor(HostileColor);
		}
	}

	if (HasAuthority() && !IsDead())
	{
		if (AActor* Target = DirectChaseTarget.Get())
		{
			FVector ToTarget = Target->GetActorLocation() - GetActorLocation();
			ToTarget.Z = 0.0f;
			if (ToTarget.Size() > AttackRange * 0.8f)
			{
				AddMovementInput(ToTarget.GetSafeNormal());
			}
		}
	}
}

bool AProjectEXEnemy::IsDead() const
{
	return Health && Health->IsDead();
}

FVector AProjectEXEnemy::GetPatrolPointWorld(int32 Index) const
{
	return PatrolPoints.IsValidIndex(Index) ? SpawnTransform.TransformPosition(PatrolPoints[Index]) : SpawnTransform.GetLocation();
}

bool AProjectEXEnemy::TryAttack(APawn* Target)
{
	if (!HasAuthority() || IsDead() || !Target)
	{
		return false;
	}

	const float Now = GetWorld()->GetTimeSeconds();
	if (Now < NextAttackTime)
	{
		return false;
	}

	UProjectEXHealthComponent* TargetHealth = Target->FindComponentByClass<UProjectEXHealthComponent>();
	if (!TargetHealth || TargetHealth->IsDead())
	{
		return false;
	}

	NextAttackTime = Now + AttackCooldown;

	FProjectEXDamageSpec Spec;
	Spec.Damage = AttackDamage;
	TargetHealth->ApplyDamage(Spec, GetController());
	MulticastAttack(Target);
	return true;
}

void AProjectEXEnemy::SetDirectChaseTarget(AActor* Target)
{
	DirectChaseTarget = Target;
}

void AProjectEXEnemy::MulticastAttack_Implementation(APawn* Target)
{
	if (StatusText)
	{
		StatusText->SetTextRenderColor(AttackColor);
		AttackFlashUntil = GetWorld()->GetTimeSeconds() + 0.25f;
	}
	OnEnemyAttack(Target);
}

void AProjectEXEnemy::HandleDied(AController* InstigatorController)
{
	if (bDeathHandled)
	{
		return;
	}
	bDeathHandled = true;
	DirectChaseTarget.Reset();

	if (UCharacterMovementComponent* Movement = GetCharacterMovement())
	{
		Movement->StopMovementImmediately();
		Movement->DisableMovement();
	}
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	USkeletalMeshComponent* Body = GetMesh();
	if (Body && Body->GetPhysicsAsset())
	{
		Body->SetCollisionProfileName(TEXT("Ragdoll"));
		Body->SetAllBodiesSimulatePhysics(true);
		Body->SetSimulatePhysics(true);
		Body->WakeAllRigidBodies();
	}
	else if (Body)
	{
		Body->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -80.0f), FRotator(0.0f, -90.0f, 90.0f));
		Body->bPauseAnims = true;
	}

	if (HasAuthority())
	{
		UE_LOG(LogProjectEX, Log, TEXT("Enemy %s died (killer %s)"), *GetActorNameOrLabel(), *GetNameSafe(InstigatorController));
		if (AProjectEXPlayerController* Killer = Cast<AProjectEXPlayerController>(InstigatorController))
		{
			Killer->AddRaidKill();
		}
		if (AController* AIController = GetController())
		{
			AIController->StopMovement();
			AIController->UnPossess();
		}
		if (CorpseLifetime > 0.0f)
		{
			SetLifeSpan(CorpseLifetime);
		}
	}

	UpdateStatusText();
	OnEnemyDied();
}

void AProjectEXEnemy::HandleHealthChanged(float NewHealth, float NewMaxHealth)
{
	const float DamageAmount = (LastKnownHealth >= 0.0f) ? (LastKnownHealth - NewHealth) : 0.0f;

	if (StatusText && DamageAmount > 0.0f && NewHealth > 0.0f)
	{
		StatusText->SetTextRenderColor(FColor::White);
		AttackFlashUntil = GetWorld()->GetTimeSeconds() + 0.12f;
	}
	LastKnownHealth = NewHealth;
	UpdateStatusText();

	// Cosmetic only. The health reduction above is the authoritative result and is
	// never delayed by this. Skipped once the body has been handled so a corpse
	// cannot keep flinching.
	if (DamageAmount > 0.0f && !bDeathHandled && HasAuthority())
	{
		MulticastHitReaction(DamageAmount, NewHealth <= 0.0f);
	}
}

void AProjectEXEnemy::MulticastHitReaction_Implementation(float DamageAmount, bool bLethal)
{
	OnEnemyHit(DamageAmount, bLethal);
}

void AProjectEXEnemy::ApplyEnemyMesh()
{
	if (GetMesh()->GetSkeletalMeshAsset())
	{
		return;
	}

	if (USkeletalMesh* BodyMesh = LoadObject<USkeletalMesh>(nullptr, EnemyBodyMeshPath))
	{
		GetMesh()->SetSkeletalMeshAsset(BodyMesh);
		if (UClass* BodyAnim = LoadClass<UAnimInstance>(nullptr, EnemyBodyAnimPath))
		{
			GetMesh()->SetAnimInstanceClass(BodyAnim);
		}
	}
}

void AProjectEXEnemy::UpdateStatusText()
{
	if (!StatusText || !Health)
	{
		return;
	}

	if (IsDead())
	{
		StatusText->SetText(FText::FromString(TEXT("DEAD")));
		StatusText->SetTextRenderColor(DeadColor);
		return;
	}

	StatusText->SetText(FText::FromString(FString::Printf(TEXT("HOSTILE %d"), FMath::CeilToInt(Health->GetHealth()))));
}
