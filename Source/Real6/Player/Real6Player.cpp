// Fill out your copyright notice in the Description page of Project Settings.


#include "Real6Player.h"

#include "CameraRail.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


AReal6Player::AReal6Player()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArmComponent);
	
	bUseControllerRotationYaw = false;
}

void AReal6Player::BeginPlay()
{
	Super::BeginPlay();
	
}

void AReal6Player::Move_Implementation(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>();
	// AddMovementInput(GetActorRightVector(), -MovementValue.X);
	// AddMovementInput(GetActorForwardVector(), MovementValue.Y);
	
	// Constrict movement to world axis
	AddMovementInput(MovementRightAxis, MovementValue.X);
	AddMovementInput(MovementForwardAxis, MovementValue.Y);
}

void AReal6Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	// Keep checking for camera rail until we get one.
	if (!IsValid(CameraRail))
	{
		TArray<AActor*> OutRails;
		UGameplayStatics::GetAllActorsOfClass(this, ACameraRail::StaticClass(), OutRails);
		// Assume there is only 0 or 1 rail

		if (OutRails.Num() > 0)
		{
			CameraRail = Cast<ACameraRail>(OutRails[0]);
		}
		
		if (CameraRail)
		{
			UE_LOG(LogTemp, Log, TEXT("CameraRail found"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("CameraRail doesn't exist in level!"));
		}
	}

	if (!IsValid(CameraRail)) return;

	USplineComponent* Spline = CameraRail->CameraSpline;
	float InputKey = Spline->FindInputKeyClosestToWorldLocation(GetActorLocation() + CameraRail->GetDistanceOffset());
	float SplineDistance = Spline->GetDistanceAlongSplineAtSplineInputKey(InputKey);
	FTransform TargetTransform = Spline->GetTransformAtDistanceAlongSpline(
		SplineDistance, ESplineCoordinateSpace::World);
	
	FVector CurrentLocation = SpringArmComponent->GetComponentLocation();
	FVector NewCamLocation = UKismetMathLibrary::VInterpTo(
		CurrentLocation, TargetTransform.GetLocation(), DeltaTime, SplineRailInterpSpeed);
	SpringArmComponent->SetWorldLocation(NewCamLocation);

	FVector CamLoc = SpringArmComponent->GetComponentLocation();
	FVector PlayerLoc = GetActorLocation();

	FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(CamLoc, PlayerLoc);
	FRotator FinalRot = FMath::RInterpTo(
		Camera->GetComponentRotation(),
		LookAt,
		DeltaTime,
		10.f
	);

	Camera->SetWorldRotation(FinalRot);
}

void AReal6Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	}
}

