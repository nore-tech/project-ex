// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectEXInteractionComponent.h"
#include "ProjectEXInteractable.h"
#include "ProjectEXInteractionPromptWidget.h"
#include "ProjectEXCharacter.h"
#include "Camera/CameraComponent.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"

UProjectEXInteractionComponent::UProjectEXInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	InteractKey = EKeys::F;
}

void UProjectEXInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	const APawn* Pawn = Cast<APawn>(GetOwner());
	SetComponentTickEnabled(Pawn && Pawn->IsLocallyControlled());

	if (Pawn && Pawn->IsLocallyControlled())
	{
		EnsurePromptWidget();
	}
}

void UProjectEXInteractionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PromptWidget)
	{
		PromptWidget->RemoveFromParent();
		PromptWidget = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

void UProjectEXInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn || !Pawn->IsLocallyControlled())
	{
		return;
	}

	UpdateFocusedActor();
}

void UProjectEXInteractionComponent::BindInput(UEnhancedInputComponent* EnhancedInput)
{
	if (!EnhancedInput)
	{
		return;
	}

	const APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn || !Pawn->IsLocallyControlled())
	{
		return;
	}

	EnsureInteractAction();
	if (!InteractAction)
	{
		return;
	}

	RegisterMappingContext(Pawn);
	EnhancedInput->BindAction(InteractAction, ETriggerEvent::Started, this, &UProjectEXInteractionComponent::RequestInteract);
	SetComponentTickEnabled(true);
	EnsurePromptWidget();
}

void UProjectEXInteractionComponent::RequestInteract()
{
	AActor* Target = FocusedActor.Get();
	if (!Target)
	{
		Target = TraceInteractable();
	}

	if (!Target)
	{
		return;
	}

	ServerRequestInteract(Target);
}

void UProjectEXInteractionComponent::ServerRequestInteract_Implementation(AActor* Target)
{
	AActor* TracedTarget = TraceInteractable();
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn || !TracedTarget || TracedTarget != Target)
	{
		return;
	}

	IProjectEXInteractable::Execute_Interact(TracedTarget, Pawn);
}

void UProjectEXInteractionComponent::EnsureInteractAction()
{
	if (InteractAction)
	{
		return;
	}

	InteractAction = NewObject<UInputAction>(this, TEXT("IA_Interact"));
	InteractAction->ValueType = EInputActionValueType::Boolean;

	InteractMappingContext = NewObject<UInputMappingContext>(this, TEXT("IMC_Interact"));
	InteractMappingContext->MapKey(InteractAction, InteractKey);
}

void UProjectEXInteractionComponent::RegisterMappingContext(const APawn* Pawn)
{
	if (bRegisteredMappingContext || !InteractMappingContext || !Pawn)
	{
		return;
	}

	const APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());
	if (!PlayerController || !PlayerController->IsLocalController())
	{
		return;
	}

	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	if (!LocalPlayer)
	{
		return;
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		Subsystem->AddMappingContext(InteractMappingContext, 0);
		bRegisteredMappingContext = true;
	}
}

void UProjectEXInteractionComponent::EnsurePromptWidget()
{
	if (PromptWidget || !GetWorld() || !GetWorld()->IsGameWorld())
	{
		return;
	}

	const APawn* Pawn = Cast<APawn>(GetOwner());
	APlayerController* PlayerController = Pawn ? Cast<APlayerController>(Pawn->GetController()) : nullptr;
	if (!PlayerController || !PlayerController->IsLocalController())
	{
		return;
	}

	TSubclassOf<UProjectEXInteractionPromptWidget> ClassToSpawn = PromptWidgetClass;
	if (!ClassToSpawn)
	{
		ClassToSpawn = UProjectEXInteractionPromptWidget::StaticClass();
	}

	PromptWidget = CreateWidget<UProjectEXInteractionPromptWidget>(PlayerController, ClassToSpawn);
	if (!PromptWidget)
	{
		return;
	}

	PromptWidget->SetIsFocusable(false);
	PromptWidget->SetVisibility(ESlateVisibility::Collapsed);
	PromptWidget->AddToViewport(0);
}

void UProjectEXInteractionComponent::UpdateFocusedActor()
{
	ApplyFocus(TraceInteractable());
}

void UProjectEXInteractionComponent::ApplyFocus(AActor* NewFocus)
{
	// Destroying the focused actor expires the weak pointer to null. That matches a missed
	// trace, so without the stale check the prompt would stay up after a successful pickup.
	if (NewFocus == FocusedActor.Get() && !FocusedActor.IsStale())
	{
		return;
	}

	FocusedActor = NewFocus;

	const FText Prompt = MakePrompt(NewFocus);
	if (PromptWidget)
	{
		if (NewFocus)
		{
			PromptWidget->SetPromptText(Prompt);
			PromptWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
		else
		{
			PromptWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	OnFocusChanged.Broadcast(NewFocus, Prompt);
}

bool UProjectEXInteractionComponent::GetTraceView(FVector& OutLocation, FRotator& OutRotation) const
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn)
	{
		return false;
	}

	// The local view uses the first-person camera so the prompt matches the crosshair.
	if (Pawn->IsLocallyControlled())
	{
		if (const AProjectEXCharacter* Character = Cast<AProjectEXCharacter>(Pawn))
		{
			if (const UCameraComponent* Camera = Character->GetFirstPersonCameraComponent())
			{
				OutLocation = Camera->GetComponentLocation();
				OutRotation = Camera->GetComponentRotation();
				return true;
			}
		}
	}

	// Remote pawns are validated from the replicated control rotation and eye height.
	// The first-person camera is attached to an owner-only mesh, so its server transform is not the view.
	if (const AController* Controller = Pawn->GetController())
	{
		OutRotation = Controller->GetControlRotation();
		OutLocation = Pawn->GetPawnViewLocation();
		return true;
	}

	return false;
}

AActor* UProjectEXInteractionComponent::TraceInteractable() const
{
	UWorld* World = GetWorld();
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!World || !Pawn)
	{
		return nullptr;
	}

	FVector Start;
	FRotator Rotation;
	if (!GetTraceView(Start, Rotation))
	{
		return nullptr;
	}

	const FVector End = Start + (Rotation.Vector() * InteractionRange);

	FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(ProjectEXInteraction), false, Pawn);
	FHitResult Hit;
	if (!World->LineTraceSingleByChannel(Hit, Start, End, TraceChannel, QueryParams))
	{
		return nullptr;
	}

	AActor* HitActor = Hit.GetActor();
	if (!HitActor || !HitActor->Implements<UProjectEXInteractable>())
	{
		return nullptr;
	}

	if (!IProjectEXInteractable::Execute_CanInteract(HitActor, Pawn))
	{
		return nullptr;
	}

	return HitActor;
}

FText UProjectEXInteractionComponent::MakePrompt(const AActor* Interactable) const
{
	if (!Interactable)
	{
		return FText::GetEmpty();
	}

	const FText Verb = IProjectEXInteractable::Execute_GetInteractionPrompt(Interactable);
	return FText::Format(NSLOCTEXT("ProjectEX", "InteractPromptFormat", "[{0}] {1}"), InteractKey.GetDisplayName(), Verb);
}
