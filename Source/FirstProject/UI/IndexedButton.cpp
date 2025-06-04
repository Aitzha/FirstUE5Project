// Copyright Epic Games, Inc. All Rights Reserved.

#include "IndexedButton.h"

UIndexedButton::UIndexedButton()
{
	OnClicked.AddDynamic(this, &UIndexedButton::HandleClicked);
}
