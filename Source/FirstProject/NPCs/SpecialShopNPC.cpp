// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpecialShopNPC.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ASpecialShopNPC::ASpecialShopNPC(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void ASpecialShopNPC::BeginPlay()
{
	Super::BeginPlay();
}

void ASpecialShopNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpecialShopNPC::OnPlayerInteraction()
{
	Super::OnPlayerInteraction();

	if (InteractionWidgetClass)
	{
		if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
		{
			if (UUserWidget* Widget = CreateWidget(PC, InteractionWidgetClass))
			{
				Widget->AddToViewport();
				
				PC->SetShowMouseCursor(true);
				PC->SetInputMode(FInputModeUIOnly());
			}
		}
	}
}
