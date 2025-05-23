// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "PlatformBase.h"
#include "BreakablePlatform.generated.h"

class UPaperSprite;
class UPaperFlipbook;
class UPaperFlipbookComponent;

UCLASS(Blueprintable)
class FIRSTPROJECT_API ABreakablePlatform : public APlatformBase
{
	GENERATED_BODY()
	
public:
	ABreakablePlatform(const FObjectInitializer& ObjectInitializer);
	
	virtual void SetIsMovingDown(bool bIsMovingDown) override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void UpdateBreakStage();
	void BreakPlatform();
	void ResetPlatform();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnPlatformBoundaryComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta = (AllowPrivateAccess = "true"))
	TArray<UPaperSprite*> BreakStagesSprites;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* BreakFlipbook = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta = (AllowPrivateAccess = "true"))
	float BreakStageDuration = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta = (AllowPrivateAccess = "true"))
	bool bIsSingleUse = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta = (AllowPrivateAccess = "true"))
	float PlatformResetTime = 5.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* PlatformBoundaryComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* FlipbookComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 CurrentBreakStage = 0;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float BreakTimer = 0.0f;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bPlayerTouchedPlatform = false;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsPlatformBreaking = false;
};
