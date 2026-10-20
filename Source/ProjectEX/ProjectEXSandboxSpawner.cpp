// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXSandboxSpawner.h"
#include "ProjectEX.h"
#include "ProjectEXDamagePad.h"
#include "ProjectEXItemDefinition.h"
#include "ProjectEXLootContainer.h"
#include "ProjectEXPickup.h"
#include "ProjectEXTargetDummy.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

namespace
{
	UProjectEXItemDefinition* LoadItem(const TCHAR* Path)
	{
		return LoadObject<UProjectEXItemDefinition>(nullptr, Path);
	}
}

AProjectEXSandboxSpawner::AProjectEXSandboxSpawner()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;

	PickupClass = AProjectEXPickup::StaticClass();
	ContainerClass = AProjectEXLootContainer::StaticClass();
	DummyClass = AProjectEXTargetDummy::StaticClass();
	DamagePadClass = AProjectEXDamagePad::StaticClass();
}

void AProjectEXSandboxSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority() || bHasSpawned || GetNetMode() == NM_Client)
	{
		return;
	}

	bHasSpawned = true;
	ResolveDefaults();

	SpawnItem(RifleItem, 1, -1, PlaceOnFloor(SlotLocation(0, 0, 0.0f), 48.0f));
	SpawnItem(PistolItem, 1, -1, PlaceOnFloor(SlotLocation(0, 1, 0.0f), 48.0f));
	SpawnItem(RifleAmmoItem, AmmoStackSize, -1, PlaceOnFloor(SlotLocation(0, 2, 0.0f), 48.0f));
	SpawnItem(RifleAmmoItem, AmmoStackSize, -1, PlaceOnFloor(SlotLocation(0, 3, 0.0f), 48.0f));
	SpawnItem(PistolAmmoItem, AmmoStackSize, -1, PlaceOnFloor(SlotLocation(0, 4, 0.0f), 48.0f));

	SpawnItem(HelmetItem, 1, -1, PlaceOnFloor(SlotLocation(1, 0, 0.0f), 48.0f));
	SpawnItem(BodyArmorItem, 1, -1, PlaceOnFloor(SlotLocation(1, 1, 0.0f), 48.0f));
	SpawnItem(BackpackItem, 1, -1, PlaceOnFloor(SlotLocation(1, 2, 0.0f), 48.0f));

	SpawnItem(BandageItem, 1, -1, PlaceOnFloor(SlotLocation(2, 0, 0.0f), 48.0f));
	SpawnItem(BandageItem, 1, -1, PlaceOnFloor(SlotLocation(2, 1, 0.0f), 48.0f));
	SpawnItem(BandageItem, 1, -1, PlaceOnFloor(SlotLocation(2, 2, 0.0f), 48.0f));
	SpawnItem(MedicalKitItem, 1, -1, PlaceOnFloor(SlotLocation(2, 3, 0.0f), 48.0f));
	SpawnItem(MedicalKitItem, 1, -1, PlaceOnFloor(SlotLocation(2, 4, 0.0f), 48.0f));

	TArray<TPair<UProjectEXItemDefinition*, int32>> FirstContainer;
	FirstContainer.Emplace(RifleItem, 1);
	FirstContainer.Emplace(RifleAmmoItem, AmmoStackSize);
	FirstContainer.Emplace(BandageItem, 2);
	FirstContainer.Emplace(HelmetItem, 1);
	SpawnContainer(PlaceOnFloor(SlotLocation(3, 0, 0.0f), 0.0f), FirstContainer);

	TArray<TPair<UProjectEXItemDefinition*, int32>> SecondContainer;
	SecondContainer.Emplace(PistolItem, 1);
	SecondContainer.Emplace(PistolAmmoItem, AmmoStackSize);
	SecondContainer.Emplace(BodyArmorItem, 1);
	SecondContainer.Emplace(BackpackItem, 1);
	SecondContainer.Emplace(MedicalKitItem, 1);
	SpawnContainer(PlaceOnFloor(SlotLocation(3, 1, 0.0f), 0.0f), SecondContainer);

	SpawnDummy(PlaceOnFloor(SlotLocation(4, 0, 0.0f), 90.0f));
	SpawnDummy(PlaceOnFloor(SlotLocation(4, 1, 0.0f), 90.0f));
	SpawnDamagePad(PlaceOnFloor(SlotLocation(5, 0, 0.0f), 8.0f));
}

