// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Maneger.generated.h"

UCLASS()
class REAL6_API AManeger : public AActor
{
	GENERATED_BODY()
	
public:	
	AManeger();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
