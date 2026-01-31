// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class AReal6Player;
// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface to inherit when the object should be interactable.
 * The object should also have a part of it that blocks the ECC_GameTraceChannel1
 */
class REAL6_API IInteractable
{
	GENERATED_BODY()

public:
	// Contains logic to call upon interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void Interact(AReal6Player* InteractingCharacter);

	// Should return text to display above the interactable (if necessary)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	FString GetInteractText(AReal6Player* InteractingCharacter);
};
