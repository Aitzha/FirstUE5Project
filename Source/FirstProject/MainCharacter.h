// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "InputActionValue.h"
#include "MainCharacter.generated.h"

class UFloatingPawnMovement;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS(Blueprintable)
class FIRSTPROJECT_API AMainCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	AMainCharacter() = delete;
	AMainCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void JumpOrDrop(const FInputActionValue& Value);
	void DownKeyPressed(const FInputActionValue& Value) { bIsDownKeyPressed = true; }
	void DownKeyReleased(const FInputActionValue& Value) { bIsDownKeyPressed = false; }
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* DropDownAction;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsDownKeyPressed = false;
};
