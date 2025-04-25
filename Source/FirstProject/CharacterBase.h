// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.generated.h"

UCLASS(Abstract, NotBlueprintable)
class FIRSTPROJECT_API ACharacterBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ACharacterBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
