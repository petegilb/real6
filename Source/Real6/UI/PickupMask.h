// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PickupMask.generated.h"

UCLASS()
class REAL6_API UPickupMask : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UFUNCTION()
    void SetPickupData( FText ItemInfo );
    void OnAnimationFinished( );

protected:
    UPROPERTY( meta = ( BindWidget ) )
    class UTextBlock* ItemInfoText;

    UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
    class UWidgetAnimation* FadeInAndOut;
};