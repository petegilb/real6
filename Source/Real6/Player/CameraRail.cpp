// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraRail.h"

#include "Components/SplineComponent.h"


ACameraRail::ACameraRail()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	CameraSpline = CreateDefaultSubobject<USplineComponent>(TEXT("CameraSpline"));
	CameraSpline->SetupAttachment(SceneRoot);
}

void ACameraRail::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACameraRail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

