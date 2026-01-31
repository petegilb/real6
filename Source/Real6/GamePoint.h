#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GamePoint.generated.h"

class AReal6Player;

UENUM( BlueprintType )
enum class EPointType : uint8 {
    Goal        UMETA( DisplayName = "Goal" ),
    CheckPoint  UMETA( DisplayName = "CheckPoint" )
};

UCLASS( )
class REAL6_API AGamePoint : public AActor {
    GENERATED_BODY( )

public:
    AGamePoint( );

protected:
    virtual void BeginPlay( ) override;

public:
    virtual void Tick( float DeltaTime ) override;

    // ===== ê›íË =====
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "GamePoint" )
    EPointType PointType;

    // ===== Components =====
    UPROPERTY( VisibleAnywhere, Category = "GamePoint" )
    USceneComponent* SceneRoot;

    UPROPERTY( VisibleAnywhere, Category = "GamePoint" )
    UStaticMeshComponent* Mesh;

    UPROPERTY( VisibleAnywhere, Category = "GamePoint" )
    USphereComponent* Trigger;

    // ===== BP Events =====
    UFUNCTION( BlueprintImplementableEvent, Category = "GamePoint" )
    void OnGoalReached(AReal6Player* Player);

    UFUNCTION( BlueprintImplementableEvent, Category = "GamePoint" )
    void OnCheckPointReached(AReal6Player* Player);

    // ===== Overlap =====
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
