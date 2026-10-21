// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ProjectEX.h"
#include "ProjectEXInteractionComponent.h"
#include "ProjectEXInventoryComponent.h"
#include "ProjectEXLootComponent.h"
#include "ProjectEXHealthComponent.h"
#include "ProjectEXWeaponComponent.h"

namespace
{
	const TCHAR* PolygonBodyMeshPath = TEXT("/Game/PolygonPrototype/Meshes/CharacterUE4Mannequin/SK_Character_Dummy_Male_01.SK_Character_Dummy_Male_01");
	const TCHAR* PolygonArmsMeshPath = TEXT("/Game/PolygonPrototype/Meshes/CharacterUE4Mannequin/Hands/SK_Character_FPS_Arms_01.SK_Character_FPS_Arms_01");
	const TCHAR* PolygonBodyAnimPath = TEXT("/Game/PolygonPrototype/EpicContent/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C");
}

AProjectEXCharacter::AProjectEXCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	InteractionComponent = CreateDefaultSubobject<UProjectEXInteractionComponent>(TEXT("Interaction"));
	InventoryComponent = CreateDefaultSubobject<UProjectEXInventoryComponent>(TEXT("Inventory"));
	LootComponent = CreateDefaultSubobject<UProjectEXLootComponent>(TEXT("Loot"));
	HealthComponent = CreateDefaultSubobject<UProjectEXHealthComponent>(TEXT("Health"));
	HealthComponent->SetMaxHealth(100.0f);
	WeaponComponent = CreateDefaultSubobject<UProjectEXWeaponComponent>(TEXT("Weapon"));

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->InitCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = FallingBrakingDeceleration;
	GetCharacterMovement()->AirControl = AirControl;

	// Crouching uses the native character crouch, so the nav agent must allow it.
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkMoveSpeed;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchMoveSpeed;
}

void AProjectEXCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AProjectEXCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AProjectEXCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjectEXCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjectEXCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AProjectEXCharacter::LookInput);

		// Sprinting (held)
		if (SprintInputAction)
		{
			EnhancedInputComponent->BindAction(SprintInputAction, ETriggerEvent::Started, this, &AProjectEXCharacter::DoSprintStart);
			EnhancedInputComponent->BindAction(SprintInputAction, ETriggerEvent::Completed, this, &AProjectEXCharacter::DoSprintEnd);
		}

		// Crouching (toggled)
		if (CrouchInputAction)
		{
			EnhancedInputComponent->BindAction(CrouchInputAction, ETriggerEvent::Started, this, &AProjectEXCharacter::DoCrouchToggle);
		}

		if (InteractionComponent)
		{
			InteractionComponent->BindInput(EnhancedInputComponent);
		}

		if (InventoryComponent)
		{
			InventoryComponent->BindInput(EnhancedInputComponent);
		}

		if (WeaponComponent)
		{
			WeaponComponent->BindInput(EnhancedInputComponent);
		}
	}
	else
	{
		UE_LOG(LogProjectEX, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AProjectEXCharacter::ApplyPolygonMeshes()
{
	if (USkeletalMesh* BodyMesh = LoadObject<USkeletalMesh>(nullptr, PolygonBodyMeshPath))
	{
		GetMesh()->SetSkeletalMeshAsset(BodyMesh);
		if (UClass* BodyAnim = LoadClass<UAnimInstance>(nullptr, PolygonBodyAnimPath))
		{
			GetMesh()->SetAnimInstanceClass(BodyAnim);
		}
	}

	if (USkeletalMesh* ArmsMesh = LoadObject<USkeletalMesh>(nullptr, PolygonArmsMeshPath))
	{
		FirstPersonMesh->SetSkeletalMeshAsset(ArmsMesh);
		FirstPersonMesh->SetAnimInstanceClass(nullptr);
		// The camera stays on this mesh. The visible arms are a local copy under the weapon view.
		FirstPersonMesh->SetVisibility(false);
	}
}

void AProjectEXCharacter::BeginPlay()
{
	if (UCharacterMovementComponent* Movement = GetCharacterMovement())
	{
		Movement->BrakingDecelerationFalling = FallingBrakingDeceleration;
		Movement->AirControl = AirControl;
		Movement->MaxWalkSpeed = WalkMoveSpeed;
		Movement->MaxWalkSpeedCrouched = CrouchMoveSpeed;
	}

	// The first person presentation now uses the native First Person template setup that is
	// already authored on BP_FirstPersonCharacter: SKM_Manny_Simple on the UE5 mannequin
	// skeleton plus ABP_FP_Copy / ABP_FP_Weapon. The old Synty arms override is intentionally
	// not applied any more. It swapped in SK_Character_FPS_Arms_01, which sits on
	// UE4_Mannequin_Skeleton and is therefore incompatible with every first person template
	// animation, and it also nulled the anim class and hid the mesh.
	Super::BeginPlay();

	if (HealthComponent)
	{
		HealthComponent->OnDied.AddDynamic(this, &AProjectEXCharacter::HandleDied);
	}
}

void AProjectEXCharacter::HandleDied(AController* InstigatorController)
{
	if (UCharacterMovementComponent* Movement = GetCharacterMovement())
	{
		Movement->StopMovementImmediately();
		Movement->DisableMovement();
	}
}

void AProjectEXCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void AProjectEXCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void AProjectEXCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		const float Scale = WeaponComponent ? WeaponComponent->GetAimLookScale() : 1.0f;
		AddControllerYawInput(Yaw * Scale);
		AddControllerPitchInput(Pitch * Scale);
	}
}

