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
