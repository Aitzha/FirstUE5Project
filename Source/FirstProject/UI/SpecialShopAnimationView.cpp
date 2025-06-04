// Copyright Epic Games, Inc. All Rights Reserved.


#include "SpecialShopAnimationView.h"

#include "IndexedButton.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"

void USpecialShopAnimationView::NativeConstruct()
{
	Super::NativeConstruct();
}

void USpecialShopAnimationView::OnAnimationButtonClicked(int32 Index)
{
	UE_LOG(LogTemp, Warning, TEXT("Button was pressed: %d"), Index);
}

void USpecialShopAnimationView::Setup(const TArray<UPaperFlipbook*> Flipbooks)
{
	Animations = Flipbooks;
	AnimationButtonContainer->ClearChildren();
	
	for (int32 Index = 0; Index < Animations.Num(); ++Index)
	{
		UIndexedButton* Button = NewObject<UIndexedButton>(this);
		UTextBlock* Label = NewObject<UTextBlock>(this);
		Label->SetText(FText::AsNumber(Index + 1));
		Button->AddChild(Label);

		Button->Index = Index;
		Button->OnButtonClickedWithIndex.AddDynamic(this, &USpecialShopAnimationView::OnAnimationButtonClicked);

		AnimationButtonContainer->AddChild(Button);
	}

	if (Flipbooks.Num() > 0)
	{
		// FlipbookComponent->SetFlipbook(Flipbooks[0]);
	}
}

