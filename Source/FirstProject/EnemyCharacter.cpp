// Copyright Epic Games, Inc. All Rights Reserved.


#include "EnemyCharacter.h"
#include "Components/CapsuleComponent.h"

AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	GetCapsuleComponent()->SetCollisionObjectType(ECC_GameTraceChannel3);
}
