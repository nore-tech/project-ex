// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXWeaponComponent.h"
#include "ProjectEX.h"
#include "ProjectEXCharacter.h"
#include "ProjectEXCombatWidgets.h"
#include "ProjectEXHealthComponent.h"
#include "ProjectEXInventoryComponent.h"
#include "ProjectEXItemDefinition.h"
#include "ProjectEXLootComponent.h"
#include "ProjectEXWeaponData.h"
#include "ProjectEXWeaponItemDefinition.h"
#include "ProjectEXWeaponViewComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Net/UnrealNetwork.h"
#include "Sound/SoundBase.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

namespace
{
	bool IsHeadshotComponent(const FHitResult& Hit)
	{
		if (const UPrimitiveComponent* Component = Hit.GetComponent())
		{
			if (Component->ComponentHasTag(TEXT("Head")))
			{
				return true;
			}
		}

		const FString Bone = Hit.BoneName.ToString();
		return Bone.Contains(TEXT("head"), ESearchCase::IgnoreCase);
	}
}

AProjectEXTracer::AProjectEXTracer()
{
	Beam = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Beam"));
	SetRootComponent(Beam);
	Beam->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Beam->SetCastShadow(false);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cylinder(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (Cylinder.Succeeded())
	{
		Beam->SetStaticMesh(Cylinder.Object);
	}
	InitialLifeSpan = 0.07f;
	SetReplicates(false);
}

void AProjectEXTracer::SetSegment(const FVector& Start, const FVector& End)
{
	const FVector Direction = End - Start;
	const float Length = Direction.Size();
	if (!Beam || Length < 30.0f)
	{
		Destroy();
		return;
	}

	SetActorLocation(Start + Direction * 0.5f);
	SetActorRotation(FRotationMatrix::MakeFromZ(Direction).Rotator());
	Beam->SetRelativeScale3D(FVector(0.012f, 0.012f, Length / 100.0f));

	if (UMaterialInterface* BaseMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial")))
	{
		if (UMaterialInstanceDynamic* Material = UMaterialInstanceDynamic::Create(BaseMaterial, this))
		{
			Material->SetVectorParameterValue(TEXT("Color"), FLinearColor(1.0f, 0.78f, 0.42f));
			Beam->SetMaterial(0, Material);
		}
	}
}

AProjectEXShotFlash::AProjectEXShotFlash()
{
	UPointLightComponent* Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	SetRootComponent(Light);
	Light->SetIntensity(12000.0f);
	Light->SetAttenuationRadius(280.0f);
	Light->SetLightColor(FLinearColor(1.0f, 0.85f, 0.55f));
	Light->SetCastShadows(false);
	InitialLifeSpan = 0.05f;
}

UProjectEXWeaponComponent::UProjectEXWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UProjectEXWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UProjectEXWeaponComponent, EquippedWeapon);
	DOREPLIFETIME(UProjectEXWeaponComponent, ActiveWeaponSlot);
	DOREPLIFETIME_CONDITION(UProjectEXWeaponComponent, bReloading, COND_OwnerOnly);
}

void UProjectEXWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UProjectEXInventoryComponent* Inventory = GetOwner() ? GetOwner()->FindComponentByClass<UProjectEXInventoryComponent>() : nullptr)
	{
		Inventory->OnInventoryChanged.AddDynamic(this, &UProjectEXWeaponComponent::HandleInventoryChanged);
	}

	if (GetOwner() && GetOwner()->HasAuthority())
	{
		SyncEquippedWeapon();
	}

	ClearMeshes();
	RefreshMeshes();
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(MeshTimer, this, &UProjectEXWeaponComponent::RefreshMeshes, 0.25f, true);
	}

	if (const APawn* Pawn = Cast<APawn>(GetOwner()); Pawn && Pawn->IsLocallyControlled())
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController()))
		{
			HudWidget = CreateWidget<UProjectEXCombatHudWidget>(PlayerController, UProjectEXCombatHudWidget::StaticClass());
			if (HudWidget)
			{
				HudWidget->BindWeapon(this);
				HudWidget->AddToViewport(8);
			}
		}
	}
}

void UProjectEXWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(ReloadTimer);
		World->GetTimerManager().ClearTimer(MeshTimer);
	}

	if (HudWidget)
	{
		HudWidget->RemoveFromParent();
		HudWidget = nullptr;
	}

	ClearMeshes();
	if (View)
	{
		View->DestroyComponent();
		View = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}

void UProjectEXWeaponComponent::BindInput(UEnhancedInputComponent* EnhancedInput)
{
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!EnhancedInput || !Pawn || !Pawn->IsLocallyControlled())
	{
		return;
	}

	if (!WeaponMappingContext)
	{
		WeaponMappingContext = NewObject<UInputMappingContext>(this, TEXT("IMC_Weapon"));
	}

	if (!FireAction)
	{
		FireAction = NewObject<UInputAction>(this, TEXT("IA_Fire"));
		FireAction->ValueType = EInputActionValueType::Boolean;
		WeaponMappingContext->MapKey(FireAction, EKeys::LeftMouseButton);
	}

	if (!AimAction)
	{
		AimAction = NewObject<UInputAction>(this, TEXT("IA_Aim"));
		AimAction->ValueType = EInputActionValueType::Boolean;
		WeaponMappingContext->MapKey(AimAction, EKeys::RightMouseButton);
	}

	if (!ReloadAction)
	{
		ReloadAction = NewObject<UInputAction>(this, TEXT("IA_Reload"));
		ReloadAction->ValueType = EInputActionValueType::Boolean;
		WeaponMappingContext->MapKey(ReloadAction, EKeys::R);
	}

	if (!CycleAction)
	{
		CycleAction = NewObject<UInputAction>(this, TEXT("IA_CycleWeapon"));
		CycleAction->ValueType = EInputActionValueType::Boolean;
		WeaponMappingContext->MapKey(CycleAction, EKeys::One);
	}

	if (!bMappingRegistered)
	{
		if (const APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController()))
		{
			if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
			{
				if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
				{
					Subsystem->AddMappingContext(WeaponMappingContext, 1);
					bMappingRegistered = true;
				}
			}
		}
	}

	EnhancedInput->BindAction(FireAction, ETriggerEvent::Started, this, &UProjectEXWeaponComponent::FirePressed);
	EnhancedInput->BindAction(FireAction, ETriggerEvent::Triggered, this, &UProjectEXWeaponComponent::FireHeld);
	EnhancedInput->BindAction(AimAction, ETriggerEvent::Started, this, &UProjectEXWeaponComponent::AimPressed);
	EnhancedInput->BindAction(AimAction, ETriggerEvent::Completed, this, &UProjectEXWeaponComponent::AimReleased);
	EnhancedInput->BindAction(ReloadAction, ETriggerEvent::Started, this, &UProjectEXWeaponComponent::TryReload);
	EnhancedInput->BindAction(CycleAction, ETriggerEvent::Started, this, &UProjectEXWeaponComponent::TryCycle);
}

int32 UProjectEXWeaponComponent::GetMagazine() const
{
	const UProjectEXInventoryComponent* Inventory = GetOwner() ? GetOwner()->FindComponentByClass<UProjectEXInventoryComponent>() : nullptr;
	FProjectEXEquippedItem Item;
	if (!Inventory || !Inventory->GetEquippedItem(ActiveWeaponSlot, Item) || !Item.IsOccupied())
	{
		return 0;
	}

	if (Item.MagazineRounds >= 0)
	{
		return Item.MagazineRounds;
	}

	return EquippedWeapon ? EquippedWeapon->MagazineSize : 0;
}

int32 UProjectEXWeaponComponent::GetReserveAmmo() const
{
	const UProjectEXInventoryComponent* Inventory = GetOwner() ? GetOwner()->FindComponentByClass<UProjectEXInventoryComponent>() : nullptr;
	if (!Inventory || !EquippedWeapon || !EquippedWeapon->AmmoType)
	{
		return 0;
	}

	return Inventory->CountItem(EquippedWeapon->AmmoType);
}

