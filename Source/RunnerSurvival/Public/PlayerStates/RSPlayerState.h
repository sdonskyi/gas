// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "GameFramework/PlayerState.h"
#include "RSPlayerState.generated.h"

UCLASS()
class RUNNERSURVIVAL_API ARSPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	float GetLifeTime() const;
	void SetLifeTime(float Value);
	float GetTimeStartGame() const;
	void SetTimeStartGame(float Value);
private:
	float TimeStartGame = 0;
	float LifeTime = 0;
};
