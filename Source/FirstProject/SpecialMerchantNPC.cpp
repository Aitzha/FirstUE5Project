// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpecialMerchantNPC.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ASpecialMerchantNPC::ASpecialMerchantNPC(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void ASpecialMerchantNPC::BeginPlay()
{
	Super::BeginPlay();
}

void ASpecialMerchantNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpecialMerchantNPC::OnPlayerInteraction()
{
	Super::OnPlayerInteraction();

	if (InteractionWidgetClass)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
		if (PC)
		{
			UUserWidget* Widget = CreateWidget(PC, InteractionWidgetClass);
			if (Widget)
			{
				Widget->AddToViewport();
	
				// Optional: Show mouse + pause game
				// PC->SetShowMouseCursor(true);
				// PC->SetInputMode(FInputModeUIOnly());
	
				// Optional: Pause
				// UGameplayStatics::SetGamePaused(this, true);
			}
		}
	}
}
