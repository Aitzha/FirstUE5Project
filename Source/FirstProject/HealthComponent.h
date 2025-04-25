// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UCLASS( ClassGroup=(Stats), meta=(BlueprintSpawnableComponent) )
class FIRSTPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercentage();

	UFUNCTION(BlueprintCallable, Category = "Health")
	int GetCurrentHealth();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void TakeDamage(int damage);

	UFUNCTION(BlueprintCallable, Category = "Regen")
	void Heal(int amount);

protected:
	virtual void BeginPlay() override;

private:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	int CurrentHealth;

	UPROPERTY(EditAnywhere)
	int MaxHealth = 20;

	UPROPERTY(EditAnywhere)
	float DamageTakeCooldown = 2.0f;

	float LastTimeDamageTaken = -100.0f;
};