bool UProjectEXWeaponComponent::IsAiming() const
{
	return bAimHeld && EquippedWeapon != nullptr && CanUseWeapon();
}

float UProjectEXWeaponComponent::ConsumeRecoilPitch()
{
	const float Value = PendingRecoilPitch;
	PendingRecoilPitch = 0.0f;
	return Value;
}

float UProjectEXWeaponComponent::ConsumeRecoilYaw()
{
	const float Value = PendingRecoilYaw;
	PendingRecoilYaw = 0.0f;
	return Value;
}

void UProjectEXWeaponComponent::FirePressed()
{
	if (IsSemiAutomatic())
	{
		TryFire();
	}
}

void UProjectEXWeaponComponent::FireHeld()
{
	if (!IsSemiAutomatic())
	{
		TryFire();
	}
}

void UProjectEXWeaponComponent::TryFire()
{
	if (!CanUseWeapon() || !EquippedWeapon || IsReloading() || GetMagazine() <= 0)
	{
		return;
	}

	const UWorld* World = GetWorld();
	if (!World || World->GetTimeSeconds() < LocalNextFireTime)
	{
		return;
	}

	LocalNextFireTime = World->GetTimeSeconds() + EquippedWeapon->FireInterval;
	ApplyLocalRecoil();
	PlayPredictedFireFX();
	if (View)
	{
		View->NotifyFired();
	}

	if (GetOwner() && GetOwner()->HasAuthority())
	{
		ServerFire_Implementation();
	}
	else
	{
		ServerFire();
	}
}

void UProjectEXWeaponComponent::AimPressed()
{
	bAimHeld = true;
}

void UProjectEXWeaponComponent::AimReleased()
{
	bAimHeld = false;
}

void UProjectEXWeaponComponent::TryReload()
{
	if (!CanUseWeapon() || !EquippedWeapon || IsReloading())
	{
		return;
	}

	if (GetMagazine() >= EquippedWeapon->MagazineSize || GetReserveAmmo() <= 0)
	{
		return;
	}

	bPredictReloading = true;
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		ServerReload_Implementation();
	}
	else
	{
		ServerReload();
	}
}

void UProjectEXWeaponComponent::TryCycle()
{
	if (!CanUseWeapon())
	{
		return;
	}

	if (GetOwner() && GetOwner()->HasAuthority())
	{
		ServerCycleWeapon_Implementation();
	}
	else
	{
		ServerCycleWeapon();
	}
}

bool UProjectEXWeaponComponent::CanUseWeapon() const
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn || !Pawn->IsLocallyControlled())
	{
		return true;
	}

	if (const UProjectEXHealthComponent* Health = Pawn->FindComponentByClass<UProjectEXHealthComponent>())
	{
		if (Health->IsDead())
		{
			return false;
		}
	}

	if (const UProjectEXInventoryComponent* Inventory = Pawn->FindComponentByClass<UProjectEXInventoryComponent>())
	{
		if (Inventory->IsInventoryOpen())
		{
			return false;
		}
	}

	if (const UProjectEXLootComponent* Loot = Pawn->FindComponentByClass<UProjectEXLootComponent>())
	{
		if (Loot->IsLootOpen())
		{
			return false;
		}
	}

	return true;
}

bool UProjectEXWeaponComponent::IsSemiAutomatic() const
{
	return !EquippedWeapon || EquippedWeapon->FireMode == EProjectEXFireMode::Semi;
}

void UProjectEXWeaponComponent::ApplyLocalRecoil()
{
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn || !Pawn->IsLocallyControlled() || !EquippedWeapon)
	{
		return;
	}

	const float Yaw = FMath::FRandRange(-EquippedWeapon->RecoilYaw, EquippedWeapon->RecoilYaw);
	PendingRecoilPitch = -EquippedWeapon->RecoilPitch;
	PendingRecoilYaw = Yaw;
	Pawn->AddControllerPitchInput(PendingRecoilPitch);
	Pawn->AddControllerYawInput(Yaw);
}

