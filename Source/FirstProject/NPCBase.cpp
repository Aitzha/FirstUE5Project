// Copyright Epic Games, Inc. All Rights Reserved.

#include "NPCBase.h"

#include "MainCharacter.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


ANPCBase::ANPCBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	RootComponent = BoxComponent;
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ANPCBase::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ANPCBase::OnOverlapEnd);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(RootComponent);
	SpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ANPCBase::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void ANPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANPCBase::OnPlayerInteraction()
{
	UE_LOG(LogTemp, Warning, TEXT("Player interacted with NPC"));
}

void ANPCBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap begin"));
	bIsPlayerInRange = true;
	PlayerCharacter->OnPlayerInteract.AddDynamic(this, &ANPCBase::OnPlayerInteraction);
}

void ANPCBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap end"));
	bIsPlayerInRange = false;
	PlayerCharacter->OnPlayerInteract.RemoveDynamic(this, &ANPCBase::OnPlayerInteraction);
}

