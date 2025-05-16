// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "NPCBase.h"
#include "SpecialShopNPC.generated.h"

UCLASS(Blueprintable)
class FIRSTPROJECT_API ASpecialShopNPC : public ANPCBase
{
	GENERATED_BODY()

public:
	ASpecialShopNPC(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void OnPlayerInteraction() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> InteractionWidgetClass;
};
