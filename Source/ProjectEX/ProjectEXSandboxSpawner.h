// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectEXSandboxSpawner.generated.h"

class AProjectEXDamagePad;
class AProjectEXLootContainer;
class AProjectEXPickup;
class AProjectEXTargetDummy;
class UProjectEXItemDefinition;

/** Place in a level. On play, the server spawns a testing row beside this actor. */
UCLASS(Blueprintable)
class PROJECTEX_API AProjectEXSandboxSpawner : public AActor
{
	GENERATED_BODY()

public:

	AProjectEXSandboxSpawner();

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere, Category="Sandbox")
	TObjectPtr<UProjectEXItemDefinition> RifleItem;

	UPROPERTY(EditAnywhere, Category="Sandbox")
	TObjectPtr<UProjectEXItemDefinition> PistolItem;

	UPROPERTY(EditAnywhere, Category="Sandbox")
	TObjectPtr<UProjectEXItemDefinition> RifleAmmoItem;

	UPROPERTY(EditAnywhere, Category="Sandbox")
	TObjectPtr<UProjectEXItemDefinition> PistolAmmoItem;

	UPROPERTY(EditAnywhere, Category="Sandbox")
	TObjectPtr<UProjectEXItemDefinition> HelmetItem;

	UPROPERTY(EditAnywhere, Category="Sandbox")
	TObjectPtr<UProjectEXItemDefinition> BodyArmorItem;

	UPROPERTY(EditAnywhere, Category="Sandbox")
	TObjectPtr<UProjectEXItemDefinition> BackpackItem;

	UPROPERTY(EditAnywhere, Category="Sandbox")
	TObjectPtr<UProjectEXItemDefinition> BandageItem;

	UPROPERTY(EditAnywhere, Category="Sandbox")
	TObjectPtr<UProjectEXItemDefinition> MedicalKitItem;

	UPROPERTY(EditAnywhere, Category="Sandbox")
	TSubclassOf<AProjectEXPickup> PickupClass;

	UPROPERTY(EditAnywhere, Category="Sandbox")
	TSubclassOf<AProjectEXLootContainer> ContainerClass;

	UPROPERTY(EditAnywhere, Category="Sandbox")
	TSubclassOf<AProjectEXTargetDummy> DummyClass;

	UPROPERTY(EditAnywhere, Category="Sandbox")
	TSubclassOf<AProjectEXDamagePad> DamagePadClass;

	UPROPERTY(EditAnywhere, Category="Sandbox", meta=(ClampMin="1"))
	int32 AmmoStackSize = 60;

	UPROPERTY(EditAnywhere, Category="Sandbox", meta=(ClampMin="0.0", Units="cm"))
	float ColumnSpacing = 200.0f;

	UPROPERTY(EditAnywhere, Category="Sandbox", meta=(ClampMin="0.0", Units="cm"))
	float RowSpacing = 350.0f;

private:

	void ResolveDefaults();
	FVector SlotLocation(int32 Row, int32 Column, float ExtraHeight) const;
	void SpawnItem(UProjectEXItemDefinition* Definition, int32 Quantity, int32 MagazineRounds, const FVector& Location);
	void SpawnContainer(const FVector& Location, const TArray<TPair<UProjectEXItemDefinition*, int32>>& Items);
	void SpawnDummy(const FVector& Location);
	void SpawnDamagePad(const FVector& Location);
	FVector PlaceOnFloor(const FVector& Desired, float Lift) const;

	bool bHasSpawned = false;
};
