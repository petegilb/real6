#include "MenuScreen.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

bool UMenuScreen::Initialize( ) {
	if ( !Super::Initialize( ) ) {
		return false;
	}
	if ( HasAnyFlags( RF_ClassDefaultObject ) ) {
		return true;
	}

	if ( StartButton ) {
		StartButton->OnClicked.AddDynamic( this, &UMenuScreen::HandleStartButtonClicked );
	}
	if ( LangToggleButton ) {
		LangToggleButton->OnClicked.AddDynamic( this, &UMenuScreen::HandleLangToggleButtonClicked );
	}

	if ( TitleText ) {
		TitleText->SetText( TitleTextValue );
	}
	if ( StartButtonText ) {
		StartButtonText->SetText( StartButtonTextValue );
	}
	if ( StartButtonText ) {
		StartButtonText->SetText( StartButtonTextValue );
	}
	if ( LangToggleButtonText ) {
		LangToggleButtonText->SetText( LangToggleButtonTextValue );
	}

	return true;
}

void UMenuScreen::HandleStartButtonClicked( ) {
	if ( !NextLevel.IsNull( ) ) {
		UGameplayStatics::OpenLevelBySoftObjectPtr( GetWorld( ), NextLevel );
	}
}

void UMenuScreen::HandleLangToggleButtonClicked( ) {

}