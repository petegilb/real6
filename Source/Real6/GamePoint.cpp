#include "GamePoint.h"

#include "Player/Real6Player.h"

AGamePoint::AGamePoint( ) {
    PrimaryActorTick.bCanEverTick = true;

    PointType = EPointType::CheckPoint;

    // ===== Root =====
    SceneRoot = CreateDefaultSubobject<USceneComponent>( TEXT( "SceneRoot" ) );
    RootComponent = SceneRoot;

    // ===== Mesh =====
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Mesh" ) );
    Mesh->SetupAttachment( SceneRoot );
    Mesh->SetCollisionEnabled( ECollisionEnabled::NoCollision );

    // ===== Trigger =====
    Trigger = CreateDefaultSubobject<USphereComponent>( TEXT( "Trigger" ) );
    Trigger->SetupAttachment( SceneRoot );
    Trigger->SetSphereRadius( 120.0f );

    Trigger->SetCollisionEnabled( ECollisionEnabled::QueryOnly );
    Trigger->SetCollisionObjectType( ECC_WorldDynamic );
    Trigger->SetCollisionResponseToAllChannels( ECR_Ignore );
    Trigger->SetCollisionResponseToChannel( ECC_Pawn, ECR_Overlap );
    Trigger->SetGenerateOverlapEvents( true );
}

void AGamePoint::BeginPlay( ) {
    Super::BeginPlay( );

    if ( Trigger ) {
        Trigger->OnComponentBeginOverlap.AddDynamic(
            this,
            &AGamePoint::OnOverlapBegin
        );
    }
}

void AGamePoint::Tick( float DeltaTime ) {
    Super::Tick( DeltaTime );
}

void AGamePoint::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
) {
    if ( !OtherActor || OtherActor == this ) {
        return;
    }

    AReal6Player* Player = Cast<AReal6Player>(OtherActor);
    if (!Player) return;

    switch ( PointType ) {
    case EPointType::Goal:
        OnGoalReached(Player);
        break;

    case EPointType::CheckPoint:
        OnCheckPointReached(Player);
        break;

    default:
        break;
    }
}

void OnGoalReached( ) {
    UE_LOG( LogTemp, Warning, TEXT( "Goal!!" ) );
}

void OnCheckPointReached( ) {
    UE_LOG( LogTemp, Warning, TEXT( "CheckPoint" ) );
}