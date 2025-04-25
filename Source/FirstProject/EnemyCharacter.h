// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class FIRSTPROJECT_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:	
	AEnemyCharacter();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Patrol")
	float PatrolDistance = 150.f;

	UPROPERTY(EditDefaultsOnly, Category = "Patrol")
	float MoveSpeed = 150.f;

	FVector InitialLocation;
	
	bool bMovingRight = true;
};