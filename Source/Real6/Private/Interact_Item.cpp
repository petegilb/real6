#include "Interact_Item.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

AInteract_Item::AInteract_Item()
{
    PrimaryActorTick.bCanEverTick = false;

    Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
    SetRootComponent(Collision);
    Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    Collision->SetGenerateOverlapEvents(true);

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(Collision);
    Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly );

   
}

void AInteract_Item::BeginPlay()
{
    Super::BeginPlay();
}

void AInteract_Item::OnPickedUp()
{
    bCanPickUp = false;

    Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SetActorEnableCollision(false);
}

void AInteract_Item::OnDropped()
{
    SetActorEnableCollision(true);
    Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AInteract_Item::OnOverlapBegin( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult ) {
    if ( OtherActor && OtherActor->ActorHasTag( TEXT( "Player" ) ) ) {
        bCanPickUp = true;
    }
}

void AInteract_Item::OnOverlapEnd( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex ) {
    if ( OtherActor && OtherActor->ActorHasTag( TEXT( "Player" ) ) ) {
        bCanPickUp = false;
    }
}