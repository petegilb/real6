#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Player/Real6Player.h"

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

	// 近づいたら次のポイントへ
	if ( Distance < 50.0f ) {
		CurrentPatrolIndex = ( CurrentPatrolIndex + 1 ) % PatrolPoints.Num( );
		return;
	}

	Direction.Normalize( );

	FRotator NewRotation = Direction.Rotation( );
	SetActorRotation( NewRotation );

	AddMovementInput( Direction, 1.0f );
	CheckSight( );
	DrawSightDebug( );
}

void AEnemy::Interact_Implementation(AReal6Player* InteractingCharacter)
{
	InteractingCharacter->StealMask(this);
}

void AEnemy::SetPatrolPoints( const TArray<ATargetPoint*>& InPatrolPoints ) {
	PatrolPoints = InPatrolPoints;
	CurrentPatrolIndex = 0;
}

void AEnemy::CheckSight( ) { 
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn( GetWorld( ), 0 );
	if ( !PlayerPawn ) {
		return;
	}
	FVector MyLocation = GetActorLocation( );
	FVector PlayerLocation = PlayerPawn->GetActorLocation( );

	FVector ToPlayer = PlayerLocation - MyLocation;
	float Distance = ToPlayer.Size( );

	if ( Distance > SightDistance ) {
		return;
	}

	ToPlayer.Normalize( );

	FVector Forward = GetActorForwardVector( );

	float Dot = FVector::DotProduct( Forward, ToPlayer );
	float AngleDeg = FMath::RadiansToDegrees( FMath::Acos( Dot ) );


	if ( AngleDeg <= SightAngle ) {
		OnPlayerFound( PlayerPawn );
	}
}

void AEnemy::OnPlayerFound( AActor* Player ) {
	UE_LOG( LogTemp, Warning, TEXT( "Player Found" ) );
	AReal6Player* RealPlayer = Cast<AReal6Player>( Player );
	if ( EnemyPowerType == RealPlayer->GetCurrentPower( ) ) {
		return;
	}
		RealPlayer->Die( );
}

void AEnemy::DrawSightDebug( ) {
	if ( !GetWorld( ) ) return;

	FVector Start = GetActorLocation( );
	FVector Forward = GetActorForwardVector( );

	const int SegmentCount = 30;
	float HalfAngle = SightAngle;

	for ( int i = 0; i < SegmentCount; i++ ) {
		float Angle1 = FMath::Lerp( -HalfAngle, HalfAngle, ( float )i / SegmentCount );
		float Angle2 = FMath::Lerp( -HalfAngle, HalfAngle, ( float )( i + 1 ) / SegmentCount );

		FRotator Rot1( 0.f, Angle1, 0.f );
		FRotator Rot2( 0.f, Angle2, 0.f );

		FVector Dir1 = Rot1.RotateVector( Forward );
		FVector Dir2 = Rot2.RotateVector( Forward );

		FVector End1 = Start + Dir1 * SightDistance;
		FVector End2 = Start + Dir2 * SightDistance;

		// 三角形を線で塗る
		DrawDebugLine( GetWorld( ), Start, End1, FColor::Red, false, -1.f, 0, 1.f );
		DrawDebugLine( GetWorld( ), End1, End2, FColor::Red, false, -1.f, 0, 1.f );
		DrawDebugLine( GetWorld( ), End2, Start, FColor::Red, false, -1.f, 0, 1.f );
	}
}
