#include "PickupMask.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"

void UPickupMask::SetPickupData( FText Info ) {
    if ( ItemInfoText ) ItemInfoText->SetText( Info );

    if ( FadeInAndOut ) {
        
        PlayAnimation( FadeInAndOut );

        FWidgetAnimationDynamicEvent EndEvent;
        EndEvent.BindDynamic( this, &UPickupMask::OnAnimationFinished );
        BindToAnimationFinished( FadeInAndOut, EndEvent );
    }
}

void UPickupMask::OnAnimationFinished( ) {
    RemoveFromParent( ); 
}