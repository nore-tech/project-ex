// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ProjectEXCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UProjectEXInteractionComponent;
class UProjectEXInventoryComponent;
class UProjectEXLootComponent;
class UProjectEXHealthComponent;
class UProjectEXWeaponComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A basic first person character
 */
UCLASS(abstract, Blueprintable)
class AProjectEXCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: first person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Look-trace interaction. Does not affect movement or camera. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectEXInteractionComponent> InteractionComponent;

	/** Per-player inventory. Does not affect movement or camera. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectEXInventoryComponent> InventoryComponent;

	/** Searchable container session. Does not affect movement or camera. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectEXLootComponent> LootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectEXHealthComponent> HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectEXWeaponComponent> WeaponComponent;

protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* MouseLookAction;

	/** Sprint Input Action. Held down to sprint. */
	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* SprintInputAction;

	/** Crouch Input Action. Pressed to toggle crouch. */
	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* CrouchInputAction;

	/** Copied onto CharacterMovement. Existing falling brake. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement", meta=(ClampMin="0.0", AllowPrivateAccess="true"))
	float FallingBrakingDeceleration = 1500.0f;

	/** Copied onto CharacterMovement. Existing air control. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement", meta=(ClampMin="0.0", ClampMax="1.0", AllowPrivateAccess="true"))
	float AirControl = 0.5f;

	/** Standing walk speed applied to CharacterMovement. Matches the existing 600 default. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement", meta=(ClampMin="0.0", Units="cm/s", AllowPrivateAccess="true"))
	float WalkMoveSpeed = 600.0f;

	/** Sprint speed. Roughly 1.5x walking. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement", meta=(ClampMin="0.0", Units="cm/s", AllowPrivateAccess="true"))
	float SprintMoveSpeed = 900.0f;

	/** Crouched speed. Roughly half of walking. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement", meta=(ClampMin="0.0", Units="cm/s", AllowPrivateAccess="true"))
	float CrouchMoveSpeed = 300.0f;

	/** How fast the view eases to the crouched eye height. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement", meta=(ClampMin="0.1", AllowPrivateAccess="true"))
	float CrouchViewInterpSpeed = 12.0f;
	
public:
	AProjectEXCharacter();

	/** True while the sprint input is held and sprinting is currently allowed. */
	UFUNCTION(BlueprintPure, Category="Movement")
	bool IsSprinting() const { return bSprintHeld; }

	UFUNCTION(BlueprintPure, Category="Movement")
	float GetSprintSpeed() const { return SprintMoveSpeed; }

	UFUNCTION(BlueprintPure, Category="Movement")
	float GetCrouchSpeed() const { return CrouchMoveSpeed; }

protected:

	/** Called from Input Actions for movement input */
	void MoveInput(const FInputActionValue& Value);

	/** Called from Input Actions for looking input */
	void LookInput(const FInputActionValue& Value);

	/** Handles aim inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoAim(float Yaw, float Pitch);

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles jump start inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump end inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	/** Handles sprint start inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoSprintStart();

	/** Handles sprint end inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoSprintEnd();

	/** Handles crouch toggle inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoCrouchToggle();

protected:

	void ApplyPolygonMeshes();

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	UFUNCTION()
	void HandleDied(AController* InstigatorController);

	/** Keeps CharacterMovement in sync with sprint, crouch, aim and death state. */
	void UpdateMovementSpeed();

	/** Eases the first-person camera between standing and crouched height. */
	void UpdateCrouchView(float DeltaSeconds);

	virtual void Tick(float DeltaSeconds) override;
	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	/** Camera location at standing height. Mirrors the constructor value. */
	FVector BaseCameraLocation = FVector(-2.8f, 5.89f, 0.0f);

	/** Offset added to the camera while a crouch transition eases out. */
	float CrouchViewOffset = 0.0f;

	/** Sprint input is held. Sprinting also requires standing, alive and not aiming. */
	bool bSprintHeld = false;
	

public:

	/** Returns the first person mesh **/
	USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Returns first person camera component **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	/** Returns the interaction component **/
	UProjectEXInteractionComponent* GetInteractionComponent() const { return InteractionComponent; }

	/** Returns the inventory component **/
	UProjectEXInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

	/** Returns the loot container session **/
	UProjectEXLootComponent* GetLootComponent() const { return LootComponent; }

	UProjectEXHealthComponent* GetHealthComponent() const { return HealthComponent; }

	UProjectEXWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }

};

