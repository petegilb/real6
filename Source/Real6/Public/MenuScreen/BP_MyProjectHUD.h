// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BP_MyProjectHUD.generated.h"

UCLASS( )
class REAL6_API AMyProjectHUD : public AHUD {
	GENERATED_BODY( )

public:
	UPROPERTY( EditAnywhere, Category = "UI" )
	TSubclassOf<class UMyUserWidget> MainMenuWidgetClass;

	UPROPERTY( )
	class UMyUserWidget* MainMenuWidget;

protected:
	virtual void BeginPlay( ) override;

public:
	void ShowMainMenu( );
	void HideMainMenu( );
};
