// Copyright Epic Games, Inc. All Rights Reserved.
#include "SpecialShopAnimationView.h"

#include "IndexedButton.h"
#include "PaperSprite.h"
#include "PaperFlipbook.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USpecialShopAnimationView::NativeConstruct()
{
	Super::NativeConstruct();
}

void USpecialShopAnimationView::OnAnimationButtonClicked(int32 Index)
{
	CurrentFrame = 0;
	CurrentAnimation = Index;
}

void USpecialShopAnimationView::Setup(const TArray<UPaperFlipbook*> Flipbooks)
{
	AnimationsContainer->ClearChildren();
	
	for (int32 Index = 0; Index < Flipbooks.Num(); ++Index)
	{
		UIndexedButton* Button = NewObject<UIndexedButton>(this);
		UTextBlock* Label = NewObject<UTextBlock>(this);
		Label->SetText(FText::AsNumber(Index + 1));
		Button->AddChild(Label);

		Button->Index = Index;
		Button->OnButtonClickedWithIndex.AddDynamic(this, &USpecialShopAnimationView::OnAnimationButtonClicked);

		AnimationsContainer->AddChild(Button);
		ExtractAnimationFrames(Flipbooks[Index]);
	}
	
	// Start Animation
	GetWorld()->GetTimerManager().SetTimer(FrameTimerHandle, this, &USpecialShopAnimationView::NextFrame, 0.3f, true);
}

void USpecialShopAnimationView::ExtractAnimationFrames(UPaperFlipbook* Animation)
{
	TArray<UPaperSprite*> Frames;
	
	for (int32 i = 0; i < Animation->GetNumFrames(); ++i)
	{
		UPaperSprite* Sprite = Animation->GetSpriteAtFrame(i);
		Frames.Add(Sprite);
	}

	AnimationsFrames.Add(Frames);
}

void USpecialShopAnimationView::NextFrame()
{
	UPaperSprite* Sprite = AnimationsFrames[CurrentAnimation][CurrentFrame];
	
	if (Sprite)
	{
		ImageElement->SetBrushFromTexture(Sprite->GetBakedTexture());
		ImageElement->SetDesiredSizeOverride(Sprite->GetSourceSize() * 2);
	}
	else
	{
		ImageElement->SetBrushFromTexture(nullptr);
		ImageElement->SetDesiredSizeOverride(FVector2D(0, 0));
	}

	CurrentFrame = (CurrentFrame + 1) % AnimationsFrames[CurrentAnimation].Num();
}

