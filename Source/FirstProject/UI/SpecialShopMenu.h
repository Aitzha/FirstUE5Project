// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpecialShopMenu.generated.h"

class USpecialShopAnimationView;
struct FSpecialShopCharacterData;
class USpecialShopCharacterEntry;
class UWidgetSwitcher;
class UCanvasPanel;
class UButton;

UCLASS()
class FIRSTPROJECT_API USpecialShopMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	USpecialShopMenu() = delete;
	USpecialShopMenu(const FObjectInitializer& ObjectInitializer);

	void OnCharacterButtonClicked(FSpecialShopCharacterData* CharacterData);

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* Canvas;
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprites")
	UTexture2D* BorderTexture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Characters")
	TArray<FSpecialShopCharacterData> Characters;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters")
	float IconSize = 512.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters")
	float Spacing = 542.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters")
	float StartX = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters")
	float StartY = 200.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USpecialShopCharacterEntry> CharacterEntryWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USpecialShopAnimationView> AnimationViewWidgetClass;

private:
	void ShowShopList();
	void ShowCharacterDetails(FSpecialShopCharacterData* CharacterData);
	TSet<FName> PurchasedCharacters;

	UPROPERTY()
	TMap<UButton*, FName> ButtonCharacterMap;
};
