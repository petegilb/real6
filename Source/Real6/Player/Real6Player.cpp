// Fill out your copyright notice in the Description page of Project Settings.


#include "Real6Player.h"
#include "EnhancedInputComponent.h"


AReal6Player::AReal6Player()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AReal6Player::BeginPlay()
{
	Super::BeginPlay();
	
}

void AReal6Player::Move_Implementation()
{
	
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

