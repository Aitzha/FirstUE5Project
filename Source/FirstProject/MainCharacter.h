// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "MainCharacter.generated.h"

UCLASS(Blueprintable)
class FIRSTPROJECT_API AMainCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	AMainCharacter() = delete;
	AMainCharacter(const FObjectInitializer& ObjectInitializer);
};
