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

protected:
	ABreakablePlatform(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void UpdateBreakStage();
	void BreakPlatform();
	void ResetPlatform();

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

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent* SpriteComponent = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* FlipbookComponent = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 CurrentBreakStage = 0;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float BreakTimer = 0.0f;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsBreaking = false;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bPlayerTouchedPlatform = false;
};