void AProjectEXSandboxSpawner::ResolveDefaults()
{
	if (!RifleItem)
	{
		RifleItem = LoadItem(TEXT("/Game/FirstPerson/Weapons/DA_Rifle.DA_Rifle"));
	}
	if (!PistolItem)
	{
		PistolItem = LoadItem(TEXT("/Game/FirstPerson/Weapons/DA_Pistol.DA_Pistol"));
	}
	if (!RifleAmmoItem)
	{
		RifleAmmoItem = LoadItem(TEXT("/Game/FirstPerson/Weapons/DA_Ammo_556.DA_Ammo_556"));
	}
	if (!PistolAmmoItem)
	{
		PistolAmmoItem = LoadItem(TEXT("/Game/FirstPerson/Weapons/DA_Ammo_9mm.DA_Ammo_9mm"));
	}
	if (!HelmetItem)
	{
		HelmetItem = LoadItem(TEXT("/Game/FirstPerson/Equipment/DA_Helmet.DA_Helmet"));
	}
	if (!BodyArmorItem)
	{
		BodyArmorItem = LoadItem(TEXT("/Game/FirstPerson/Equipment/DA_BodyArmor.DA_BodyArmor"));
	}
	if (!BackpackItem)
	{
		BackpackItem = LoadItem(TEXT("/Game/FirstPerson/Equipment/DA_Backpack.DA_Backpack"));
	}
	if (!BandageItem)
	{
		BandageItem = LoadItem(TEXT("/Game/FirstPerson/DA_Bandage.DA_Bandage"));
	}
	if (!MedicalKitItem)
	{
		MedicalKitItem = LoadItem(TEXT("/Game/FirstPerson/DA_MedicalKit.DA_MedicalKit"));
	}
}

FVector AProjectEXSandboxSpawner::SlotLocation(int32 Row, int32 Column, float ExtraHeight) const
{
	return GetActorLocation()
		+ (GetActorForwardVector() * (static_cast<float>(Row) * RowSpacing))
		+ (GetActorRightVector() * (static_cast<float>(Column) * ColumnSpacing))
		+ FVector(0.0f, 0.0f, ExtraHeight);
}

void AProjectEXSandboxSpawner::SpawnItem(UProjectEXItemDefinition* Definition, int32 Quantity, int32 MagazineRounds, const FVector& Location)
{
	UWorld* World = GetWorld();
	if (!World || !Definition || Quantity <= 0)
	{
		if (!Definition)
		{
			UE_LOG(LogProjectEX, Warning, TEXT("%s skipped a sandbox pickup because its item definition is missing."), *GetName());
		}
		return;
	}

	TSubclassOf<AProjectEXPickup> Class = PickupClass;
	if (Definition->PickupClass)
	{
		Class = Definition->PickupClass;
	}
	if (!Class)
	{
		Class = AProjectEXPickup::StaticClass();
	}

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AProjectEXPickup* Pickup = World->SpawnActor<AProjectEXPickup>(Class, Location, GetActorRotation(), Params);
	if (!Pickup)
	{
		return;
	}

	Pickup->SetItemStack(Definition, Quantity);
	Pickup->SetStoredMagazine(MagazineRounds);
}

FVector AProjectEXSandboxSpawner::PlaceOnFloor(const FVector& Desired, float Lift) const
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return Desired + FVector(0.0f, 0.0f, Lift);
	}

	FCollisionQueryParams Params(SCENE_QUERY_STAT(SandboxFloor), false, this);
	FHitResult Hit;
	const FVector Start = Desired + FVector(0.0f, 0.0f, 200.0f);
	const FVector End = Desired - FVector(0.0f, 0.0f, 2000.0f);
	if (World->LineTraceSingleByChannel(Hit, Start, End, ECC_WorldStatic, Params))
	{
		return FVector(Desired.X, Desired.Y, Hit.ImpactPoint.Z + Lift);
	}

	return Desired + FVector(0.0f, 0.0f, Lift);
}

void AProjectEXSandboxSpawner::SpawnContainer(const FVector& Location, const TArray<TPair<UProjectEXItemDefinition*, int32>>& Items)
{
	UWorld* World = GetWorld();
	TSubclassOf<AProjectEXLootContainer> Class = ContainerClass ? ContainerClass : TSubclassOf<AProjectEXLootContainer>(AProjectEXLootContainer::StaticClass());
	if (!World || !Class)
	{
		return;
	}

	const FTransform Transform(GetActorRotation(), Location);
	AProjectEXLootContainer* Container = World->SpawnActorDeferred<AProjectEXLootContainer>(Class, Transform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (!Container)
	{
		return;
	}

	for (const TPair<UProjectEXItemDefinition*, int32>& Item : Items)
	{
		Container->AddItem(Item.Key, Item.Value, -1);
	}

	UGameplayStatics::FinishSpawningActor(Container, Transform);
}

void AProjectEXSandboxSpawner::SpawnDummy(const FVector& Location)
{
	UWorld* World = GetWorld();
	TSubclassOf<AProjectEXTargetDummy> Class = DummyClass ? DummyClass : TSubclassOf<AProjectEXTargetDummy>(AProjectEXTargetDummy::StaticClass());
	if (!World || !Class)
	{
		return;
	}

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	World->SpawnActor<AProjectEXTargetDummy>(Class, Location, GetActorRotation(), Params);
}

void AProjectEXSandboxSpawner::SpawnDamagePad(const FVector& Location)
{
	UWorld* World = GetWorld();
	TSubclassOf<AProjectEXDamagePad> Class = DamagePadClass ? DamagePadClass : TSubclassOf<AProjectEXDamagePad>(AProjectEXDamagePad::StaticClass());
	if (!World || !Class)
	{
		return;
	}

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	World->SpawnActor<AProjectEXDamagePad>(Class, Location, GetActorRotation(), Params);
}
