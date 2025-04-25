// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomCamera.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ACustomCamera::ACustomCamera() 
{
	PrimaryActorTick.bCanEverTick = true;

	UCameraComponent* Camera = GetCameraComponent();
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
}

void ACustomCamera::BeginPlay()
{
	Super::BeginPlay();
    
	TargetActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void ACustomCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TargetActor) return;

	FVector TargetLocation = TargetActor->GetActorLocation();
	FVector CurrentLocation = GetActorLocation();
    
	FVector TargetWithOffset = FVector(
		TargetLocation.X + CameraOffset.X,
		TargetLocation.Y + CameraDepthOffset,
		TargetLocation.Z + CameraOffset.Y
	);

	FVector SmoothedLocation = UKismetMathLibrary::VInterpTo(
		CurrentLocation,
		TargetWithOffset,
		DeltaTime,
		FollowSpeed
	);

	SetActorLocation(SmoothedLocation);
}

void ACustomCamera::SetTargetActor(AActor* NewTarget)
{
	if (IsValid(NewTarget)) TargetActor = NewTarget;
}