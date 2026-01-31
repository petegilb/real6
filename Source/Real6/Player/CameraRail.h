// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraRail.generated.h"

class USplineComponent;

UCLASS()
class REAL6_API ACameraRail : public AActor
{
	GENERATED_BODY()

public:
	ACameraRail();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USplineComponent> CameraSpline;

	UFUNCTION(BlueprintPure, Category = "Camera")
	FVector GetDistanceOffset() const { return DistanceOffset; }

protected:
	virtual void BeginPlay() override;

	// Offset to be applied when attaching camera to the rail (putting the camera behind the player)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	FVector DistanceOffset = FVector(1000, 0, 0);

public:
	virtual void Tick(float DeltaTime) override;
};
