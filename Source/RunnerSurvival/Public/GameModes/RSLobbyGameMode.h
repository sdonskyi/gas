// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "GameFramework/GameMode.h"
#include "RSLobbyGameMode.generated.h"

UCLASS()
class RUNNERSURVIVAL_API ARSLobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level")
	FString PathGame = "/Game/Levels/GameLevel?listen";

};
