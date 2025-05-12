// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "NPCBase.h"
#include "SpecialMerchantNPC.generated.h"

UCLASS(Blueprintable)
class FIRSTPROJECT_API ASpecialMerchantNPC : public ANPCBase
{
	GENERATED_BODY()

public:
	ASpecialMerchantNPC(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	// UPROPERTY(EditDefaultsOnly, Category = "UI")
	// TSubclassOf<UUserWidget> InteractionWidgetClass;
};
