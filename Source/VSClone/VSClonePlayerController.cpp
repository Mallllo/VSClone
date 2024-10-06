// Copyright Epic Games, Inc. All Rights Reserved.

#include "VSClonePlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "VSCloneCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AVSClonePlayerController::AVSClonePlayerController()
{
}

void AVSClonePlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void AVSClonePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Custom move input
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVSClonePlayerController::OnMove);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AVSClonePlayerController::OnMove(const FInputActionValue& Input)
{
	FVector2D InVector = Input.Get<FVector2D>();
	FVector MoveDirection = FVector(InVector.Y, InVector.X, 0);
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		ControlledPawn->AddMovementInput(MoveDirection, 1.0, false);
	}

}