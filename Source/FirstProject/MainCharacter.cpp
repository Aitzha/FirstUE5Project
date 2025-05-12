// Copyright Epic Games, Inc. All Rights Reserved.

#include "MainCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HealthComponent.h"
#include "PaperSpriteComponent.h"
#include "Components/CapsuleComponent.h"

AMainCharacter::AMainCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	GetCapsuleComponent()->SetCollisionObjectType(ECC_GameTraceChannel1);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Block);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMainCharacter::OnHit);
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
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &AMainCharacter::JumpOrDrop);
		EnhancedInput->BindAction(DropDownAction, ETriggerEvent::Started, this, &AMainCharacter::DownKeyPressed);
		EnhancedInput->BindAction(DropDownAction, ETriggerEvent::Completed, this, &AMainCharacter::DownKeyReleased);
		EnhancedInput->BindAction(InteractAction, ETriggerEvent::Started, this, &AMainCharacter::Interact);
	}
}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	const float MoveValue = Value.Get<float>();
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), MoveValue);

	if (MoveValue == -1.0f && bIsLookingRight)
	{
		SpriteComponent->SetRelativeRotation(FRotator(0, 180, 0));
		bIsLookingRight = false;
	}
	
	if (MoveValue == 1.0f && !bIsLookingRight)
	{
		SpriteComponent->SetRelativeRotation(FRotator(0, 0, 0));
		bIsLookingRight = true;
	}
}

void AMainCharacter::JumpOrDrop(const FInputActionValue& Value)
{
	if (bIsDownKeyPressed)
	{
		OnDropDown.Broadcast(true);
	}
	else
	{
		Jump();
	}
}

void AMainCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComp->GetCollisionObjectType() == ECC_GameTraceChannel3)
	{
		HealthComponent->TakeDamage(DamageFromCollision);
	}
}
