// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "LoseGame.generated.h"

class UButton;
class UTextBlock;

UCLASS( )
class REAL6_API ULoseGame : public UUserWidget {
	GENERATED_BODY( )

public:

protected:
	UFUNCTION( )
	virtual bool Initialize( ) override;
	UFUNCTION( )
	void HandleReSpawnButtonClicked( );
	UFUNCTION( )
	void HandleMenuBackButtonClicked( );
protected:
	UPROPERTY( meta = ( BindWidget ) )
	UButton* ReSpawnButton;
	UPROPERTY( meta = ( BindWidget ) )
	UButton* MenuBackButton;

	UPROPERTY( meta = ( BindWidget ) )
	UTextBlock* LoseText;
	UPROPERTY( meta = ( BindWidget ) )
	class UTextBlock* ReSpawnButtonText;
	UPROPERTY( meta = ( BindWidget ) )
	class UTextBlock* MenuBackButtonText;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Localization" )
	FText LoseTextValue;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Localization" )
	FText ReSpawnButtonTextValue;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Localization" )
	FText MenuBackButtonTextValue;
	UPROPERTY( EditAnywhere, Category = "Navigation" )
	TSoftObjectPtr<UWorld> MenuLevel;

};
