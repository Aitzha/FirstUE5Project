// Fill out your copyright notice in the Description page of Project Settings.

#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter() : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->JumpZVelocity = JumpForce;
	GetCharacterMovement()->AirControl = AirControl; 
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (ULocalPlayer* LP = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				Subsystem->AddMappingContext(InputMapping, 0);
			}
		}
	}

	UpdateHealthBar();
	// GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &APlayerCharacter::OnHit);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Location = GetActorLocation(); // Get current location
	Location.Y = 0;               // Change only Y axis
	SetActorLocation(Location); 
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveRight);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	}
}

void APlayerCharacter::MoveRight(const FInputActionValue& Value)
{
	const float Direction = Value.Get<float>();
	AddMovementInput(FVector(Direction, 0.0f, 0.0f));
}

UPaperSpriteComponent* APlayerCharacter::GetSprite()
{
	return nullptr;
}

// void APlayerCharacter::OnHit(UPrimitiveComponent* HitComponent,
// 						 AActor* OtherActor,
// 						 UPrimitiveComponent* OtherComp,
// 						 FVector NormalImpulse,
// 						 const FHitResult& Hit)
// {
// 	UE_LOG(LogTemp, Warning, TEXT("HIT! HIT HIT HIT"));
// }