// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpecialShopMenu.h"

#include "SpecialShopCharacterEntry.h"
#include "SpecialShopAnimationView.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Engine/Texture2D.h"
#include "FirstProject/Common/MyGameInstance.h"
#include "FirstProject/Common/SpecialShopCharacterData.h"

USpecialShopMenu::USpecialShopMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	GI = Cast<UMyGameInstance>(GetGameInstance());
}

void USpecialShopMenu::OnCharacterButtonClicked(USpecialShopCharacterEntry* CharacterEntry)
{
	FSpecialShopCharacterData* CharacterData = CharacterEntry->CharacterData;
	if (!PurchasedCharacters.Contains(CharacterData->CharacterID))
	{
		if (GI->Money >= CharacterData->Price)
		{
			GI->Money -= CharacterData->Price;
			PurchasedCharacters.Add(CharacterData->CharacterID);
			CharacterEntry->UpdateButtonLabel();
			MoneyLabel->SetText(FText::AsNumber(GI->Money));
		}
	}
	else
	{
		ShowCharacterDetails(CharacterData);
	}
}

void USpecialShopMenu::NativeConstruct()
{
	Super::NativeConstruct();
	CreateShopPage();
	WidgetSwitcher->SetActiveWidgetIndex(0);
}

void USpecialShopMenu::CreateShopPage()
{
	CharactersContainer->ClearChildren();

	for (FSpecialShopCharacterData& CharData : Characters)
	{
		USpecialShopCharacterEntry* Entry = CreateWidget<USpecialShopCharacterEntry>(this, CharacterEntryWidgetClass);
		bool bIsPurchased = PurchasedCharacters.Contains(CharData.CharacterID);
		Entry->Setup(CharData, bIsPurchased, this);
		CharactersContainer->AddChild(Entry);
	}

	MoneyLabel->SetText(FText::AsNumber(GI->Money));
}

void USpecialShopMenu::ShowCharacterDetails(FSpecialShopCharacterData* CharacterData)
{
	UCanvasPanel* AnimationViewPanel = Cast<UCanvasPanel>(WidgetSwitcher->GetWidgetAtIndex(1));
	AnimationViewPanel->ClearChildren();
	
	USpecialShopAnimationView* AnimationView = CreateWidget<USpecialShopAnimationView>(this, AnimationViewWidgetClass);
	AnimationView->Setup(CharacterData->Animations);

	if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(AnimationViewPanel->AddChild(AnimationView)))
	{
		CanvasSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
		CanvasSlot->SetOffsets(FMargin(0.f));
	}
	
	WidgetSwitcher->SetActiveWidgetIndex(1);
}
