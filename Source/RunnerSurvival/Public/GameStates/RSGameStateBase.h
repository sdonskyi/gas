// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "GameFramework/GameStateBase.h"
#include "RSGameStateBase.generated.h"

UCLASS()
class RUNNERSURVIVAL_API ARSGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level")
	FString PathLobby = "/Game/Levels/Lobby?Listen";

	UFUNCTION(Server, Reliable)
	void EndGame();
private:

	UFUNCTION(Client, Reliable)
	void EndGameClient();

	bool IsSomePlayerAlive();
};
