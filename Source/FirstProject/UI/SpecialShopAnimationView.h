// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpecialShopAnimationView.generated.h"

class UPaperSprite;
class UImage;
class UHorizontalBox;
class UPaperFlipbook;

UCLASS()
class FIRSTPROJECT_API USpecialShopAnimationView : public UUserWidget
{
	GENERATED_BODY()

public:
	void Setup(const TArray<UPaperFlipbook*> Flipbooks);
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnAnimationButtonClicked(int32 Index);

	UPROPERTY(meta = (BindWidget))
	UImage* ImageElement;
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* AnimationsContainer;
	
	TArray<UPaperFlipbook*> Animations;
	TArray<TArray<UPaperSprite*>> AnimationsFrames;

private:
	void ExtractAnimationFrames(UPaperFlipbook* Animation);
	void NextFrame();

	int32 CurrentAnimation = 0;
	int32 CurrentFrame = 0;
	FTimerHandle FrameTimerHandle;
};
