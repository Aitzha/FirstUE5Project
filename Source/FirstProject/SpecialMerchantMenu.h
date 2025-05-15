// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpecialMerchantMenu.generated.h"

class UPaperSprite;

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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Options")
	TArray<UPaperSprite*> CharacterOptions;
};
