// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"

AEnemyCharacter::AEnemyCharacter() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InitialLocation = GetActorLocation();
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	float DeltaMove = MoveSpeed * DeltaTime;
	float Offset = CurrentLocation.X - InitialLocation.X;

	if (bMovingRight)
	{
		CurrentLocation.X += DeltaMove;
		if (Offset >= PatrolDistance)
		{
			bMovingRight = false;
		}
	}
	else
	{
		CurrentLocation.X -= DeltaMove;
		if (Offset <= -PatrolDistance)
		{
			bMovingRight = true;
		}
	}

	SetActorLocation(CurrentLocation);
}