void UProjectEXWeaponComponent::ServerFire_Implementation()
{
	APawn* Pawn = Cast<APawn>(GetOwner());
	UWorld* World = GetWorld();
	UProjectEXInventoryComponent* Inventory = Pawn ? Pawn->FindComponentByClass<UProjectEXInventoryComponent>() : nullptr;
	if (!Pawn || !World || !Pawn->HasAuthority() || !Inventory || !EquippedWeapon || bReloading)
	{
		return;
	}

	if (const UProjectEXHealthComponent* Health = Pawn->FindComponentByClass<UProjectEXHealthComponent>())
	{
		if (Health->IsDead())
		{
			return;
		}
	}

	if (World->GetTimeSeconds() < ServerNextFireTime)
	{
		return;
	}

	EnsureEquippedMagazine();
	FProjectEXEquippedItem Item;
	if (!Inventory->GetEquippedItem(ActiveWeaponSlot, Item) || !Item.IsOccupied())
	{
		return;
	}

	const int32 Rounds = Item.MagazineRounds;
	if (Rounds <= 0)
	{
		return;
	}

	ServerNextFireTime = World->GetTimeSeconds() + EquippedWeapon->FireInterval;
	Inventory->SetEquippedMagazine(ActiveWeaponSlot, Rounds - 1);

	const FVector TraceStart = Pawn->GetPawnViewLocation();
	const FVector TraceDirection = Pawn->GetControlRotation().Vector();
	const FVector TraceEnd = TraceStart + (TraceDirection * EquippedWeapon->Range);

	FCollisionQueryParams Params(SCENE_QUERY_STAT(ProjectEXWeaponFire), true, Pawn);
	FHitResult Hit;
	const bool bHit = World->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, Params);
	bool bHeadshot = false;
	if (bHit)
	{
		bHeadshot = IsHeadshotComponent(Hit);
		if (AActor* HitActor = Hit.GetActor())
		{
			if (!HitActor->IsA<AProjectEXCharacter>())
			{
				if (UProjectEXHealthComponent* Health = HitActor->FindComponentByClass<UProjectEXHealthComponent>())
				{
					FProjectEXDamageSpec Spec;
					Spec.Damage = EquippedWeapon->Damage;
					Spec.bHeadshot = bHeadshot;
					Spec.HitBone = Hit.BoneName;
					Spec.DamageType = EquippedWeapon->AmmoType ? EquippedWeapon->AmmoType->GetItemId() : NAME_None;
					Health->ApplyDamage(Spec, Pawn->GetController());
				}
			}
		}
	}

	const FVector ImpactPoint = bHit ? Hit.ImpactPoint : TraceEnd;
	MulticastFireFX(TraceStart, ImpactPoint);
}

void UProjectEXWeaponComponent::ServerReload_Implementation()
{
	APawn* Pawn = Cast<APawn>(GetOwner());
	UWorld* World = GetWorld();
	UProjectEXInventoryComponent* Inventory = Pawn ? Pawn->FindComponentByClass<UProjectEXInventoryComponent>() : nullptr;
	if (!Pawn || !World || !Pawn->HasAuthority() || !Inventory || !EquippedWeapon || bReloading || !EquippedWeapon->AmmoType)
	{
		ClientSetReloading(false);
		return;
	}

	EnsureEquippedMagazine();
	FProjectEXEquippedItem Item;
	if (!Inventory->GetEquippedItem(ActiveWeaponSlot, Item) || !Item.IsOccupied())
	{
		ClientSetReloading(false);
		return;
	}

	const int32 Rounds = Item.MagazineRounds;
	if (Rounds >= EquippedWeapon->MagazineSize || Inventory->CountItem(EquippedWeapon->AmmoType) <= 0)
	{
		ClientSetReloading(false);
		return;
	}

	bReloading = true;
	ClientSetReloading(true);
	World->GetTimerManager().SetTimer(ReloadTimer, this, &UProjectEXWeaponComponent::FinishReload, EquippedWeapon->ReloadDuration, false);
}

