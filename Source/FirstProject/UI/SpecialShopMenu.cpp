// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpecialShopMenu.h"

#include "SpecialShopCharacterEntry.h"
#include "SpecialShopAnimationView.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"
#include "Engine/Texture2D.h"
#include "FirstProject/SpecialShopCharacterData.h"

class USpecialShopCharacterEntry;

USpecialShopMenu::USpecialShopMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void USpecialShopMenu::OnCharacterButtonClicked(FSpecialShopCharacterData* CharacterData)
{
	if (!PurchasedCharacters.Contains(CharacterData->CharacterID))
	{
		// Mock purchase
		PurchasedCharacters.Add(CharacterData->CharacterID);
		ShowShopList();
	}
	else
	{
		ShowCharacterDetails(CharacterData);
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
		ShopListPanel->AddChild(Entry);
	}

	WidgetSwitcher->SetActiveWidgetIndex(0);
}

void USpecialShopMenu::ShowCharacterDetails(FSpecialShopCharacterData* CharacterData)
{
	UCanvasPanel* AnimationViewPanel = Cast<UCanvasPanel>(WidgetSwitcher->GetWidgetAtIndex(1));
	AnimationViewPanel->ClearChildren();
	
	USpecialShopAnimationView* AnimationView = CreateWidget<USpecialShopAnimationView>(this, AnimationViewWidgetClass);

	if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(AnimationViewPanel->AddChild(AnimationView)))
	{
		CanvasSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
		CanvasSlot->SetOffsets(FMargin(0.f));
	}
	WidgetSwitcher->SetActiveWidgetIndex(1);
}
