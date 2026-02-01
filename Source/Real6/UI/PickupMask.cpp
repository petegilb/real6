#include "PickupMask.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"
#include "MyProjectHUD.h"

void UPickupMask::SetPickupData( FText Info ) {
	if ( ItemInfoText ) ItemInfoText->SetText( Info );

	if ( FadeInAndOut ) {

		PlayAnimation( FadeInAndOut );

		FWidgetAnimationDynamicEvent EndEvent;
		EndEvent.BindDynamic( this, &UPickupMask::OnFadeAnimationFinished );
		BindToAnimationFinished( FadeInAndOut, EndEvent );
	}
}

void UPickupMask::OnFadeAnimationFinished( ) {
	APlayerController* PC = GetOwningPlayer( );
	if ( PC ) {
		// 2. PCからHUDを取得し、自分のHUDクラスにキャスト
		AMyProjectHUD* HUD = Cast<AMyProjectHUD>( PC->GetHUD( ) );
		if ( HUD ) {
			// 3. HUDの関数を呼び出す（例：通知終了の報告など）
			SetVisibility( ESlateVisibility::Collapsed );
			HUD->HidePickupMask( );
		}
	}
}