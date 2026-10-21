// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXWeaponViewComponent.h"
#include "ProjectEXCharacter.h"
#include "ProjectEXWeaponComponent.h"
#include "ProjectEXWeaponData.h"
#include "ProjectEXWeaponRig.h"
#include "Camera/CameraComponent.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "Math/RotationMatrix.h"
#include "TwoBoneIK.h"

namespace
{
	const TCHAR* ViewmodelArmsPath = TEXT("/Game/PolygonPrototype/Meshes/CharacterUE4Mannequin/Hands/SK_Character_FPS_Arms_01.SK_Character_FPS_Arms_01");

	struct FProjectEXHandAim
	{
		FVector Finger = FVector::XAxisVector;
		FVector BackOfHand = FVector::ZAxisVector;
	};

	struct FProjectEXHold
	{
		FVector RightHandView = FVector(34.0f, 8.0f, -16.0f);
		FVector RightElbowView = FVector(8.0f, 30.0f, -34.0f);
		FVector LeftElbowView = FVector(16.0f, -20.0f, -30.0f);
		FProjectEXHandAim RightHand;
		FProjectEXHandAim LeftHand;
		float FingerCurl = 64.0f;
		float IndexCurl = 36.0f;
		float ThumbPitch = -12.0f;
		float ThumbYaw = -25.0f;
	};

	FProjectEXHold HoldForWeapon(EProjectEXGripStyle Style)
	{
		FProjectEXHold Hold;
		if (Style == EProjectEXGripStyle::Pistol)
		{
			// Isosceles: both arms out, hands stacked, support hand wrapped on the left.
			Hold.RightHandView = FVector(50.0f, 0.0f, -12.0f);
			Hold.RightElbowView = FVector(22.0f, 18.0f, -26.0f);
			Hold.LeftElbowView = FVector(22.0f, -16.0f, -26.0f);
			Hold.RightHand.Finger = FVector(0.2f, -1.0f, -0.45f);
			Hold.RightHand.BackOfHand = FVector(0.0f, 1.0f, 0.08f);
			Hold.LeftHand.Finger = FVector(0.15f, 1.0f, -0.2f);
			Hold.LeftHand.BackOfHand = FVector(0.1f, -1.0f, 0.15f);
			Hold.FingerCurl = 72.0f;
			Hold.IndexCurl = 22.0f;
			Hold.ThumbPitch = -18.0f;
			Hold.ThumbYaw = -55.0f;
		}
		else
		{
			// Rifle: firing hand on the grip, support hand forward on the handguard, elbow down.
			Hold.RightHand.Finger = FVector(0.35f, 0.05f, -1.0f);
			Hold.RightHand.BackOfHand = FVector(0.05f, 1.0f, 0.1f);
			Hold.LeftHand.Finger = FVector(0.2f, 0.85f, -0.55f);
			Hold.LeftHand.BackOfHand = FVector(-0.25f, -0.15f, 1.0f);
		}
		return Hold;
	}

	FQuat MakeHandRotation(const FProjectEXHandAim& Aim)
	{
		return FRotationMatrix::MakeFromXZ(Aim.Finger.GetSafeNormal(), Aim.BackOfHand.GetSafeNormal()).ToQuat();
	}

	void CurlFinger(UPoseableMeshComponent* Mesh, const FString& BoneName, float Pitch, float Yaw)
	{
		const int32 Index = Mesh->GetBoneIndex(FName(*BoneName));
		if (!Mesh->BoneSpaceTransforms.IsValidIndex(Index))
		{
			return;
		}

		Mesh->BoneSpaceTransforms[Index].ConcatenateRotation(FRotator(Pitch, Yaw, 0.0f).Quaternion());
	}