void UProjectEXWeaponComponent::ServerCycleWeapon_Implementation()
{
	UProjectEXInventoryComponent* Inventory = GetOwner() ? GetOwner()->FindComponentByClass<UProjectEXInventoryComponent>() : nullptr;
	if (!Inventory || !GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	const EProjectEXEquipmentSlot Other = ActiveWeaponSlot == EProjectEXEquipmentSlot::SecondaryWeapon
		? EProjectEXEquipmentSlot::PrimaryWeapon
		: EProjectEXEquipmentSlot::SecondaryWeapon;
	FProjectEXEquippedItem Item;
	const UProjectEXWeaponItemDefinition* WeaponItem = nullptr;
	if (Inventory->GetEquippedItem(Other, Item) && Item.IsOccupied())
	{
		WeaponItem = Cast<UProjectEXWeaponItemDefinition>(Item.Definition);
	}

	if (WeaponItem && WeaponItem->WeaponData)
	{
		ActiveWeaponSlot = Other;
	}

	SyncEquippedWeapon();
}

void UProjectEXWeaponComponent::MulticastFireFX_Implementation(FVector TraceStart, FVector TraceEnd)
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	const bool bLocalOwner = Pawn && Pawn->IsLocallyControlled();
	const FVector Muzzle = GetMuzzleLocation(TraceStart);
	if (!bLocalOwner)
	{
		PlayShotFlash(Muzzle);
		PlayShotSound(Muzzle);
	}

	if (!GetWorld() || !EquippedWeapon || EquippedWeapon->TracerInterval <= 0)
	{
		return;
	}

	++TracerCounter;
	if (((TracerCounter - 1) % EquippedWeapon->TracerInterval) != 0)
	{
		return;
	}

	const FVector TracerStart = Muzzle;
	if (FVector::DistSquared(TracerStart, TraceEnd) < FMath::Square(40.0f))
	{
		return;
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	if (AProjectEXTracer* Tracer = GetWorld()->SpawnActor<AProjectEXTracer>(TracerStart, FRotator::ZeroRotator, Params))
	{
		Tracer->SetSegment(TracerStart, TraceEnd);
	}
}

void UProjectEXWeaponComponent::ClientSetReloading_Implementation(bool bNewReloading)
{
	bPredictReloading = bNewReloading;
}

void UProjectEXWeaponComponent::OnRep_EquippedWeapon()
{
	RefreshMeshes();
}

void UProjectEXWeaponComponent::OnRep_Reloading()
{
	bPredictReloading = bReloading;
}

void UProjectEXWeaponComponent::EnsureEquippedMagazine()
{
	UProjectEXInventoryComponent* Inventory = GetOwner() ? GetOwner()->FindComponentByClass<UProjectEXInventoryComponent>() : nullptr;
	FProjectEXEquippedItem Item;
	if (!Inventory || !EquippedWeapon || !Inventory->GetEquippedItem(ActiveWeaponSlot, Item) || !Item.IsOccupied())
	{
		return;
	}

	if (Item.MagazineRounds < 0)
	{
		Inventory->SetEquippedMagazine(ActiveWeaponSlot, EquippedWeapon->MagazineSize);
	}
}

void UProjectEXWeaponComponent::SyncEquippedWeapon()
{
	UProjectEXInventoryComponent* Inventory = GetOwner() ? GetOwner()->FindComponentByClass<UProjectEXInventoryComponent>() : nullptr;
	if (!Inventory || !GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	auto WeaponInSlot = [Inventory](EProjectEXEquipmentSlot Slot) -> UProjectEXWeaponData*
	{
		FProjectEXEquippedItem Item;
		if (!Inventory->GetEquippedItem(Slot, Item) || !Item.IsOccupied())
		{
			return nullptr;
		}

		const UProjectEXWeaponItemDefinition* WeaponItem = Cast<UProjectEXWeaponItemDefinition>(Item.Definition);
		return WeaponItem ? WeaponItem->WeaponData : nullptr;
	};

	bool bSlotChanged = false;
	UProjectEXWeaponData* Desired = WeaponInSlot(ActiveWeaponSlot);
	if (!Desired)
	{
		const EProjectEXEquipmentSlot Other = ActiveWeaponSlot == EProjectEXEquipmentSlot::SecondaryWeapon
			? EProjectEXEquipmentSlot::PrimaryWeapon
			: EProjectEXEquipmentSlot::SecondaryWeapon;
		if (UProjectEXWeaponData* OtherWeapon = WeaponInSlot(Other))
		{
			ActiveWeaponSlot = Other;
			Desired = OtherWeapon;
			bSlotChanged = true;
		}
	}

	if (Desired == EquippedWeapon)
	{
		if (bSlotChanged)
		{
			GetOwner()->ForceNetUpdate();
		}
		return;
	}

	if (!Desired)
	{
		ClearEquipped();
		return;
	}

	if (bReloading)
	{
		bReloading = false;
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().ClearTimer(ReloadTimer);
		}
		ClientSetReloading(false);
	}

	EquippedWeapon = Desired;
	EnsureEquippedMagazine();
	RefreshMeshes();
	GetOwner()->ForceNetUpdate();
}

void UProjectEXWeaponComponent::ClearEquipped()
{
	EquippedWeapon = nullptr;
	bReloading = false;
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(ReloadTimer);
	}
	RefreshMeshes();
}

