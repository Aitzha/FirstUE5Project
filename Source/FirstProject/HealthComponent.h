// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthUpdate);

UCLASS( ClassGroup=(Stats), meta=(BlueprintSpawnableComponent) )
class FIRSTPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent() = delete;
	UHealthComponent(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthUpdate OnHealthUpdate;

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercentage();

	UFUNCTION(BlueprintCallable, Category = "Health")
	int GetCurrentHealth();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void TakeDamage(int damage);

	UFUNCTION(BlueprintCallable, Category = "Regeneration")
	void Heal(int amount);

protected:
	virtual void BeginPlay() override;

private:
	int CurrentHealth;

	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
	int MaxHealth = 20;
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
	float DamageTakeCooldown = 2.0f;

	float LastTimeDamageTaken = -100.0f;
};
