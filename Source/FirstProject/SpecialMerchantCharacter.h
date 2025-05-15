// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbook.h"
#include "SpecialMerchantCharacter.generated.h"

USTRUCT(BlueprintType)
struct FSpecialMerchantCharacter
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CharacterTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UPaperFlipbook*> Stages;
};
