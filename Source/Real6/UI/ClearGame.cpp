#include "ClearGame.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

bool UClearGame::Initialize( ) {
	if ( !Super::Initialize( ) ) {
		return false;
	}
	if ( HasAnyFlags( RF_ClassDefaultObject ) ) {
		return true;
	}

	if ( ReStartButton ) {
		ReStartButton->OnClicked.AddDynamic( this, &UClearGame::HandleReStartButtonClicked );
	}
	if ( MenuBackButton ) {
		MenuBackButton->OnClicked.AddDynamic( this, &UClearGame::HandleMenuBackButtonClicked );
	}

	if ( ClearText ) {
		ClearText->SetText( ClearTextValue );
	}
	if ( ReStartButtonText ) {
		ReStartButtonText->SetText( ReStartButtonTextValue );
	}
	if ( MenuBackButtonText ) {
		MenuBackButtonText->SetText( MenuBackButtonTextValue );
	}

	return true;
}

void UClearGame::HandleReStartButtonClicked( ) {
	if ( !ReStartLevel.IsNull( ) ) {
		UGameplayStatics::OpenLevelBySoftObjectPtr( GetWorld( ), ReStartLevel );
	}
}

void UClearGame::HandleMenuBackButtonClicked( ) {
	if ( !MenuLevel.IsNull( ) ) {
		UGameplayStatics::OpenLevelBySoftObjectPtr( GetWorld( ), MenuLevel );
	}
}