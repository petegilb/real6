// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePoint.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AGamePoint::AGamePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Root
	Root = CreateDefaultSubobject<USceneComponent>( TEXT( "Root" ) );
	RootComponent = Root;

	// Mesh（見える用）
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Mesh" ) );
	Mesh->SetupAttachment( Root );
	Mesh->SetCollisionEnabled( ECollisionEnabled::NoCollision );

	// Trigger（踏む用）
	Trigger = CreateDefaultSubobject<USphereComponent>( TEXT( "Trigger" ) );
	Trigger->SetupAttachment( Root );
	Trigger->SetSphereRadius( 120.0f );
	Trigger->SetCollisionProfileName( TEXT( "Trigger" ) );
}

// Called when the game starts or when spawned
void AGamePoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGamePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGamePoint::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
) {
	UE_LOG( LogTemp, Log, TEXT( "Overlap!" ) );
}