	void CurlHand(UPoseableMeshComponent* Mesh, const TCHAR* Side, const FProjectEXHold& Hold)
	{
		const bool bTriggerHand = FCString::Strcmp(Side, TEXT("r")) == 0;
		const float IndexCurl = bTriggerHand ? Hold.IndexCurl : Hold.FingerCurl;
		const float ThumbYaw = bTriggerHand ? Hold.ThumbYaw : -Hold.ThumbYaw;
		CurlFinger(Mesh, FString::Printf(TEXT("index_01_%s"), Side), -IndexCurl, 0.0f);
		CurlFinger(Mesh, FString::Printf(TEXT("index_02_%s"), Side), -IndexCurl, 0.0f);
		CurlFinger(Mesh, FString::Printf(TEXT("index_03_%s"), Side), -IndexCurl * 0.5f, 0.0f);

		const TCHAR* Fingers[] = { TEXT("middle"), TEXT("ring"), TEXT("pinky") };
		for (const TCHAR* Finger : Fingers)
		{
			CurlFinger(Mesh, FString::Printf(TEXT("%s_01_%s"), Finger, Side), -Hold.FingerCurl, 0.0f);
			CurlFinger(Mesh, FString::Printf(TEXT("%s_02_%s"), Finger, Side), -Hold.FingerCurl, 0.0f);
			CurlFinger(Mesh, FString::Printf(TEXT("%s_03_%s"), Finger, Side), -Hold.FingerCurl * 0.55f, 0.0f);
		}

		CurlFinger(Mesh, FString::Printf(TEXT("thumb_01_%s"), Side), Hold.ThumbPitch, ThumbYaw);
		CurlFinger(Mesh, FString::Printf(TEXT("thumb_02_%s"), Side), Hold.ThumbPitch * 0.45f, 0.0f);
	}

	bool PoseArm(UPoseableMeshComponent* Mesh, FName Upper, FName Lower, FName Hand, const FVector& Contact, const FVector& ElbowHint, const FQuat& HandRotation)
	{
		if (Mesh->GetBoneIndex(Upper) == INDEX_NONE || Mesh->GetBoneIndex(Lower) == INDEX_NONE || Mesh->GetBoneIndex(Hand) == INDEX_NONE)
		{
			return false;
		}

		FTransform UpperTransform = Mesh->GetBoneTransformByName(Upper, EBoneSpaces::ComponentSpace);
		FTransform LowerTransform = Mesh->GetBoneTransformByName(Lower, EBoneSpaces::ComponentSpace);
		FTransform HandTransform = Mesh->GetBoneTransformByName(Hand, EBoneSpaces::ComponentSpace);
		const FVector Wrist = Contact + (ElbowHint - Contact).GetSafeNormal() * 7.0f;
		AnimationCore::SolveTwoBoneIK(UpperTransform, LowerTransform, HandTransform, ElbowHint, Wrist, false, 1.0, 1.0);

		// The wrist has to stay welded to its own forearm. Two things were wrong here: an absolute
		// component-space rotation let the hand swing up to 180 degrees off the lower arm and sheared
		// the palm into flat shards, and the two-bone solve preserves the rest pose's bone roll, so a
		// T-posed arm swung forward keeps its palms-down roll and presents the BACK of the hand to the
		// camera. Split the authored aim into the two axes and treat them differently: twist runs along
		// the hand's own length axis (pronation/supination, which is safe and is what turns the palm
		// onto the grip) and is applied in full, while the off-axis swing is what tears the wrist and
		// so stays clamped.
		const FQuat ForearmRotation = LowerTransform.GetRotation();
		const FQuat DesiredLocal = ForearmRotation.Inverse() * HandRotation;
		FQuat Swing(0.0f, 0.0f, 0.0f, 1.0f);
		FQuat Twist(0.0f, 0.0f, 0.0f, 1.0f);
		DesiredLocal.ToSwingTwist(FVector::XAxisVector, Swing, Twist);
		FVector SwingAxis = FVector::XAxisVector;
		float SwingAngle = 0.0f;
		Swing.ToAxisAndAngle(SwingAxis, SwingAngle);
		const FQuat ClampedSwing(SwingAxis, FMath::Min(SwingAngle, FMath::DegreesToRadians(25.0f)));
		HandTransform.SetRotation(ForearmRotation * ClampedSwing * Twist);
		Mesh->SetBoneTransformByName(Upper, UpperTransform, EBoneSpaces::ComponentSpace);
		Mesh->SetBoneTransformByName(Lower, LowerTransform, EBoneSpaces::ComponentSpace);
		Mesh->SetBoneTransformByName(Hand, HandTransform, EBoneSpaces::ComponentSpace);
		return true;
	}
}

