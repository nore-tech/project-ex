// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectEXPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "ProjectEXCameraManager.h"
#include "Blueprint/UserWidget.h"
#include "ProjectEX.h"
#include "ProjectEXHealthComponent.h"
#include "ProjectEXRaidWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"
#include "Widgets/Input/SVirtualJoystick.h"

AProjectEXPlayerController::AProjectEXPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AProjectEXCameraManager::StaticClass();
	RaidWidgetClass = UProjectEXRaidWidget::StaticClass();
}

void AProjectEXPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AProjectEXPlayerController, RaidStatus);
	DOREPLIFETIME_CONDITION(AProjectEXPlayerController, ExtractionSecondsLeft, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AProjectEXPlayerController, ExtractionName, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AProjectEXPlayerController, RaidKills, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AProjectEXPlayerController, RaidDuration, COND_OwnerOnly);
}

void AProjectEXPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		SetInputMode(FInputModeGameOnly());
		SetShowMouseCursor(false);

		if (RaidWidgetClass)
		{
			RaidWidget = CreateWidget<UProjectEXRaidWidget>(this, RaidWidgetClass);
			if (RaidWidget)
			{
				RaidWidget->AddToViewport(20);
			}
		}
		ApplyLocalRaidStatus();
	}

	
	// only spawn touch controls on local player controllers
	if (IsLocalPlayerController() && ShouldUseTouchControls())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogProjectEX, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void AProjectEXPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
	
}

bool AProjectEXPlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}

void AProjectEXPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!InPawn)
	{
		return;
	}

	if (UProjectEXHealthComponent* Health = InPawn->FindComponentByClass<UProjectEXHealthComponent>())
	{
		Health->OnDied.AddUniqueDynamic(this, &AProjectEXPlayerController::HandlePawnDied);
	}

	if (RaidStatus == EProjectEXRaidStatus::Preparing)
	{
		RaidKills = 0;
		RaidDuration = 0.0f;
		ExtractionSecondsLeft = -1;
		if (DeployDelay > 0.0f)
		{
			GetWorldTimerManager().SetTimer(DeployTimer, this, &AProjectEXPlayerController::BeginRaid, DeployDelay, false);
		}
		else
		{
			BeginRaid();
		}
	}
}

void AProjectEXPlayerController::BeginRaid()
{
	if (RaidStatus != EProjectEXRaidStatus::Preparing)
	{
		return;
	}
	RaidStartTime = GetWorld()->GetTimeSeconds();
	SetRaidStatus(EProjectEXRaidStatus::InRaid);
}

void AProjectEXPlayerController::SetRaidStatus(EProjectEXRaidStatus NewStatus)
{
	if (!HasAuthority() || RaidStatus == NewStatus)
	{
		return;
	}

	RaidStatus = NewStatus;
	UE_LOG(LogProjectEX, Log, TEXT("Raid status %s: %s"), *GetName(), *UEnum::GetValueAsString(NewStatus));
	if (NewStatus == EProjectEXRaidStatus::Extracted || NewStatus == EProjectEXRaidStatus::Dead)
	{
		RaidDuration = GetWorld()->GetTimeSeconds() - RaidStartTime;
		ExtractionSecondsLeft = -1;
		GetWorldTimerManager().ClearTimer(DeployTimer);
	}

	if (NewStatus == EProjectEXRaidStatus::Extracted)
	{
		if (ACharacter* RaidCharacter = GetCharacter())
		{
			RaidCharacter->GetCharacterMovement()->StopMovementImmediately();
			RaidCharacter->GetCharacterMovement()->DisableMovement();
		}
	}

	if (IsLocalController())
	{
		ApplyLocalRaidStatus();
	}
}

void AProjectEXPlayerController::OnRep_RaidStatus()
{
	ApplyLocalRaidStatus();
}

void AProjectEXPlayerController::ApplyLocalRaidStatus()
{
	if (!IsLocalPlayerController())
	{
		return;
	}

	const bool bFinished = RaidStatus == EProjectEXRaidStatus::Extracted || RaidStatus == EProjectEXRaidStatus::Dead;
	if (bFinished)
	{
		FInputModeUIOnly InputMode;
		if (RaidWidget)
		{
			RaidWidget->RefreshStatus();
			InputMode.SetWidgetToFocus(RaidWidget->GetFocusTarget());
		}
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputMode);
		SetShowMouseCursor(true);
		FlushPressedKeys();
	}

	if (RaidWidget)
	{
		RaidWidget->RefreshStatus();
	}
	OnRaidStatusChanged(RaidStatus);
}

void AProjectEXPlayerController::SetExtractionProgress(int32 SecondsLeft, const FText& ZoneName)
{
	if (!HasAuthority())
	{
		return;
	}
	ExtractionSecondsLeft = RaidStatus == EProjectEXRaidStatus::InRaid ? SecondsLeft : -1;
	ExtractionName = ZoneName;
}

void AProjectEXPlayerController::CompleteExtraction(const FText& ZoneName)
{
	if (!HasAuthority() || RaidStatus != EProjectEXRaidStatus::InRaid)
	{
		return;
	}
	ExtractionName = ZoneName;
	SetRaidStatus(EProjectEXRaidStatus::Extracted);
}

void AProjectEXPlayerController::AddRaidKill()
{
	if (HasAuthority() && RaidStatus == EProjectEXRaidStatus::InRaid)
	{
		++RaidKills;
	}
}

void AProjectEXPlayerController::HandlePawnDied(AController* InstigatorController)
{
	if (RaidStatus == EProjectEXRaidStatus::Preparing || RaidStatus == EProjectEXRaidStatus::InRaid)
	{
		SetRaidStatus(EProjectEXRaidStatus::Dead);
	}
}

void AProjectEXPlayerController::RaidTeleport(float X, float Y)
{
#if !UE_BUILD_SHIPPING
	if (GetNetMode() == NM_Standalone && GetPawn())
	{
		GetPawn()->TeleportTo(FVector(X, Y, 100.0f), GetPawn()->GetActorRotation());
	}
#endif
}

void AProjectEXPlayerController::RequestDeployAgain()
{
	ServerDeployAgain();
}

void AProjectEXPlayerController::ServerDeployAgain_Implementation()
{
	if (RaidStatus == EProjectEXRaidStatus::InRaid || RaidStatus == EProjectEXRaidStatus::Preparing)
	{
		return;
	}

	UWorld* World = GetWorld();
	const FString LevelName = UGameplayStatics::GetCurrentLevelName(this, true);
	if (World->GetNetMode() == NM_Standalone)
	{
		UGameplayStatics::OpenLevel(this, FName(*LevelName));
		return;
	}

	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		const AProjectEXPlayerController* Other = Cast<AProjectEXPlayerController>(It->Get());
		if (Other && (Other->RaidStatus == EProjectEXRaidStatus::InRaid || Other->RaidStatus == EProjectEXRaidStatus::Preparing))
		{
			return;
		}
	}
	World->ServerTravel(LevelName + TEXT("?listen"));
}
