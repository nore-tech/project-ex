// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectEXInteractable.h"
#include "ProjectEXPickup.generated.h"

class UProjectEXItemDefinition;
class UStaticMeshComponent;

/**
 *  World item. The server adds it to the interactor's inventory and destroys it only when that succeeds.
 */
UCLASS(Blueprintable)
class PROJECTEX_API AProjectEXPickup : public AActor, public IProjectEXInteractable
{
	GENERATED_BODY()

	/** Visible mesh. Line traces hit this component. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

protected:

	/** Verb used when this pickup has no item definition. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	FText InteractionPrompt;

	UPROPERTY(ReplicatedUsing=OnRep_ItemStack, EditAnywhere, BlueprintReadOnly, Category="Pickup")
	TObjectPtr<UProjectEXItemDefinition> ItemDefinition;

	UPROPERTY(ReplicatedUsing=OnRep_ItemStack, EditAnywhere, BlueprintReadOnly, Category="Pickup", meta=(ClampMin="1"))
	int32 Quantity = 1;

	/** Speed applied when this pickup is dropped. */
	UPROPERTY(EditAnywhere, Category="Pickup|Drop", meta=(ClampMin="0.0", Units="cm/s"))
	float DropImpulseSpeed = 180.0f;

	/** How long the item must stay nearly still before physics turns off. */
	UPROPERTY(EditAnywhere, Category="Pickup|Drop", meta=(ClampMin="0.1", Units="s"))
	float DropRestTime = 0.5f;

public:

	AProjectEXPickup();

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual FText GetInteractionPrompt_Implementation() const override;
	virtual bool CanInteract_Implementation(APawn* Interactor) const override;
	virtual void Interact_Implementation(APawn* Interactor) override;

	/** Authority, or a pickup that has not begun play yet, may set the stack that this actor grants. */
	UFUNCTION(BlueprintCallable, Category="Pickup")
	void SetItemStack(UProjectEXItemDefinition* InDefinition, int32 InQuantity);

	/** Server-only. Simulates a short drop, replicates physics, then sleeps when the item settles. */
	void StartDropPhysics();

	UStaticMeshComponent* GetMesh() const { return Mesh; }
	UProjectEXItemDefinition* GetItemDefinition() const { return ItemDefinition; }
	int32 GetQuantity() const { return Quantity; }

protected:

	UFUNCTION()
	void OnRep_ItemStack();

	void ApplyVisuals();
	void ConfigureMeshCollision();
	void ApplyDropImpulse();
	void SettleDropPhysics();

private:

	/** Server latch so a second interact cannot collect the same pickup. */
	bool bCollected = false;

	bool bDropPhysicsActive = false;
	float DropRestElapsed = 0.0f;
	float DropPhysicsElapsed = 0.0f;

	static constexpr float DropRestSpeed = 12.0f;
	static constexpr float DropRestAngularSpeed = 20.0f;
	static constexpr float MaxDropPhysicsTime = 8.0f;
};