void ProjectEXAlignWeaponToHand(USkeletalMeshComponent* WeaponMesh, const USkeletalMeshComponent* Holder, FName SocketName, float GripOffset)
{
	if (!WeaponMesh || !Holder || !Holder->DoesSocketExist(SocketName))
	{
		return;
	}

	// The weapon is attached to the socket, so this is the socket's own space.
	// The mannequin hand points along X. The prototype guns point along Y, with Z up.
	const FQuat RelativeRotation = FRotationMatrix::MakeFromYZ(FVector::XAxisVector, FVector::ZAxisVector).ToQuat();
	WeaponMesh->SetRelativeRotation(RelativeRotation.Rotator());
	WeaponMesh->SetRelativeLocation(RelativeRotation.RotateVector(FVector(0.0f, GripOffset, 0.0f)));
}

UProjectEXWeaponViewComponent::UProjectEXWeaponViewComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostUpdateWork;
	SetIsReplicatedByDefault(false);
}

void UProjectEXWeaponViewComponent::BeginPlay()
{
	Super::BeginPlay();

	WeaponComponent = GetOwner() ? GetOwner()->FindComponentByClass<UProjectEXWeaponComponent>() : nullptr;

	if (const ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		if (const UCharacterMovementComponent* Movement = Character->GetCharacterMovement())
		{
			WalkSpeedReference = FMath::Max(Movement->MaxWalkSpeed, 150.0f);
		}
	}

	if (const AProjectEXCharacter* Character = Cast<AProjectEXCharacter>(GetOwner()))
	{
		if (const UCameraComponent* Camera = Character->GetFirstPersonCameraComponent())
		{
			RestingFieldOfView = Camera->FieldOfView;
			bCapturedFieldOfView = true;
		}
	}
}

void UProjectEXWeaponViewComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	RestoreCamera();
	if (Mesh)
	{
		Mesh->DestroyComponent();
		Mesh = nullptr;
	}
	if (ArmsMesh)
	{
		ArmsMesh->DestroyComponent();
		ArmsMesh = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

void UProjectEXWeaponViewComponent::SetWeapon(UProjectEXWeaponData* NewWeapon)
{
	const bool bSameWeapon = Weapon == NewWeapon && Mesh && Mesh->GetSkeletalMeshAsset();
	Weapon = NewWeapon;
	if (!bSameWeapon)
	{
		UpdateFirstPersonMesh();
	}

	if (!Weapon)
	{
		AimAlpha = 0.0f;
		KickOffset = FVector::ZeroVector;
		KickRotation = FRotator::ZeroRotator;
		ReloadPose = 0.0f;
		RestoreCamera();
	}
}

void UProjectEXWeaponViewComponent::NotifyFired()
{
	if (!Weapon)
	{
		return;
	}

	KickOffset.X = FMath::Max(KickOffset.X - Weapon->VisualKickDistance, -Weapon->VisualKickDistance * 2.5f);
	KickOffset.Z += Weapon->VisualKickDistance * 0.25f;
	KickRotation.Pitch = FMath::Min(KickRotation.Pitch + Weapon->VisualKickPitch, Weapon->VisualKickPitch * 3.0f);
	KickRotation.Yaw += FMath::FRandRange(-Weapon->VisualKickPitch * 0.15f, Weapon->VisualKickPitch * 0.15f);
}

bool UProjectEXWeaponViewComponent::GetMuzzleLocation(FVector& OutLocation) const
{
	if (!Mesh || !Weapon)
	{
		return false;
	}

	OutLocation = Mesh->GetComponentTransform().TransformPosition(Weapon->MuzzleOffset);
	return true;
}

void UProjectEXWeaponViewComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!WeaponComponent)
	{
		WeaponComponent = GetOwner() ? GetOwner()->FindComponentByClass<UProjectEXWeaponComponent>() : nullptr;
	}
	if (!Pawn || !Pawn->IsLocallyControlled() || !Weapon)
	{
		return;
	}

	if (!bHandsPosed && !UsesPresentationRig())
	{
		PlaceHeldWeapon();
	}

	const bool bWantAim = WeaponComponent && WeaponComponent->IsAiming();
	const float AimRate = 1.0f / FMath::Max(Weapon->AdsTransitionDuration, 0.01f);
	AimAlpha = FMath::FInterpConstantTo(AimAlpha, bWantAim ? 1.0f : 0.0f, DeltaTime, AimRate);

	const FRotator Look = Pawn->GetControlRotation();
	FRotator LookDelta = FRotator::ZeroRotator;
	if (bHasLastLook)
	{
		LookDelta = (Look - LastLook).GetNormalized();
		LookDelta.Yaw -= WeaponComponent ? WeaponComponent->ConsumeRecoilYaw() : 0.0f;
		LookDelta.Pitch -= WeaponComponent ? WeaponComponent->ConsumeRecoilPitch() : 0.0f;
		LookDelta.Yaw = FMath::Clamp(LookDelta.Yaw, -8.0f, 8.0f);
		LookDelta.Pitch = FMath::Clamp(LookDelta.Pitch, -8.0f, 8.0f);
	}
	else if (WeaponComponent)
	{
		WeaponComponent->ConsumeRecoilYaw();
		WeaponComponent->ConsumeRecoilPitch();
	}
	LastLook = Look;
	bHasLastLook = true;
	AlignArmsToCamera();

	const float SwayGain = Weapon->SwayDegrees / 6.0f;
	SwayTarget.Yaw = FMath::Clamp(SwayTarget.Yaw - LookDelta.Yaw * SwayGain, -Weapon->SwayDegrees, Weapon->SwayDegrees);
	SwayTarget.Pitch = FMath::Clamp(SwayTarget.Pitch - LookDelta.Pitch * SwayGain, -Weapon->SwayDegrees, Weapon->SwayDegrees);
	SwayTarget.Roll = FMath::Clamp(SwayTarget.Yaw * 0.45f, -Weapon->SwayDegrees, Weapon->SwayDegrees);
	SwayTarget = FMath::RInterpTo(SwayTarget, FRotator::ZeroRotator, DeltaTime, Weapon->SwaySpeed * 0.65f);
	Sway = FMath::RInterpTo(Sway, SwayTarget, DeltaTime, Weapon->SwaySpeed);

	const float Speed = Pawn->GetVelocity().Size2D();
	const float SpeedAlpha = FMath::Clamp(Speed / WalkSpeedReference, 0.0f, 2.0f);
	const float SprintAlpha = FMath::Clamp((Speed - WalkSpeedReference * 1.05f) / WalkSpeedReference, 0.0f, 1.0f);
	if (Speed > 20.0f)
	{
		BobPhase += DeltaTime * Weapon->BobSpeed * FMath::Max(SpeedAlpha, 0.35f) * 2.0f * PI;
	}

	const float BobAmplitude = FMath::Lerp(1.0f, Weapon->SprintBobMultiplier, SprintAlpha);
	FVector BobTarget = FVector::ZeroVector;
	if (Speed > 20.0f)
	{
		BobTarget.Y = FMath::Sin(BobPhase) * Weapon->BobHorizontal * BobAmplitude;
		BobTarget.Z = FMath::Sin(BobPhase * 2.0f) * Weapon->BobVertical * BobAmplitude;
	}
	BobOffset = FMath::VInterpTo(BobOffset, BobTarget, DeltaTime, 10.0f);

	const float SwayScale = FMath::Lerp(1.0f, Weapon->AimSwayScale, AimAlpha);
	const float BobScale = FMath::Lerp(1.0f, Weapon->AimBobScale, AimAlpha);
	const bool bReload = WeaponComponent && WeaponComponent->IsReloading();
	if (bReload)
	{
		if (!bReloadWasActive)
		{
			ReloadElapsed = 0.0f;
		}
		ReloadElapsed += DeltaTime;
		const float Duration = FMath::Max(Weapon->ReloadDuration, 0.05f);
		ReloadPose = FMath::Sin(FMath::Clamp(ReloadElapsed / Duration, 0.0f, 1.0f) * PI);
	}
	else
	{
		ReloadElapsed = 0.0f;
		ReloadPose = FMath::FInterpTo(ReloadPose, 0.0f, DeltaTime, 8.0f);
	}
	bReloadWasActive = bReload;

	KickOffset = FMath::VInterpTo(KickOffset, FVector::ZeroVector, DeltaTime, Weapon->VisualKickRecovery);
	KickRotation = FMath::RInterpTo(KickRotation, FRotator::ZeroRotator, DeltaTime, Weapon->VisualKickRecovery);

	FVector Location = FVector::ZeroVector;
	FRotator Rotation = FRotator::ZeroRotator;
	if (bHeldInHands || UsesPresentationRig())
	{
		Location = (BobOffset * BobScale) + KickOffset;
		Location.Z -= ReloadPose * Weapon->ReloadDropDistance;
		Rotation = (Sway * SwayScale) + KickRotation;
		Rotation.Pitch -= ReloadPose * Weapon->ReloadDropPitch;
	}
	else
	{
		Location = FMath::Lerp(Weapon->ViewOffset, Weapon->AdsOffset, AimAlpha);
		const FRotator RotationBase = Weapon->ViewRotation;
		const FRotator RotationAim = Weapon->AdsRotation;
		Rotation = FRotator(
			FMath::Lerp(RotationBase.Pitch, RotationAim.Pitch, AimAlpha),
			FMath::Lerp(RotationBase.Yaw, RotationAim.Yaw, AimAlpha),
			FMath::Lerp(RotationBase.Roll, RotationAim.Roll, AimAlpha));
		Location += BobOffset * BobScale;
		Location += KickOffset;
		Location.Z -= ReloadPose * Weapon->ReloadDropDistance;
		Rotation += Sway * SwayScale;
		Rotation += KickRotation;
		Rotation.Pitch -= ReloadPose * Weapon->ReloadDropPitch;
	}
	SetRelativeLocationAndRotation(Location, Rotation);

	if (AProjectEXCharacter* Character = Cast<AProjectEXCharacter>(Pawn))
	{
		if (UCameraComponent* Camera = Character->GetFirstPersonCameraComponent())
		{
			if (!bCapturedFieldOfView)
			{
				RestingFieldOfView = Camera->FieldOfView;
				RestingFirstPersonFieldOfView = Camera->FirstPersonFieldOfView;
				bCapturedFieldOfView = true;
			}
			Camera->SetFieldOfView(FMath::Lerp(RestingFieldOfView, Weapon->AdsFOV, AimAlpha));
			// The first-person projection stays at its resting value. Driving it toward AdsFOV
			// would shrink the gun and hands on screen exactly when they should be filling it.
			Camera->FirstPersonFieldOfView = RestingFirstPersonFieldOfView;

			if (UsesPresentationRig())
			{
				ApplyRigPose();
			}
			else if (bHeldInHands && Mesh && AimAlpha > 0.0f)
			{
				UpdateComponentToWorld();
				Mesh->UpdateComponentToWorld();
				const FVector SightWorld = Mesh->GetComponentTransform().TransformPosition(Weapon->SightOffset);
				const FVector SightCamera = Camera->GetComponentTransform().InverseTransformPosition(SightWorld);
				const float SightBlend = AimAlpha * (1.0f - ReloadPose);
				Location.Y -= SightCamera.Y * SightBlend;
				Location.Z -= SightCamera.Z * SightBlend;
				SetRelativeLocation(Location);
			}
		}
	}
}

