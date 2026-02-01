#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Interact_Item.generated.h"

UCLASS()
class REAL6_API AInteract_Item : public AActor
{
    GENERATED_BODY()

public:
    AInteract_Item();

    // ÉvÉåÉCÉÑÅ[Ç™åƒÇ‘
    UFUNCTION( BlueprintCallable, Category = "Interact" )
    void OnPickedUp();
    UFUNCTION( BlueprintCallable, Category = "Interact" )
    void OnDropped();

    bool CanPickUp() const { return bCanPickUp; }

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* Collision;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* Mesh;

    UPROPERTY(EditAnywhere, Category="Interact")
    bool bCanPickUp = false;

    UFUNCTION( )
    void OnOverlapBegin( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

    UFUNCTION( )
    void OnOverlapEnd( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );
};
