// RunnerSurvival. All Rights Reserved. SDonskyi

#include "UI/RSGameHUD.h"
#include "Blueprint/UserWidget.h"

void ARSGameHUD::BeginPlay()
{
	Super::BeginPlay();

	PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (IsValid(PlayerHUDWidget))
	{
		PlayerHUDWidget->AddToViewport();
	}
}