void UProjectEXWeaponViewComponent::AlignArmsToCamera()
{
	if (bArmsAligned || !ArmsMesh || !ArmsMesh->DoesSocketExist(TEXT("head")))
	{
		return;
	}

	ArmsMesh->RefreshBoneTransforms();
	const FVector HeadLocal = ArmsMesh->GetSocketTransform(TEXT("head"), RTS_Component).GetLocation();
	if (HeadLocal.SizeSquared() < 100.0f)
	{
		return;
	}

	ArmsMesh->SetRelativeLocation(-HeadLocal);
	bArmsAligned = true;
}

void UProjectEXWeaponViewComponent::EnsureArms()
{
	if (ArmsMesh && ArmsMesh->GetSkinnedAsset())
	{
		return;
	}

	USkeletalMesh* Arms = LoadObject<USkeletalMesh>(nullptr, ViewmodelArmsPath);
	AProjectEXCharacter* Character = Cast<AProjectEXCharacter>(GetOwner());
	if (!Arms || !Character)
	{
		return;
	}

	if (!ArmsMesh)
	{
		ArmsMesh = NewObject<UPoseableMeshComponent>(Character);
		ArmsMesh->SetupAttachment(this);
		ArmsMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ArmsMesh->SetOnlyOwnerSee(true);
		ArmsMesh->SetCastShadow(false);
		ArmsMesh->SetFirstPersonPrimitiveType(EFirstPersonPrimitiveType::FirstPerson);
		ArmsMesh->SetSkinnedAssetAndUpdate(Arms);
		ArmsMesh->RegisterComponent();
	}
	else if (ArmsMesh->GetSkinnedAsset() != Arms)
	{
		ArmsMesh->SetSkinnedAssetAndUpdate(Arms);
	}

	if (ArmsMesh->GetBoneSpaceTransforms().Num() == 0)
	{
		ArmsMesh->AllocateTransformData();
	}

	ArmsMesh->SetVisibility(true);
	ArmsMesh->SetRelativeRotation(FRotator::ZeroRotator);
	ArmsMesh->SetRelativeScale3D(FVector::OneVector);
	bArmsAligned = false;
	bHandsPosed = false;
	AlignArmsToCamera();
}

