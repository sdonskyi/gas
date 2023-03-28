// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "GameFramework/PlayerController.h"
#include "RSLeaderboardPlayerController.generated.h"

UCLASS()
class RUNNERSURVIVAL_API ARSLeaderboardPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
