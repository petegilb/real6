#include "BP_MyProjectHUD.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.h" // 先ほど作ったクラス

void AMyProjectHUD::BeginPlay( ) {
    Super::BeginPlay( );

    ShowMainMenu( );
}

void AMyProjectHUD::ShowMainMenu( ) {
    if ( MainMenuWidgetClass ) {
        // UIを生成
        MainMenuWidget = CreateWidget<UMyUserWidget>( GetWorld( ), MainMenuWidgetClass );

        if ( MainMenuWidget ) {
            // 画面に追加
            MainMenuWidget->AddToViewport( );

            // マウスカーソルを表示し、操作をUIに集中させる設定
            APlayerController* PC = GetOwningPlayerController( );
            PC->SetShowMouseCursor( true );
            FInputModeUIOnly InputMode;
            InputMode.SetWidgetToFocus( MainMenuWidget->TakeWidget( ) );
            PC->SetInputMode( InputMode );
        }
    }
}