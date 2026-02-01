#include "MyProjectHUD.h"
#include "Blueprint/UserWidget.h"
#include "MenuScreen.h"
#include "ClearGame.h"
#include "LoseGame.h"
#include "PickupMask.h"

void AMyProjectHUD::BeginPlay( ) {
	Super::BeginPlay( );

	PC = GetOwningPlayerController( );
}

void AMyProjectHUD::ShowMenuScreen( ) {
	if ( MenuScreenWidgetClass ) {
		MenuScreenWidget = CreateWidget<UMenuScreen>( GetWorld( ), MenuScreenWidgetClass );

		if ( MenuScreenWidget ) {
			MenuScreenWidget->AddToViewport( );
			SetUIInputMode( true, MenuScreenWidget );
		}
	}
}

void AMyProjectHUD::HideMenuScreen( ) {
	if ( MenuScreenWidget ) {
		MenuScreenWidget->RemoveFromParent( );
		SetUIInputMode( false );
	}
}

void AMyProjectHUD::ShowClearGame( ) {
	if ( ClearGameWidgetClass ) {
		ClearGameWidget = CreateWidget<UClearGame>( GetWorld( ), ClearGameWidgetClass );

		if ( ClearGameWidget ) {
			ClearGameWidget->AddToViewport( );
			SetUIInputMode( true, ClearGameWidget );
		}
	}
}

void AMyProjectHUD::HideClearGame( ) {
	if ( ClearGameWidget ) {
		ClearGameWidget->RemoveFromParent( );
		SetUIInputMode( false );
	}
}

void AMyProjectHUD::ShowLoseGame( ) {
	if ( LoseGameWidgetClass ) {
		LoseGameWidget = CreateWidget<ULoseGame>( GetWorld( ), LoseGameWidgetClass );

		if ( LoseGameWidget ) {
			LoseGameWidget->AddToViewport( );
			SetUIInputMode( true, LoseGameWidget );
		}
	}
}

void AMyProjectHUD::HideLoseGame( ) {
	if ( LoseGameWidget ) {
		LoseGameWidget->RemoveFromParent( );
		SetUIInputMode( false );
	}
}

void AMyProjectHUD::ShowPickupMask( FText ItemInfo ) {
	if ( PickupMaskWidgetClass ) {
		PickupMaskWidget = CreateWidget<UPickupMask>( GetWorld( ), PickupMaskWidgetClass );

		if ( PickupMaskWidget ) {
			PickupMaskWidget->AddToViewport( );
			PickupMaskWidget->SetPickupData( ItemInfo );
			SetUIInputMode( true, PickupMaskWidget );
		}
	}
}

void AMyProjectHUD::HidePickupMask( ) {
	if ( PickupMaskWidget ) {
		PickupMaskWidget->RemoveFromParent( );
		SetUIInputMode( false );
	}
}

void AMyProjectHUD::SetUIInputMode( bool bIsUIOnly, UUserWidget* WidgetToFocus ) {
	if ( !PC ) {
		PC = GetOwningPlayerController( );
	}
	if ( !PC ) {
		UE_LOG( LogTemp, Warning, TEXT( "HUD: PlayerController is still NULL." ) );
		return;
	}

	if ( bIsUIOnly ) {
		PC->SetShowMouseCursor( true );
		FInputModeUIOnly InputMode;
		if ( WidgetToFocus ) {
			InputMode.SetWidgetToFocus( WidgetToFocus->TakeWidget( ) );
		}
		PC->SetInputMode( InputMode );
	} else {
		PC->SetShowMouseCursor( false );
		FInputModeGameOnly InputMode;
		PC->SetInputMode( InputMode );
	}
}