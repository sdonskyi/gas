// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "GameFramework/PlayerController.h"
#include "RSPlayerController.generated.h"

UCLASS()
class RUNNERSURVIVAL_API ARSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level")
	FName LeaderboardLevelName = "LeaderboardLevel";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level")
	FString PathGame = "/Game/Levels/GameLevel?listen";

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void CheckSimple();
	void Exit();
	void ExitToMenu();
	void StartGame();	
};
