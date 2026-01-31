#include "LoseGame.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

bool ULoseGame::Initialize( ) {
	if ( !Super::Initialize( ) ) {
		return false;
	}
	if ( HasAnyFlags( RF_ClassDefaultObject ) ) {
		return true;
	}

	if ( ReSpawnButton ) {
		ReSpawnButton->OnClicked.AddDynamic( this, &ULoseGame::HandleReSpawnButtonClicked );
	}
	if ( MenuBackButton ) {
		MenuBackButton->OnClicked.AddDynamic( this, &ULoseGame::HandleMenuBackButtonClicked );
	}

	if ( LoseText ) {
		LoseText->SetText( LoseTextValue );
	}
	if ( ReSpawnButtonText ) {
		ReSpawnButtonText->SetText( ReSpawnButtonTextValue );
	}
	if ( MenuBackButtonText ) {
		MenuBackButtonText->SetText( MenuBackButtonTextValue );
	}

	return true;
}

void ULoseGame::HandleReSpawnButtonClicked( ) {
	
}

void ULoseGame::HandleMenuBackButtonClicked( ) {
	if ( !MenuLevel.IsNull( ) ) {
		UGameplayStatics::OpenLevelBySoftObjectPtr( GetWorld( ), MenuLevel );
	}
}
