// Copyright Epic Games, Inc. All Rights Reserved.

#include "BreakablePlatform.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbook.h"
#include "Components/CapsuleComponent.h"

ABreakablePlatform::ABreakablePlatform(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer), SpriteComponent{ CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent")) }
{
	InitializePlatformComponent(SpriteComponent);
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComponent"));
	FlipbookComponent->SetupAttachment(RootComponent);
	FlipbookComponent->SetVisibility(false);
	FlipbookComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABreakablePlatform::BeginPlay()
{
	Super::BeginPlay();
	if (FlipbookComponent && BreakFlipbook)
	{
		FlipbookComponent->SetFlipbook(BreakFlipbook);
		FlipbookComponent->SetLooping(false);
		FlipbookComponent->Stop();
	}
}

void ABreakablePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	const float XDistanceBetweenCharacterAndPlatform = FMath::Abs(-(FloorLocation.X - PlayerCharacter->GetCapsuleComponent()->GetComponentLocation().X));
	bool CharacterWithinThePlatform = XDistanceBetweenCharacterAndPlatform < PlatformComponent->GetLocalBounds().GetBox().GetExtent().X + PlayerCharacter->GetCapsuleComponent()->GetUnscaledCapsuleRadius();
	if (ZDistanceBetweenCharacterAndPlatform > 0 && CharacterWithinThePlatform)
	{
		bPlayerTouchedPlatform = true;
		bIsBreaking = true;
		BreakTimer += DeltaTime;
		if (BreakTimer >= BreakStageDuration)
		{
			UpdateBreakStage();
			BreakTimer = 0.0f;
		}
	}
	else
	{
		if (bPlayerTouchedPlatform)
		{
			BreakPlatform();
		}
		
		bIsBreaking = false;
		BreakTimer = 0.0f;
	}
}

void ABreakablePlatform::UpdateBreakStage()
{
	
	if (CurrentBreakStage < BreakStagesSprites.Num())
	{
		SpriteComponent->SetSprite(BreakStagesSprites[CurrentBreakStage]);
		CurrentBreakStage++;
	}
	else
	{
		BreakPlatform();
	}
}

void ABreakablePlatform::BreakPlatform()
{
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlatformComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	SetActorTickEnabled(false);
	
	SpriteComponent->SetVisibility(false);
	FlipbookComponent->SetVisibility(true);
	FlipbookComponent->PlayFromStart();
	float FlipbookDuration = BreakFlipbook->GetTotalDuration();
	
	if (bIsSingleUse)
	{
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, [this]() { Destroy(); }, FlipbookDuration, false);
	}
	else
	{
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABreakablePlatform::ResetPlatform, FlipbookDuration, false);
	}
}

void ABreakablePlatform::ResetPlatform()
{
	// Reset platform somehow
}




