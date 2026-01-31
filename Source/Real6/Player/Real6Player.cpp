// Fill out your copyright notice in the Description page of Project Settings.


#include "Real6Player.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


AReal6Player::AReal6Player()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArmComponent);
}

void AReal6Player::BeginPlay()
{
	Super::BeginPlay();
	
}

void AReal6Player::Move_Implementation(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>();
	AddMovementInput(GetActorRightVector(), -MovementValue.X);
	AddMovementInput(GetActorForwardVector(), MovementValue.Y);
}

void AReal6Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

