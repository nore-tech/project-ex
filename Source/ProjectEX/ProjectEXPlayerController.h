// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ProjectEXPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;
class UProjectEXRaidWidget;

UENUM(BlueprintType)
enum class EProjectEXRaidStatus : uint8
{
	Preparing,
	InRaid,
	Extracted,
	Dead
};

/**
 *  Simple first person Player Controller
 *  Manages the input mapping context.
 *  Overrides the Player Camera Manager class.
 */
UCLASS(abstract, config="Game")
class PROJECTEX_API AProjectEXPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	/** Constructor */
	AProjectEXPlayerController();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintPure, Category="Raid")
	EProjectEXRaidStatus GetRaidStatus() const { return RaidStatus; }

	UFUNCTION(BlueprintPure, Category="Raid")
	bool IsInRaid() const { return RaidStatus == EProjectEXRaidStatus::InRaid; }

	/** Whole seconds left on the active extraction, or -1 when not extracting. */
	UFUNCTION(BlueprintPure, Category="Raid")
	int32 GetExtractionSecondsLeft() const { return ExtractionSecondsLeft; }

	UFUNCTION(BlueprintPure, Category="Raid")
	FText GetExtractionName() const { return ExtractionName; }

	UFUNCTION(BlueprintPure, Category="Raid")
	int32 GetRaidKills() const { return RaidKills; }

	UFUNCTION(BlueprintPure, Category="Raid")
	float GetRaidDuration() const { return RaidDuration; }

	/** Server only. */
	void SetExtractionProgress(int32 SecondsLeft, const FText& ZoneName);

	/** Server only. Ends the raid as a success. Ignored unless in raid. */
	void CompleteExtraction(const FText& ZoneName);

	/** Server only. */
	void AddRaidKill();

	/** Reloads the encounter. Standalone reloads immediately; a listen server waits until nobody is still in raid. */
	UFUNCTION(BlueprintCallable, Category="Raid")
	void RequestDeployAgain();

	/** Development testing: moves the pawn to X Y on the arena floor. Standalone only. */
	UFUNCTION(Exec)
	void RaidTeleport(float X, float Y);

	/** Cosmetic. Runs on the owning client when the raid status changes. */
	UFUNCTION(BlueprintImplementableEvent, Category="Raid")
	void OnRaidStatusChanged(EProjectEXRaidStatus NewStatus);

protected:

	virtual void OnPossess(APawn* InPawn) override;

	/** Seconds in Preparing before enemies engage and extraction opens. */
	UPROPERTY(EditAnywhere, Category="Raid", meta=(ClampMin="0.0", Units="s"))
	float DeployDelay = 3.0f;

	/** Raid HUD. Defaults to the native widget; a Blueprint subclass can replace it. */
	UPROPERTY(EditAnywhere, Category="Raid")
	TSubclassOf<UProjectEXRaidWidget> RaidWidgetClass;

	UPROPERTY(ReplicatedUsing=OnRep_RaidStatus)
	EProjectEXRaidStatus RaidStatus = EProjectEXRaidStatus::Preparing;

	UPROPERTY(Replicated)
	int32 ExtractionSecondsLeft = -1;

	UPROPERTY(Replicated)
	FText ExtractionName;

	UPROPERTY(Replicated)
	int32 RaidKills = 0;

	UPROPERTY(Replicated)
	float RaidDuration = 0.0f;

	UFUNCTION()
	void OnRep_RaidStatus();

	UFUNCTION(Server, Reliable)
	void ServerDeployAgain();

	UFUNCTION()
	void HandlePawnDied(AController* InstigatorController);

	void BeginRaid();
	void SetRaidStatus(EProjectEXRaidStatus NewStatus);
	void ApplyLocalRaidStatus();

	UPROPERTY(Transient)
	TObjectPtr<UProjectEXRaidWidget> RaidWidget;

	FTimerHandle DeployTimer;
	float RaidStartTime = 0.0f;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	UPROPERTY()
	TObjectPtr<UUserWidget> MobileControlsWidget;

	/** If true, the player will use UMG touch controls even if not playing on mobile platforms */
	UPROPERTY(EditAnywhere, Config, Category = "Input|Touch Controls")
	bool bForceTouchControls = false;

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	/** Returns true if the player should use UMG touch controls */
	bool ShouldUseTouchControls() const;
};
