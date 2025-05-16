// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpecialShopMenu.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Engine/Texture2D.h"
#include "FirstProject/SpecialMerchantCharacter.h"

USpecialShopMenu::USpecialShopMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void USpecialShopMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Canvas) return;

	for (int32 i = 0; i < Characters.Num(); ++i)
	{
		UTexture2D* Texture = Characters[i].CharacterTexture;
		if (!Texture) continue;

		UVerticalBox* EntryBox = NewObject<UVerticalBox>(this);

		// Border with image
		UBorder* Border = NewObject<UBorder>(this);
		UImage* Image = NewObject<UImage>(this);

		// Set sprite brush
		FSlateBrush Brush;
		Brush.SetResourceObject(Texture);
		Brush.ImageSize = FVector2D(IconSize, IconSize);
		Image->SetBrush(Brush);

		// Put image into border
		Border->SetContent(Image);
		Border->SetPadding(FMargin(20.f));

		FSlateBrush BorderBrush;
		BorderBrush.DrawAs = ESlateBrushDrawType::Box;
		BorderBrush.SetResourceObject(BorderTexture);
		Border->SetBrush(BorderBrush);

		// Button below
		UButton* SelectButton = NewObject<UButton>(this);
		UTextBlock* ButtonText = NewObject<UTextBlock>(this);
		ButtonText->SetText(FText::FromString("Select"));
		SelectButton->AddChild(ButtonText);

		// Add to vertical box
		EntryBox->AddChild(Border);
		EntryBox->AddChild(SelectButton);

		// Add to Canvas
		if (UCanvasPanelSlot* CanvasSlot = Canvas->AddChildToCanvas(EntryBox))
		{
			CanvasSlot->SetAutoSize(true);
			CanvasSlot->SetPosition(FVector2D(StartX + i * Spacing, StartY));
		}
	}
}
