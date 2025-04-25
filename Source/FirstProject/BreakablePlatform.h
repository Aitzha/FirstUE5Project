// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlatformBase.h"
#include "PaperSprite.h"
#include "PaperFlipbook.h"
#include "BreakablePlatform.generated.h"


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
	void BreakPlatform(); // CHANGE HERE: Renamed to BreakPlatform cuz it does more than play flipbook now
	void ResetPlatform();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta = (AllowPrivateAccess = "true"))
	TArray<UPaperSprite*> BreakStagesSprites;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* BreakFlipbook;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta = (AllowPrivateAccess = "true"))
	float BreakStageDuration = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta = (AllowPrivateAccess = "true"))
	bool bIsSingleUse = true; // CHANGE HERE: Added new parameter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta = (AllowPrivateAccess = "true"))
	float PlatformResetTime = 5.0f; // CHANGE HERE: Added new parameter

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
	// CHANGE HERE: Removed bIsFlipbookPlaying variable
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bPlayerTouchedPlatform = false; // CHANGE HERE: Added new variable
};
