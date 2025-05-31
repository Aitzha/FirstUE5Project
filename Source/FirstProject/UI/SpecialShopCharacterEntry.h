// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpecialShopCharacterEntry.generated.h"

class UTextBlock;
class UButton;
class UImage;
class USpecialShopMenu;
struct FSpecialShopCharacterData;

UCLASS()
class FIRSTPROJECT_API USpecialShopCharacterEntry : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Setup(FSpecialShopCharacterData& Data, bool IsPurchased, USpecialShopMenu* Menu);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnActionButtonClicked();

	UPROPERTY(meta = (BindWidget))
	UImage* SpriteImage;

	UPROPERTY(meta = (BindWidget))
	UButton* ActionButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonLabel;

	UPROPERTY()
	USpecialShopMenu* ParentMenu;

	FSpecialShopCharacterData* CharacterData;
	
	bool bIsPurchased;
};
