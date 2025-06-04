// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpecialShopAnimationView.generated.h"

class UHorizontalBox;
class UPaperFlipbookComponent;
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

	// UPROPERTY(meta = (BindWidget))
	// UPaperFlipbookComponent* FlipbookComponent;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* AnimationButtonContainer;
	
	TArray<UPaperFlipbook*> Animations;
};
