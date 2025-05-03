// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlatformBase.h"
#include "MainCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


APlatformBase::APlatformBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APlatformBase::OnBoxComponentBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APlatformBase::OnBoxComponentEndOverlap);
	PrimaryActorTick.bCanEverTick = true;
}

void APlatformBase::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    SetActorTickEnabled(false);
	FloorZPos = PlatformComponent->GetComponentLocation().Z + PlatformComponent->GetLocalBounds().GetBox().GetExtent().Z / 2;
}

void APlatformBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (!PlayerCharacter) return;
    if (!PlatformComponent) return;
	FloorZPos = PlatformComponent->GetComponentLocation().Z + PlatformComponent->GetLocalBounds().GetBox().GetExtent().Z / 2;
	const float PlayerLegsZPos = PlayerCharacter->GetCapsuleComponent()->GetComponentLocation().Z - PlayerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	ZDistanceFromCharacter = -(FloorZPos - PlayerLegsZPos);
    static float Timer = 0;
    if (bIsCharacterMovingDown)
    {
        Timer += DeltaTime;
        PlatformComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
        if (Timer > 0.2f)
        {
            bIsCharacterMovingDown = false;
            Timer = 0;
        }
    }
    else
    {
        if (ZDistanceFromCharacter < 5)
        {
            PlatformComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
        }
        else
        {
            PlatformComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
        }
    }
}

void APlatformBase::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetActorTickEnabled(true);
	PlayerCharacter->OnDropDown.AddDynamic(this, &APlatformBase::SetIsMovingDown);
}

void APlatformBase::OnBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
 	SetActorTickEnabled(false);
	PlayerCharacter->OnDropDown.RemoveDynamic(this, &APlatformBase::SetIsMovingDown);
}

void APlatformBase::InitializePlatformComponent(UPrimitiveComponent* InPlatformComponent)
{
    if (!InPlatformComponent) return;
    PlatformComponent = InPlatformComponent;
    PlatformComponent->SetupAttachment(RootComponent);
	PlatformComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    PlatformComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Block);
    PlatformComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}