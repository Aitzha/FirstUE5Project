// Copyright Epic Games, Inc. All Rights Reserved.
#include "SpecialShopCharacterEntry.h"

#include "PaperSprite.h"
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
	ImageElement->SetBrushFromTexture(CharacterData->Sprite->GetBakedTexture());

	// Set button text
	ButtonLabel->SetText(IsPurchased
		? FText::FromString("Select")
		: FText::Format(FText::FromString("Buy for {0} Gold"), FText::AsNumber(CharacterData->Price)));
}