void UProjectEXWeaponComponent::FinishReload()
{
	bReloading = false;
	ClientSetReloading(false);

	UProjectEXInventoryComponent* Inventory = GetOwner() ? GetOwner()->FindComponentByClass<UProjectEXInventoryComponent>() : nullptr;
	FProjectEXEquippedItem Item;
	if (!Inventory || !EquippedWeapon || !EquippedWeapon->AmmoType || !Inventory->GetEquippedItem(ActiveWeaponSlot, Item) || !Item.IsOccupied())
	{
		return;
	}

	EnsureEquippedMagazine();
	if (!Inventory->GetEquippedItem(ActiveWeaponSlot, Item))
	{
		return;
	}

	const int32 Rounds = Item.MagazineRounds;
	const int32 Missing = EquippedWeapon->MagazineSize - Rounds;
	if (Missing <= 0)
	{
		return;
	}

	const int32 Taken = Inventory->ConsumeItem(EquippedWeapon->AmmoType, Missing);
	if (Taken > 0)
	{
		Inventory->SetEquippedMagazine(ActiveWeaponSlot, Rounds + Taken);
	}
}

void UProjectEXWeaponComponent::RefreshMeshes()
{
	if (MeshWeapon != EquippedWeapon)
	{
		ClearMeshes();
		MeshWeapon = EquippedWeapon;
	}

	EnsureView();
	if (View)
	{
		View->SetWeapon(EquippedWeapon);
	}

	if (!EquippedWeapon || EquippedWeapon->ViewMesh.IsNull())
	{
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().ClearTimer(MeshTimer);
		}
		return;
	}

	if (!EquippedWeapon->ViewMesh.LoadSynchronous())
	{
		return;
	}

	const APawn* Pawn = Cast<APawn>(GetOwner());
	const bool bLocal = Pawn && Pawn->IsLocallyControlled();
	if (!WorldMesh)
	{
		WorldMesh = CreateWorldMesh();
	}

	if ((!bLocal || View) && WorldMesh)
	{
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().ClearTimer(MeshTimer);
		}
	}
}

void UProjectEXWeaponComponent::ClearMeshes()
{
	if (WorldMesh)
	{
		WorldMesh->DestroyComponent();
		WorldMesh = nullptr;
	}
}

