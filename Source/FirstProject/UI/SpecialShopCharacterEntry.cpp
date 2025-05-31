// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpecialShopCharacterEntry.h"
#include "SpecialShopMenu.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "FirstProject/SpecialShopCharacterData.h"

void USpecialShopCharacterEntry::NativeConstruct()
{
	Super::NativeConstruct();
	ActionButton->OnPressed.AddDynamic(this, &USpecialShopCharacterEntry::OnActionButtonClicked);
}

void USpecialShopCharacterEntry::OnActionButtonClicked()
{
	ParentMenu->OnCharacterButtonClicked(CharacterData);
}

void USpecialShopCharacterEntry::Setup(FSpecialShopCharacterData& Data, bool IsPurchased, USpecialShopMenu* Menu)
{
	CharacterData = &Data;
	bIsPurchased = IsPurchased;
	ParentMenu = Menu;

	// Set image
	FSlateBrush Brush;
	Brush.SetResourceObject(CharacterData->Texture);
	Brush.ImageSize = FVector2D(128, 128);
	SpriteImage->SetBrush(Brush);

	// Set button text
	ButtonLabel->SetText(IsPurchased
		? FText::FromString("Select")
		: FText::Format(FText::FromString("Buy for {0} Gold"), FText::AsNumber(CharacterData->Price)));
}