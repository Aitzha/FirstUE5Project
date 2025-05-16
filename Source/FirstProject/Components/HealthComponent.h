// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthUpdate);

UCLASS()
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
	int32 GetCurrentHealth();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void TakeDamage(int32 damage);

	UFUNCTION(BlueprintCallable, Category = "Regeneration")
	void Heal(int32 amount);

protected:
	virtual void BeginPlay() override;

private:
	int32 CurrentHealth = 20;

	UPROPERTY(EditAnywhere, Category = "Parameters")
	int32 MaxHealth = 20;
	UPROPERTY(EditAnywhere, Category = "Parameters")
	float DamageTakeCooldown = 2.0f;

	float LastTimeDamageTaken = 0.0f;
};
