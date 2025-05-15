// Copyright Epic Games, Inc. All Rights Reserved.


#include "SpecialMerchantMenu.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "PaperSprite.h"
#include "Components/CanvasPanel.h"
#include "Engine/Texture2D.h"

USpecialMerchantMenu::USpecialMerchantMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void USpecialMerchantMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Canvas) return;

	const float IconSize = 512.f;
	const float Spacing = 512.f;
	const float StartX = 100.f;
	const float Y = 200.f;

	for (int32 i = 0; i < CharacterOptions.Num(); ++i)
	{
		UPaperSprite* Sprite = CharacterOptions[i];
		if (!Sprite) continue;

		// Create UImage
		UImage* SpriteImage = NewObject<UImage>(this);
		
		// Convert UPaperSprite to Brush
		FSlateBrush Brush;
		Brush.SetResourceObject(Sprite->GetBakedTexture());
		Brush.ImageSize = FVector2D(IconSize, IconSize);
		SpriteImage->SetBrush(Brush);

		// Add to Canvas
		if (UCanvasPanelSlot* CanvasSlot = Canvas->AddChildToCanvas(SpriteImage))
		{
			CanvasSlot->SetAutoSize(true);
			CanvasSlot->SetPosition(FVector2D(StartX + i * Spacing, Y));
		}
	}
}
