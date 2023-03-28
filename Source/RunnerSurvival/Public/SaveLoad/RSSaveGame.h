// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "GameFramework/SaveGame.h"
#include "RSSaveGame.generated.h"

UCLASS()
class RUNNERSURVIVAL_API URSSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, SaveGame)
	TArray<int32> BestTimes;

};
