// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h" 
#include "PlayerCharacter.generated.h"

class UPaperSpriteComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class FIRSTPROJECT_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveRight(const FInputActionValue& Value);
	UPaperSpriteComponent* GetSprite();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveRightAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;
	
	// UFUNCTION()
	// void OnHit(
	// 	UPrimitiveComponent* HitComponent,
	// 	AActor* OtherActor,
	// 	UPrimitiveComponent* OtherComp,
	// 	FVector NormalImpulse,
	// 	const FHitResult& Hit);

private:
	float JumpForce = 700.0f;
	float AirControl = 0.1f;
};
