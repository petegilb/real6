// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "BoxPickup.generated.h"

UCLASS()
class REAL6_API ABoxPickup : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	ABoxPickup();

	virtual void Interact_Implementation(AReal6Player* InteractingCharacter) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components)
	TObjectPtr<UStaticMeshComponent> Mesh;

public:
	virtual void Tick(float DeltaTime) override;
};
