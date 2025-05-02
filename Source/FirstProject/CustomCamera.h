// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "CustomCamera.generated.h"

UCLASS()
class FIRSTPROJECT_API ACustomCamera : public ACameraActor
{
	GENERATED_BODY()
public:
	ACustomCamera();
	
	virtual void Tick(float DeltaTime) override;

	void SetTargetActor(AActor* NewTarget);

protected:
	virtual void BeginPlay() override;
    
	UPROPERTY(EditAnywhere, Category = "Camera")
	FVector2D CameraOffset = FVector2D(0.0f, 0.0f);

	UPROPERTY(EditAnywhere, Category = "Camera")
	float CameraDepthOffset = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float FollowSpeed = 5.0f;

private:
	AActor* TargetActor;
};
