// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interact_Item.generated.h"

UCLASS()
class REAL6_API AInteract_Item : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteract_Item();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	UStaticMeshComponent* Mesh;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	USceneComponent* Root;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	class UBoxComponent* Collision;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	bool bIsInteract = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION( BlueprintCallable )
	void PickUp( AActor* Interact );

	UFUNCTION( BlueprintCallable )
	void Drop();

private:
	int InternalID;
};
