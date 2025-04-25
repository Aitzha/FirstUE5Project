// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformBase.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


APlatformBase::APlatformBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	// BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	// BoxComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APlatformBase::OnBoxComponentBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APlatformBase::OnBoxComponentEndOverlap);
	PrimaryActorTick.bCanEverTick = true;
}

void APlatformBase::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    SetActorTickEnabled(false);
    FloorLocation = PlatformComponent->GetComponentLocation();
    FloorLocation.Z += PlatformComponent->GetLocalBounds().GetBox().GetExtent().Z / 2;
}

void APlatformBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (!PlayerCharacter) return;
    if (!PlatformComponent) return;
    FloorLocation = PlatformComponent->GetComponentLocation();
    FloorLocation.Z += PlatformComponent->GetLocalBounds().GetBox().GetExtent().Z / 2;
    const float DistanceBetweenCharacterAndPlatform = -(FloorLocation.Z - PlayerCharacter->GetActorLocation().Z);
    static float Timer = 0;
    if (bIsCharacterMovingDown)
    {
        Timer += DeltaTime;
    	PlatformComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
        // PlatformComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
        if (Timer > 0.2f)
        {
            bIsCharacterMovingDown = false;
            Timer = 0;
        }
    }
    else
    {
        if (DistanceBetweenCharacterAndPlatform < 0)
        {
        	PlatformComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
            // PlatformComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
        }
        else
        {
        	PlatformComponent->SetCollisionResponseToAllChannels(ECR_Block);
            // PlatformComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
        }
    }
}

void APlatformBase::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetActorTickEnabled(true);
}

void APlatformBase::OnBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
 	SetActorTickEnabled(false);
	PlatformComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
}

void APlatformBase::InitializePlatformComponent(UPrimitiveComponent* InPlatformComponent)
{
    if (!InPlatformComponent) return;
    PlatformComponent = InPlatformComponent;
    PlatformComponent->SetupAttachment(RootComponent);
	PlatformComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	// PlatformComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    // PlatformComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
    // PlatformComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Block);
    // PlatformComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}