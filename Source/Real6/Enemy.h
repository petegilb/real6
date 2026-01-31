// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/TargetPoint.h"
#include "Enemy.generated.h"

UCLASS()
class REAL6_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 巡回用 TargetPoint 配列をセットする関数
	UFUNCTION( BlueprintCallable, Category = "Patrol" )
	void SetPatrolPoints( const TArray<ATargetPoint*>& InPatrolPoints );

	// 巡回用 TargetPoint 配列
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Patrol" )
	TArray<ATargetPoint*> PatrolPoints;

private:
	int32 CurrentPatrolIndex;
};
