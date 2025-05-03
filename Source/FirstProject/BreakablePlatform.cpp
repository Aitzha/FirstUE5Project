// Copyright Epic Games, Inc. All Rights Reserved.

#include "BreakablePlatform.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbook.h"

ABreakablePlatform::ABreakablePlatform(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	InitializePlatformComponent(SpriteComponent);
	PlatformComponent->OnComponentHit.AddDynamic(this, &ABreakablePlatform::OnHit);
	
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComponent"));
	FlipbookComponent->SetupAttachment(RootComponent);
	FlipbookComponent->SetVisibility(false);
	FlipbookComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PlatformBoundaryComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("PlatformBoundaryComponent"));
	PlatformBoundaryComponent->SetupAttachment(RootComponent);
	PlatformBoundaryComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	PlatformBoundaryComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	PlatformBoundaryComponent->OnComponentEndOverlap.AddDynamic(this, &ABreakablePlatform::OnPlatformBoundaryComponentEndOverlap);
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
	
	PlatformBoundaryComponent->SetBoxExtent(PlatformComponent->GetLocalBounds().GetBox().GetExtent() + FVector(3.0f, 0.0f, 3.0f));
}

void ABreakablePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bPlayerTouchedPlatform)
	{
		BreakTimer += DeltaTime;
		if (BreakTimer >= BreakStageDuration)
		{
			UpdateBreakStage();
			BreakTimer = 0.0f;
		}
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

void ABreakablePlatform::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Cast<AMainCharacter>(OtherActor))
	{
		bPlayerTouchedPlatform = true;
	}
}

void ABreakablePlatform::OnPlatformBoundaryComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (bPlayerTouchedPlatform && Cast<AMainCharacter>(OtherActor))
	{
		BreakPlatform();
	}
}





