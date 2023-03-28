// RunnerSurvival. All Rights Reserved. SDonskyi

#include "PlayerStates/RSPlayerState.h"

void ARSPlayerState::BeginPlay()
{
	if (IsValid(GetWorld()) == false)
	{
		return;
	}
	TimeStartGame = GetWorld()->GetTimeSeconds();
}

float ARSPlayerState::GetLifeTime() const
{
	return LifeTime;
}

void ARSPlayerState::SetLifeTime(float Value)
{
	LifeTime = Value;
}

float ARSPlayerState::GetTimeStartGame() const
{
	return TimeStartGame;
}

void ARSPlayerState::SetTimeStartGame(float Value)
{
	TimeStartGame = Value;
}
