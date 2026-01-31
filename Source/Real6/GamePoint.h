#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GamePoint.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS( )
class REAL6_API AGamePoint : public AActor {
	GENERATED_BODY( )

public:
	AGamePoint( );

protected:
	virtual void BeginPlay( ) override;

public:
	// 毎フレーム更新（演出・デバッグ用）
	virtual void Tick( float DeltaTime ) override;

	// ===== コンポーネント =====
	UPROPERTY( VisibleAnywhere, Category = "GamePoint" )
	USceneComponent* Root;

	UPROPERTY( VisibleAnywhere, Category = "GamePoint" )
	UStaticMeshComponent* Mesh;

	UPROPERTY( VisibleAnywhere, Category = "GamePoint" )
	USphereComponent* Trigger;

	// ===== オーバーラップ =====
	UFUNCTION( )
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};
