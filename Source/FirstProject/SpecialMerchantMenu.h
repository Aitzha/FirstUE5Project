// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpecialMerchantMenu.generated.h"

UCLASS()
class FIRSTPROJECT_API USpecialMerchantMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	USpecialMerchantMenu() = delete;
	USpecialMerchantMenu(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Canvas;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprites")
	TArray<UTexture2D*> CharacterOptions;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprites")
	UTexture2D* BorderTexture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters")
	float IconSize = 512.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters")
	float Spacing = 542.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters")
	float StartX = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters")
	float StartY = 200.f;
};
