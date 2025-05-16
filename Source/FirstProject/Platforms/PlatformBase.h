// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "PlatformBase.generated.h"

class AMainCharacter;
class UPrimitiveComponent;
class UBoxComponent;
class UPaperSpriteComponent;

UCLASS(Abstract, NotBlueprintable)
class FIRSTPROJECT_API APlatformBase : public AActor
{
	GENERATED_BODY()
	
public:
    APlatformBase() = delete;
    APlatformBase(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    virtual void SetIsMovingDown(bool bIsMovingDown) { bIsCharacterMovingDown = bIsMovingDown; }

protected:
    virtual void Tick(float deltaTime) override;
    virtual void BeginPlay() override;

    void InitializePlatformComponent(UPrimitiveComponent* InPlatformComponent);

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
    AMainCharacter* PlayerCharacter = nullptr;
    UPROPERTY(BlueprintReadOnly)
    bool bIsCharacterMovingDown = false;
    UPROPERTY(BlueprintReadOnly)
    float ZDistanceFromCharacter;
    UPROPERTY(BlueprintReadOnly)
    float FloorZPos;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UPrimitiveComponent* PlatformComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UBoxComponent* BoxComponent;


private:
    UFUNCTION()
    void OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
    void OnBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
};
