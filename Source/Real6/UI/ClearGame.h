#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ClearGame.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class REAL6_API UClearGame : public UUserWidget
{
	GENERATED_BODY()
public:

protected:
	UFUNCTION( )
	virtual bool Initialize( ) override;
	UFUNCTION()
	void HandleReStartButtonClicked( );
	UFUNCTION()
	void HandleMenuBackButtonClicked( );
protected :
	UPROPERTY( meta = ( BindWidget ) )
	UButton* ReStartButton;
	UPROPERTY( meta = ( BindWidget ) )
	UButton* MenuBackButton;

	UPROPERTY( meta = ( BindWidget ) )
	UTextBlock* ClearText;
	UPROPERTY( meta = ( BindWidget ) )
	class UTextBlock* ReStartButtonText;
	UPROPERTY( meta = ( BindWidget ) )
	class UTextBlock* MenuBackButtonText;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Localization" )
	FText ClearTextValue;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Localization" )
	FText ReStartButtonTextValue;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Localization" )
	FText MenuBackButtonTextValue;
	UPROPERTY( EditAnywhere, Category = "Navigation" )
	TSoftObjectPtr<UWorld> ReStartLevel;
	UPROPERTY( EditAnywhere, Category = "Navigation" )
	TSoftObjectPtr<UWorld> MenuLevel;
	
};