void AProjectEXCharacter::DoMove(float Right, float Forward)
{
	if (HealthComponent && HealthComponent->IsDead())
	{
		return;
	}

	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void AProjectEXCharacter::DoJumpStart()
{
	if (HealthComponent && HealthComponent->IsDead())
	{
		return;
	}

	// pass Jump to the character
	Jump();
}

void AProjectEXCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

void AProjectEXCharacter::DoSprintStart()
{
	if (HealthComponent && HealthComponent->IsDead())
	{
		return;
	}

	bSprintHeld = true;

	// Sprinting cancels ADS, so the weapon drops straight back to hip-fire.
	if (WeaponComponent && WeaponComponent->IsAiming())
	{
		WeaponComponent->CancelAim();
	}

	UpdateMovementSpeed();
}

void AProjectEXCharacter::DoSprintEnd()
{
	bSprintHeld = false;
	UpdateMovementSpeed();
}

void AProjectEXCharacter::DoCrouchToggle()
{
	if (HealthComponent && HealthComponent->IsDead())
	{
		return;
	}

	// Native crouch. UnCrouch checks head clearance itself, so standing up under
	// geometry is refused rather than clipping the player into it.
	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}

void AProjectEXCharacter::UpdateMovementSpeed()
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	if (!Movement)
	{
		return;
	}

	const bool bAlive = !(HealthComponent && HealthComponent->IsDead());
	const bool bAiming = WeaponComponent && WeaponComponent->IsAiming();

	// Sprint needs the input held, a live pawn, standing on both feet, and no ADS.
	// Requiring !bAiming is what makes ADS block sprinting every frame.
	const bool bSprintActive = bSprintHeld && bAlive && !bIsCrouched && !bAiming;

	Movement->MaxWalkSpeed = bSprintActive ? SprintMoveSpeed : WalkMoveSpeed;
	Movement->MaxWalkSpeedCrouched = CrouchMoveSpeed;
}

void AProjectEXCharacter::UpdateCrouchView(float DeltaSeconds)
{
	if (!FirstPersonCameraComponent)
	{
		return;
	}

	if (DeltaSeconds > 0.0f)
	{
		CrouchViewOffset = FMath::FInterpTo(CrouchViewOffset, 0.0f, DeltaSeconds, CrouchViewInterpSpeed);
	}

	FirstPersonCameraComponent->SetRelativeLocation(
		FVector(BaseCameraLocation.X, BaseCameraLocation.Y, BaseCameraLocation.Z + CrouchViewOffset));
}

void AProjectEXCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);

	// The mesh drops with the capsule, which would snap the socket camera down in one
	// frame. Raise it by the same amount and let it ease back to zero for a smooth descent.
	CrouchViewOffset += ScaledHalfHeightAdjust;
	UpdateCrouchView(0.0f);
	UpdateMovementSpeed();
}

void AProjectEXCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);

	CrouchViewOffset -= ScaledHalfHeightAdjust;
	UpdateCrouchView(0.0f);
	UpdateMovementSpeed();
}

void AProjectEXCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateCrouchView(DeltaSeconds);

	// Cheap reconciliation. Catches aiming, death and crouch changes made outside
	// the movement input path without duplicating the rules in several places.
	UpdateMovementSpeed();
}
