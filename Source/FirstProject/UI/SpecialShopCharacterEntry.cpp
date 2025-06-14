// Copyright Epic Games, Inc. All Rights Reserved.
#include "SpecialShopCharacterEntry.h"

#include "PaperSprite.h"
#include "SpecialShopMenu.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "FirstProject/Common/SpecialShopCharacterData.h"

void USpecialShopCharacterEntry::UpdateButtonLabel()
{
	ButtonLabel->SetText(FText::FromString("Select"));
}

void USpecialShopCharacterEntry::NativeConstruct()
{
	Super::NativeConstruct();
	ActionButton->OnPressed.AddDynamic(this, &USpecialShopCharacterEntry::OnActionButtonClicked);
}

void USpecialShopCharacterEntry::OnActionButtonClicked()
{
	ParentMenu->OnCharacterButtonClicked(this);
}

void USpecialShopCharacterEntry::Setup(FSpecialShopCharacterData& Data, bool IsPurchased, USpecialShopMenu* Menu)
{
	CharacterData = &Data;
	ParentMenu = Menu;
	
	ImageElement->SetBrushFromTexture(CharacterData->Sprite->GetBakedTexture());

	ButtonLabel->SetText(IsPurchased
		? FText::FromString("Select")
		: FText::Format(FText::FromString("Buy for {0} Gold"), FText::AsNumber(CharacterData->Price)));

}