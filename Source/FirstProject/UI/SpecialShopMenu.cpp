// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpecialShopMenu.h"

#include "SpecialShopCharacterEntry.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/WidgetSwitcher.h"
#include "Engine/Texture2D.h"
#include "FirstProject/SpecialShopCharacterData.h"

class USpecialShopCharacterEntry;

USpecialShopMenu::USpecialShopMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void USpecialShopMenu::OnCharacterButtonClicked(FSpecialShopCharacterData* CharacterData)
{
	UE_LOG(LogTemp, Warning, TEXT("Button was pressed for: %s"), *CharacterData->CharacterID.ToString());
	if (!PurchasedCharacters.Contains(CharacterData->CharacterID))
	{
		// Mock purchase
		PurchasedCharacters.Add(CharacterData->CharacterID);
		// RefreshShopList();
	}
	else
	{
		// ShowCharacterDetails(CharacterData);
	}
}

void USpecialShopMenu::NativeConstruct()
{
	Super::NativeConstruct();
	ShowShopList();
}

void USpecialShopMenu::ShowShopList()
{
	UScrollBox* ShopListPanel = Cast<UScrollBox>(WidgetSwitcher->GetWidgetAtIndex(0));
	ShopListPanel->ClearChildren();

	for (FSpecialShopCharacterData& CharData : Characters)
	{
		USpecialShopCharacterEntry* Entry = CreateWidget<USpecialShopCharacterEntry>(this, CharacterEntryWidgetClass);
		bool bIsPurchased = PurchasedCharacters.Contains(CharData.CharacterID);
		Entry->Setup(CharData, bIsPurchased, this);
		
		if (UScrollBoxSlot* ScrollBoxElement = Cast<UScrollBoxSlot>(ShopListPanel->AddChild(Entry)))
		{
			ScrollBoxElement->SetPadding(FMargin(10.f, 0.f));
		}
	}

	WidgetSwitcher->SetActiveWidgetIndex(0);
}
