// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "EnemyCharacter.generated.h"

UCLASS(Blueprintable)
class FIRSTPROJECT_API AEnemyCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	AEnemyCharacter() = delete;
	AEnemyCharacter(const FObjectInitializer& ObjectInitializer);
};
