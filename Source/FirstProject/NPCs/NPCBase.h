// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPCBase.generated.h"

class AMainCharacter;
class UPaperSpriteComponent;
class UBoxComponent;

UCLASS(Abstract, NotBlueprintable)
class FIRSTPROJECT_API ANPCBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ANPCBase() = delete;
	ANPCBase(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnPlayerInteraction();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Other")
	AMainCharacter* PlayerCharacter = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Other")
	bool bIsPlayerInRange = false;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
};
