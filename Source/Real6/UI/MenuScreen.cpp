#include "MenuScreen.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInternationalizationLibrary.h"
#include "Real6/Real6.h"

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
	if ( LangToggleButtonText ) {
		LangToggleButtonText->SetText( LangToggleButtonTextValue );
	}

	UKismetInternationalizationLibrary::SetCurrentCulture(TEXT("ja"), true);

	return true;
}

void UMenuScreen::HandleStartButtonClicked( ) {
	if ( !NextLevel.IsNull( ) ) {
		UGameplayStatics::OpenLevelBySoftObjectPtr( GetWorld( ), NextLevel );
	}
}

void UMenuScreen::HandleLangToggleButtonClicked( ) {
	FString CurrentCulture = UKismetInternationalizationLibrary::GetCurrentCulture();
	LOG_ARGS(Warning, "Current Culture %s", *CurrentCulture)

	if (CurrentCulture.Equals(TEXT("en")))
	{
		UKismetInternationalizationLibrary::SetCurrentCulture(TEXT("ja"), true);
		UE_LOG(LogTemp, Warning, TEXT("Changed to ja"))
	}
	else
	{
		UKismetInternationalizationLibrary::SetCurrentCulture(TEXT("en"), true);
		UE_LOG(LogTemp, Warning, TEXT("Changed to en"))
	}
}