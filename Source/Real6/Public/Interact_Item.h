#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Real6/Interactable.h"
#include "Interact_Item.generated.h"

UCLASS()
class REAL6_API AInteract_Item : public AActor, public IInteractable
{
    GENERATED_BODY()

public:
    AInteract_Item();

    // ÉvÉåÉCÉÑÅ[Ç™åƒÇ‘
    UFUNCTION( BlueprintCallable, Category = "Interact" )
    void OnPickedUp(AReal6Player* InteractingCharacter);
    UFUNCTION( BlueprintCallable, Category = "Interact" )
    void OnDropped();

    bool CanPickUp() const { return bCanPickUp; }

    virtual void Interact_Implementation(AReal6Player* InteractingCharacter) override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* Mesh;

    UPROPERTY(EditAnywhere, Category="Interact")
    bool bCanPickUp = false;
};
