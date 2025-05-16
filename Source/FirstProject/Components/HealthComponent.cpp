// Copyright Epic Games, Inc. All Rights Reserved.

#include "HealthComponent.h"

UHealthComponent::UHealthComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;

	CurrentHealth = MaxHealth;
	LastTimeDamageTaken -= DamageTakeCooldown;
}

float UHealthComponent::GetHealthPercentage()
{
	return static_cast<float>(CurrentHealth) / MaxHealth;
}

int UHealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

void UHealthComponent::TakeDamage(int damage)
{
	double CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - LastTimeDamageTaken < DamageTakeCooldown)
		return;
	
	CurrentHealth -= damage;
	LastTimeDamageTaken = CurrentTime;
	
	OnHealthUpdate.Broadcast();
}

void UHealthComponent::Heal(int amount)
{
	CurrentHealth = FMath::Max(CurrentHealth + amount, MaxHealth);
	OnHealthUpdate.Broadcast();
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

