#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyProjectHUD.generated.h"

UCLASS( )
class REAL6_API AMyProjectHUD : public AHUD {
	GENERATED_BODY( )

public:
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void ShowMenuScreen( );

	UFUNCTION( BlueprintCallable, Category = "UI" )
	void HideMenuScreen( );

	UFUNCTION( BlueprintCallable, Category = "UI" )
	void ShowClearGame( );

	UFUNCTION( BlueprintCallable, Category = "UI" )
	void HideClearGame( );

	UFUNCTION( BlueprintCallable, Category = "UI" )
	void ShowLoseGame( );

	UFUNCTION( BlueprintCallable, Category = "UI" )
	void HideLoseGame( );

	UFUNCTION( BlueprintCallable, Category = "UI" )
	void ShowPickupMask( FText ItemInfo );

	UFUNCTION( BlueprintCallable, Category = "UI" )
	void HidePickupMask( );
public:
	UPROPERTY( EditAnywhere, Category = "UI" )
	TSubclassOf<class UMenuScreen> MenuScreenWidgetClass;

	UPROPERTY( )
	class UMenuScreen* MenuScreenWidget;

	UPROPERTY( EditAnywhere, Category = "UI" )
	TSubclassOf<class UClearGame> ClearGameWidgetClass;

	UPROPERTY( )
	class UClearGame* ClearGameWidget;

	UPROPERTY( EditAnywhere, Category = "UI" )
	TSubclassOf<class ULoseGame> LoseGameWidgetClass;

	UPROPERTY( )
	class ULoseGame* LoseGameWidget;

	UPROPERTY( EditAnywhere, Category = "UI" )
	TSubclassOf<class UPickupMask> PickupMaskWidgetClass;

	UPROPERTY( )
	class UPickupMask* PickupMaskWidget;

protected:
	virtual void BeginPlay( ) override;
	void SetUIInputMode( bool bIsUIOnly, class UUserWidget* WidgetToFocus = nullptr );

	UPROPERTY( )
	class APlayerController* PC;
};