void UProjectEXWeaponViewComponent::UpdateFirstPersonMesh()
{
	bHeldInHands = false;
	bHandsPosed = false;
	if (Mesh)
	{
		Mesh->DestroyComponent();
		Mesh = nullptr;
	}

	AProjectEXCharacter* Character = Cast<AProjectEXCharacter>(GetOwner());
	USkeletalMesh* ViewMesh = Weapon ? Weapon->ViewMesh.LoadSynchronous() : nullptr;
	if (!Character || !Weapon || !ViewMesh)
	{
		return;
	}

	// Every pose grips the weapon with the Synty FPS arms, so they are created whether the
	// gun placement comes from a presentation rig or from the held-weapon IK below.
	const bool bRig = UsesPresentationRig();
	EnsureArms();

	Mesh = NewObject<USkeletalMeshComponent>(Character);
	Mesh->SetSkeletalMeshAsset(ViewMesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetOnlyOwnerSee(true);
	Mesh->SetCastShadow(false);
	Mesh->SetFirstPersonPrimitiveType(EFirstPersonPrimitiveType::FirstPerson);
	Mesh->SetupAttachment(bRig || !ArmsMesh ? static_cast<USceneComponent*>(this) : static_cast<USceneComponent*>(ArmsMesh));
	Mesh->SetRelativeScale3D(bRig || ArmsMesh ? FVector::OneVector : FVector(Weapon->ViewScale));
	if (!ArmsMesh)
	{
		Mesh->SetRelativeRotation(Weapon->ViewRotation);
		Mesh->SetRelativeLocation(Weapon->ViewOffset);
	}
	Mesh->RegisterComponent();
	if (bRig)
	{
		ApplyRigPose();
	}
	else
	{
		PlaceHeldWeapon();
	}
}

bool UProjectEXWeaponViewComponent::UsesPresentationRig() const
{
	return Weapon && Weapon->PresentationRig != nullptr;
}

void UProjectEXWeaponViewComponent::ApplyRigPose()
{
	const AProjectEXWeaponRig* Rig = Weapon && Weapon->PresentationRig
		? Weapon->PresentationRig->GetDefaultObject<AProjectEXWeaponRig>()
		: nullptr;
	if (!Rig || !Rig->GetHipFireAnchor() || !Rig->GetADSAnchor() || !Rig->GetPreviewMesh() || !Mesh)
	{
		return;
	}

	const FTransform MeshOnAnchor = Rig->GetPreviewMesh()->GetRelativeTransform();
	const FTransform Hip = Rig->GetHipFireAnchor()->GetRelativeTransform() * MeshOnAnchor;
	const FTransform Aim = Rig->GetADSAnchor()->GetRelativeTransform() * MeshOnAnchor;
	Mesh->SetRelativeLocation(FMath::Lerp(Hip.GetLocation(), Aim.GetLocation(), AimAlpha));
	Mesh->SetRelativeRotation(FQuat::Slerp(Hip.GetRotation(), Aim.GetRotation(), AimAlpha).Rotator());
	Mesh->SetRelativeScale3D(FMath::Lerp(Hip.GetScale3D(), Aim.GetScale3D(), AimAlpha));

	// The rig just moved the gun. The hands have to be re-solved onto it every frame, or they
	// would only ever grip the pose the gun happened to have on the first update.
	PoseRigHands();
}

void UProjectEXWeaponViewComponent::PoseRigHands()
{
	const USkinnedAsset* ArmsAsset = ArmsMesh ? ArmsMesh->GetSkinnedAsset() : nullptr;
	if (!ArmsAsset || !Mesh || !Weapon || ArmsMesh->GetBoneSpaceTransforms().Num() == 0)
	{
		return;
	}

	if (!ArmsMesh->DoesSocketExist(TEXT("head"))
		|| ArmsMesh->GetBoneIndex(TEXT("hand_r")) == INDEX_NONE
		|| ArmsMesh->GetBoneIndex(TEXT("hand_l")) == INDEX_NONE)
	{
		return;
	}

	ArmsMesh->RefreshBoneTransforms();
	const FVector HeadLocal = ArmsMesh->GetSocketTransform(TEXT("head"), RTS_Component).GetLocation();
	if (HeadLocal.SizeSquared() < 100.0f)
	{
		return;
	}

	const FProjectEXHold Hold = HoldForWeapon(Weapon->GripStyle);

	// ApplyRigPose already placed the gun inside this component. The arms mesh is shifted so its
	// head bone sits on the camera, so adding that same shift brings the gun into arm space.
	const FTransform GunTransform(Mesh->GetRelativeRotation().Quaternion(), Mesh->GetRelativeLocation() + HeadLocal, Mesh->GetRelativeScale3D());

	// Solve from the reference pose every frame so repeated IK does not accumulate error.
	ArmsMesh->BoneSpaceTransforms = ArmsAsset->GetRefSkeleton().GetRefBonePose();
	// Without this the solver reads last frame's component-space pose and feeds on its own output.
	ArmsMesh->RefreshBoneTransforms();

	const bool bRight = PoseArm(ArmsMesh, TEXT("upperarm_r"), TEXT("lowerarm_r"), TEXT("hand_r"),
		GunTransform.TransformPosition(Weapon->RightHandOffset), Hold.RightElbowView + HeadLocal, MakeHandRotation(Hold.RightHand));
	const bool bLeft = PoseArm(ArmsMesh, TEXT("upperarm_l"), TEXT("lowerarm_l"), TEXT("hand_l"),
		GunTransform.TransformPosition(Weapon->LeftHandOffset), Hold.LeftElbowView + HeadLocal, MakeHandRotation(Hold.LeftHand));

	if (bRight)
	{
		CurlHand(ArmsMesh, TEXT("r"), Hold);
	}
	if (bLeft)
	{
		CurlHand(ArmsMesh, TEXT("l"), Hold);
	}

	ArmsMesh->RefreshBoneTransforms();
}

void UProjectEXWeaponViewComponent::PlaceHeldWeapon()
{
	if (bHandsPosed || !ArmsMesh || !Mesh || !Weapon || ArmsMesh->GetBoneSpaceTransforms().Num() == 0)
	{
		return;
	}

	if (!ArmsMesh->DoesSocketExist(TEXT("head")) || ArmsMesh->GetBoneIndex(TEXT("hand_r")) == INDEX_NONE || ArmsMesh->GetBoneIndex(TEXT("hand_l")) == INDEX_NONE)
	{
		return;
	}

	const FVector HeadLocal = ArmsMesh->GetSocketTransform(TEXT("head"), RTS_Component).GetLocation();
	if (HeadLocal.SizeSquared() < 100.0f)
	{
		return;
	}

	const FProjectEXHold Hold = HoldForWeapon(Weapon->GripStyle);
	const FQuat GunRotation = FRotationMatrix::MakeFromYZ(FVector::XAxisVector, FVector::ZAxisVector).ToQuat();
	const FVector GunView = Hold.RightHandView - GunRotation.RotateVector(Weapon->RightHandOffset);
	const FVector GunArms = GunView + HeadLocal;

	Mesh->AttachToComponent(ArmsMesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	Mesh->SetRelativeScale3D(FVector::OneVector);
	Mesh->SetRelativeRotation(GunRotation.Rotator());
	Mesh->SetRelativeLocation(GunArms);

	const FTransform GunTransform(GunRotation, GunArms);
	const USkinnedAsset* ArmsAsset = ArmsMesh->GetSkinnedAsset();
	if (!ArmsAsset)
	{
		return;
	}

	ArmsMesh->BoneSpaceTransforms = ArmsAsset->GetRefSkeleton().GetRefBonePose();
	// Without this the solver reads last frame's component-space pose and feeds on its own output.
	ArmsMesh->RefreshBoneTransforms();
	const bool bRight = PoseArm(ArmsMesh, TEXT("upperarm_r"), TEXT("lowerarm_r"), TEXT("hand_r"), GunTransform.TransformPosition(Weapon->RightHandOffset), Hold.RightElbowView + HeadLocal, MakeHandRotation(Hold.RightHand));
	const bool bLeft = PoseArm(ArmsMesh, TEXT("upperarm_l"), TEXT("lowerarm_l"), TEXT("hand_l"), GunTransform.TransformPosition(Weapon->LeftHandOffset), Hold.LeftElbowView + HeadLocal, MakeHandRotation(Hold.LeftHand));
	if (bRight)
	{
		CurlHand(ArmsMesh, TEXT("r"), Hold);
	}
	if (bLeft)
	{
		CurlHand(ArmsMesh, TEXT("l"), Hold);
	}

	ArmsMesh->RefreshBoneTransforms();
	bHeldInHands = bRight && bLeft;
	bHandsPosed = bHeldInHands;
}

void UProjectEXWeaponViewComponent::RestoreCamera() const
{
	if (!bCapturedFieldOfView)
	{
		return;
	}

	if (const AProjectEXCharacter* Character = Cast<AProjectEXCharacter>(GetOwner()))
	{
		if (UCameraComponent* Camera = Character->GetFirstPersonCameraComponent())
		{
			Camera->SetFieldOfView(RestingFieldOfView);
			Camera->FirstPersonFieldOfView = RestingFirstPersonFieldOfView;
		}
	}
}
