// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterBase.h"
#include "PaperSpriteComponent.h"
#include "Components/CapsuleComponent.h"
#include "FirstProject/Components/HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACharacterBase::ACharacterBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Restrict rotation and Y motion
	GetCapsuleComponent()->BodyInstance.bLockXRotation = true;
	GetCapsuleComponent()->BodyInstance.bLockYRotation = true;
	GetCapsuleComponent()->BodyInstance.bLockZRotation = true;
	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);
	GetCharacterMovement()->bConstrainToPlane = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(RootComponent);
	SpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

