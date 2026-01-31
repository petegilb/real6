#include "Enemy.h"


AEnemy::AEnemy( ) {
	PrimaryActorTick.bCanEverTick = true;
	CurrentPatrolIndex = 0;
}

void AEnemy::BeginPlay( ) {
	Super::BeginPlay( );
}

void AEnemy::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );

	if ( PatrolPoints.Num( ) == 0 ) return;
	if ( !PatrolPoints.IsValidIndex( CurrentPatrolIndex ) ) return;
	if ( !PatrolPoints[ CurrentPatrolIndex ] ) return;

	FVector TargetLocation = PatrolPoints[ CurrentPatrolIndex ]->GetActorLocation( );
	FVector MyLocation = GetActorLocation( );

	FVector Direction = TargetLocation - MyLocation;
	Direction.Z = 0.0f;

	float Distance = Direction.Size( );

	// ‹ß‚Ã‚¢‚½‚çŽŸ‚Ìƒ|ƒCƒ“ƒg‚Ö
	if ( Distance < 50.0f ) {
		CurrentPatrolIndex = ( CurrentPatrolIndex + 1 ) % PatrolPoints.Num( );
		return;
	}

	Direction.Normalize( );

	FRotator NewRotation = Direction.Rotation( );
	SetActorRotation( NewRotation );

	AddMovementInput( Direction, 1.0f );
}

void AEnemy::SetPatrolPoints( const TArray<ATargetPoint*>& InPatrolPoints ) {
	PatrolPoints = InPatrolPoints;
	CurrentPatrolIndex = 0;
}