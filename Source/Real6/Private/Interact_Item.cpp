// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact_Item.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AInteract_Item::AInteract_Item()
	:InternalID(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>( TEXT( "Root" ) );
	SetRootComponent( Root );

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Mesh" ) );
	Mesh->SetupAttachment( Root );

	Collision = CreateDefaultSubobject<UBoxComponent>( TEXT( "Collision" ) );
	Collision->SetupAttachment( Root );

	Mesh->SetSimulatePhysics( true );
}

// Called when the game starts or when spawned
void AInteract_Item::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteract_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteract_Item::PickUp( AActor* Interact ) {
	if ( !Interact ) return;

	bIsInteract = true;

	AttachToActor( Interact, FAttachmentTransformRules::SnapToTargetNotIncludingScale );
}

void AInteract_Item::Drop( ) {
	bIsInteract = false;

	DetachFromActor( FDetachmentTransformRules::KeepWorldTransform );

	Mesh->SetSimulatePhysics( true );
}