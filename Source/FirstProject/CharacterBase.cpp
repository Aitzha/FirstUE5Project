// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterBase.h"
#include "HealthComponent.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

ACharacterBase::ACharacterBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	// Enable physics 
	BoxComponent->SetSimulatePhysics(true);
	BoxComponent->SetEnableGravity(true);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Block);
	BoxComponent->SetCollisionObjectType(ECC_PhysicsBody);

	// Restrict rotation and Y motion
	BoxComponent->BodyInstance.bLockXRotation = true;
	BoxComponent->BodyInstance.bLockYRotation = true;
	BoxComponent->BodyInstance.bLockZRotation = true;
	BoxComponent->BodyInstance.bLockYTranslation = true;

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

