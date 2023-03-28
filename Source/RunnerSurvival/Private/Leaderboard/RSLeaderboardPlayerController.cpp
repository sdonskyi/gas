// RunnerSurvival. All Rights Reserved. SDonskyi


#include "Leaderboard/RSLeaderboardPlayerController.h"

void ARSLeaderboardPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}