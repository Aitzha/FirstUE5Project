// Copyright Epic Games, Inc. All Rights Reserved.

#include "MainCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AMainCharacter::AMainCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &AMainCharacter::Jump);
		EnhancedInput->BindAction(DropDownAction, ETriggerEvent::Started, this, &AMainCharacter::DropDown);
	}
}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value.Get<float>());
}

void AMainCharacter::DropDown(const FInputActionValue& Value)
{
	// float InputValue = Value.Get<float>();
	// AddMovementInput(FVector(1.0f, 0.0f, 0.0f), InputValue);
}

