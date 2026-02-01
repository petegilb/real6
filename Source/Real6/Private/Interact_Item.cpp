#include "Interact_Item.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Real6/Player/Real6Player.h"

AInteract_Item::AInteract_Item()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    SetRootComponent(Mesh);
    Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly );
    
    Mesh->SetCollisionResponseToAllChannels(ECR_Block);
    
    // block the interaction trace channel
    Mesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
}

void AInteract_Item::Interact_Implementation(AReal6Player* InteractingCharacter)
{
    FString InteractString = FString::Printf(TEXT("Interacted with %s"), *GetName());
    GEngine->AddOnScreenDebugMessage(99, 5.f, FColor::Green, InteractString);

    if (InteractingCharacter->GetCurrentPower() == EPowerType::Carry)
    {
        OnPickedUp(InteractingCharacter);
    }
}

void AInteract_Item::BeginPlay()
{
    Super::BeginPlay();
}

void AInteract_Item::OnPickedUp(AReal6Player* InteractingCharacter)
{
    bCanPickUp = false;
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SetActorEnableCollision(false);

    // Attach to the player
    InteractingCharacter->PickupItem(this);
}

void AInteract_Item::OnDropped()
{
    SetActorEnableCollision(true);
    Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}