void UProjectEXWeaponComponent::EnsureView()
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	if (View || !Pawn || !Pawn->IsLocallyControlled())
	{
		return;
	}

	AProjectEXCharacter* Character = Cast<AProjectEXCharacter>(GetOwner());
	UCameraComponent* Camera = Character ? Character->GetFirstPersonCameraComponent() : nullptr;
	if (!Character || !Camera)
	{
		return;
	}

	View = NewObject<UProjectEXWeaponViewComponent>(Character);
	View->SetupAttachment(Camera);
	View->RegisterComponent();
	View->SetWeapon(EquippedWeapon);
}

void UProjectEXWeaponComponent::PlayPredictedFireFX()
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn || !Pawn->IsLocallyControlled())
	{
		return;
	}

	const FVector Location = GetMuzzleLocation(Pawn->GetPawnViewLocation());
	PlayShotFlash(Location);
	PlayShotSound(Location);
}

void UProjectEXWeaponComponent::PlayShotFlash(const FVector& Location) const
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	World->SpawnActor<AProjectEXShotFlash>(Location, FRotator::ZeroRotator, Params);
}

void UProjectEXWeaponComponent::PlayShotSound(const FVector& Location) const
{
	if (!EquippedWeapon)
	{
		return;
	}

	if (USoundBase* Sound = EquippedWeapon->FireSound.LoadSynchronous())
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, Location);
	}
}

USkeletalMeshComponent* UProjectEXWeaponComponent::CreateWorldMesh()
{
	AProjectEXCharacter* Character = Cast<AProjectEXCharacter>(GetOwner());
	USkeletalMesh* RifleMesh = EquippedWeapon ? EquippedWeapon->ViewMesh.LoadSynchronous() : nullptr;
	USkeletalMeshComponent* Body = Character ? Character->GetMesh() : nullptr;
	if (!Character || !EquippedWeapon || !RifleMesh || !Body)
	{
		return nullptr;
	}

	USkeletalMeshComponent* Mesh = NewObject<USkeletalMeshComponent>(Character);
	Mesh->SetSkeletalMeshAsset(RifleMesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	const FName HandSocket = Body->DoesSocketExist(TEXT("hand_r")) ? FName(TEXT("hand_r")) : NAME_None;
	Mesh->SetupAttachment(Body, HandSocket);
	if (HandSocket.IsNone())
	{
		Mesh->SetRelativeLocation(FVector(20.0f, 18.0f, 50.0f));
		Mesh->SetRelativeRotation(EquippedWeapon->ViewRotation);
		Mesh->SetRelativeScale3D(FVector(EquippedWeapon->ViewScale));
	}
	else
	{
		Mesh->SetRelativeScale3D(FVector::OneVector);
		ProjectEXAlignWeaponToHand(Mesh, Body, HandSocket, EquippedWeapon->GripOffset);
	}
	Mesh->SetOnlyOwnerSee(false);
	Mesh->SetOwnerNoSee(true);
	Mesh->SetVisibility(true);
	Mesh->SetHiddenInGame(false);
	Mesh->SetCastShadow(true);
	Mesh->bUseAttachParentBound = false;
	Mesh->SetFirstPersonPrimitiveType(EFirstPersonPrimitiveType::None);
	Mesh->RegisterComponent();
	return Mesh;
}

FVector UProjectEXWeaponComponent::GetMuzzleLocation(const FVector& Fallback) const
{
	FVector Location = Fallback;
	const APawn* Pawn = Cast<APawn>(GetOwner());
	if (Pawn && Pawn->IsLocallyControlled() && View && View->GetMuzzleLocation(Location))
	{
		return Location;
	}

	if (WorldMesh && EquippedWeapon)
	{
		return WorldMesh->GetComponentTransform().TransformPosition(EquippedWeapon->MuzzleOffset);
	}

	return Fallback;
}

void UProjectEXWeaponComponent::HandleInventoryChanged()
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		SyncEquippedWeapon();
	}
}
