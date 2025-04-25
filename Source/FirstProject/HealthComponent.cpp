// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
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
}

void UHealthComponent::Heal(int amount)
{
	CurrentHealth = FMath::Max(CurrentHealth + amount, MaxHealth);
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

