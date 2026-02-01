// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Real6.h"
#include "GameFramework/Character.h"
#include "Engine/TargetPoint.h"
#include "Enemy.generated.h"

class AReal6Player;

UCLASS()
class REAL6_API AEnemy : public ACharacter, public IInteractable {
	GENERATED_BODY( )

public:
	// Sets default values for this character's properties
	AEnemy( );

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay( ) override;

public:
	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	// Interact override from IInteractable interface
	virtual void Interact_Implementation(AReal6Player* InteractingCharacter) override;

	// 巡回用 TargetPoint 配列をセットする関数
	UFUNCTION( BlueprintCallable, Category = "Patrol" )
	void SetPatrolPoints( const TArray<ATargetPoint*>& InPatrolPoints );

	// 巡回用 TargetPoint 配列
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Patrol" )
	TArray<ATargetPoint*> PatrolPoints;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enemy")
	EPowerType EnemyPowerType = EPowerType::None;

private:
	void CheckSight( );
	void OnPlayerFound( AActor* Player );
	void DrawSightDebug( );

	UPROPERTY( EditAnywhere, Category = "Sight" )
	float SightDistance = 300.0f;

	UPROPERTY( EditAnywhere, Category = "Sight" )
	float SightAngle = 60.0f;

	int32 CurrentPatrolIndex;
};
