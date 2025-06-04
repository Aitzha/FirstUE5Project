// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "IndexedButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonClickedWithIndex, int32, Index);

UCLASS()
class FIRSTPROJECT_API UIndexedButton : public UButton
{
	GENERATED_BODY()
	
public:
	UIndexedButton();
	
	UPROPERTY(BlueprintAssignable, Category = "Button")
	FOnButtonClickedWithIndex OnButtonClickedWithIndex;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
	int32 Index;

private:
	UFUNCTION()
	void HandleClicked()
	{
		OnButtonClickedWithIndex.Broadcast(Index);
	}
};
