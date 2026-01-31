#include "MyProjectHUD.h"
#include "Blueprint/UserWidget.h"
#include "MenuScreen.h"

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

void AMyProjectHUD::SetUIInputMode( bool bIsUIOnly, UUserWidget* WidgetToFocus ) {
    if ( !PC ) return;

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