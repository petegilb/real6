#include "MenuGameMode.h"
#include "MyProjectHUD.h"

AMenuGameMode::AMenuGameMode( ) {
	HUDClass = AMyProjectHUD::StaticClass( );
	DefaultPawnClass = nullptr;
}