// Fill out your copyright notice in the Description page of Project Settings.

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
    inline void setIsMovingDown(bool bIsMovingDown) { bIsCharacterMovingDown = bIsMovingDown; }

protected:
    virtual void Tick(float deltaTime) override;
    virtual void BeginPlay() override;

    void InitializePlatformComponent(UPrimitiveComponent* InPlatformComponent);

    UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    bool bIsCharacterMovingDown = false;
    UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    AMainCharacter* PlayerCharacter = nullptr;
    UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    FVector FloorLocation;
    UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float ZDistanceBetweenCharacterAndPlatform;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    UPrimitiveComponent* PlatformComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    UBoxComponent* BoxComponent;


private:
    UFUNCTION()
    void OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
    void OnBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
};
