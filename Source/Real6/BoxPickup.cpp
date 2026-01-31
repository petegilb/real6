// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxPickup.h"


ABoxPickup::ABoxPickup()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionResponseToAllChannels(ECR_Block);
	// block the interaction trace channel
	Mesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
}

void ABoxPickup::Interact_Implementation(AReal6Player* InteractingCharacter)
{
	FString InteractString = FString::Printf(TEXT("Interacted with %s"), *GetName());
	GEngine->AddOnScreenDebugMessage(99, 5.f, FColor::Green, InteractString);
}

void ABoxPickup::BeginPlay()
{
	Super::BeginPlay();
}

void ABoxPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

