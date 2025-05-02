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
	if (BreakStagesSprites.Num() > 0 && SpriteComponent)
	{
		SpriteComponent->SetSprite(BreakStagesSprites[0]);
	}
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
	
	const float XDistanceBetwennCharacterAndPlatform = FMath::Abs(-(FloorLocation.X - PlayerCharacter->GetCapsuleComponent()->GetComponentLocation().X));
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Emerald, FString::FromInt(XDistanceBetwennCharacterAndPlatform));
	bool CharacterWithinThePlatform = XDistanceBetwennCharacterAndPlatform < PlatformComponent->GetLocalBounds().GetBox().GetExtent().X + PlayerCharacter->GetCapsuleComponent()->GetUnscaledCapsuleRadius();
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
	CurrentBreakStage++;
	if (CurrentBreakStage < BreakStagesSprites.Num())
	{
		SpriteComponent->SetSprite(BreakStagesSprites[CurrentBreakStage]);
	}
	else
	{
		BreakPlatform();
	}
}

void ABreakablePlatform::BreakPlatform()
{
	// CHANGE HERE: Added logic to remove platform collision
	/* Reasoning 
	 * 1) No logic of changing platform component collision to overlap was added. Meaning that character might be
	 * standing on platform during break animation
	 * 2) Destroying platform would be enough since platform component will be deleted as well but platform destruction
	 * would happen only after animation, and it might look weird for players to see character standing on platform that
	 * in the process of destruction for a split second.
	 * 3) Simply changing platform component collision to overlap might not be enough since it could be changed back to
	 * block in Tick function of the parent class
	 */
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlatformComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	SetActorTickEnabled(false);
	
	SpriteComponent->SetVisibility(false);
	FlipbookComponent->SetVisibility(true);
	FlipbookComponent->PlayFromStart();
	float FlipbookDuration = BreakFlipbook->GetTotalDuration();

	// CHANGE HERE: Change logic of platform destruction
	// if (bIsSingleUse)
	// {
	// 	CTimerManager::DelayFunction(this, "Destroy", FlipbookDuration, [this]() {Destroy(); }, false);
	// }
	// else
	// {
	// 	CTimerManager::DelayFunction(this, "ResetPlatform", FlipbookDuration + PlatformResetTime, [this]() {ResetPlatform(); }, false);
	// }
}

void ABreakablePlatform::ResetPlatform()
{
	// Reset platform somehow
}




