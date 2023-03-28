// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "GameFramework/GameModeBase.h"
#include "RSGameModeBase.generated.h"

class ARSSaveLoadManager;
class ARSHealthPickupSpawnManager;

DECLARE_MULTICAST_DELEGATE(FOnEndGameSignature);

UCLASS()
class RUNNERSURVIVAL_API ARSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ARSGameModeBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level")
	FName LeaderboardLevelName = "LeaderboardLevel";

private:
	void LoadLeaderboard();

	UPROPERTY()
	ARSSaveLoadManager* SaveLoadManager = nullptr;

	UPROPERTY()
	ARSHealthPickupSpawnManager* HealthPickupSpawnManager = nullptr;

	FOnEndGameSignature OnEndGame;
};
