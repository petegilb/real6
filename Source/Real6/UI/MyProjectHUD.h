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
public:
	UPROPERTY( EditAnywhere, Category = "UI" )
	TSubclassOf<class UMenuScreen> MenuScreenWidgetClass;

	UPROPERTY( )
	class UMenuScreen* MenuScreenWidget;

protected:
	virtual void BeginPlay( ) override;
	void SetUIInputMode( bool bIsUIOnly, class UUserWidget* WidgetToFocus = nullptr );

	UPROPERTY( )
	class APlayerController* PC;
};
