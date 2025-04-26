// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.generated.h"

class UBoxComponent;
class UPaperSpriteComponent;
class UHealthComponent;

UCLASS(Abstract, NotBlueprintable)
class FIRSTPROJECT_API ACharacterBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ACharacterBase() = delete;
	ACharacterBase(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* HealthComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperSpriteComponent* SpriteComponent;
};
