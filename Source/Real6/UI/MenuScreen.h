#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h" 
#include "MenuScreen.generated.h"

class UButton;
class UTextBlock;

UCLASS( )
class REAL6_API UMenuScreen : public UUserWidget {
	GENERATED_BODY( )

protected:
	UFUNCTION( )
	virtual bool Initialize( ) override;
	UFUNCTION( )
	void HandleStartButtonClicked( );
	UFUNCTION( )
	void HandleLangToggleButtonClicked( );
protected:
	UPROPERTY( meta = ( BindWidget ) )
	UButton* StartButton;
	UPROPERTY( meta = ( BindWidget ) )
	UButton* LangToggleButton;
	UPROPERTY( meta = ( BindWidget ) )
	UTextBlock* TitleText;
	UPROPERTY( meta = ( BindWidget ) )
	class UTextBlock* StartButtonText;
	UPROPERTY( meta = ( BindWidget ) )
	class UTextBlock* LangToggleButtonText;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Localization" )
	FText TitleTextValue;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Localization" )
	FText StartButtonTextValue;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Localization" )
	FText LangToggleButtonTextValue;
	UPROPERTY( EditAnywhere, Category = "Navigation" )
	TSoftObjectPtr<UWorld> NextLevel;

};