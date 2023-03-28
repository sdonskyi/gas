// RunnerSurvival. All Rights Reserved. SDonskyi

#include "Leaderboard/UI/RSLeaderboardHUD.h"
#include "Blueprint/UserWidget.h"

void ARSLeaderboardHUD::BeginPlay()
{
	Super::BeginPlay();

	LeaderboardWidget = CreateWidget<UUserWidget>(GetWorld(), LeaderboardWidgetClass);

	if (IsValid(LeaderboardWidget))
	{
		LeaderboardWidget->AddToViewport();
	}
}
