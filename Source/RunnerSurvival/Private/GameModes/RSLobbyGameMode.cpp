// RunnerSurvival. All Rights Reserved. SDonskyi


#include "GameModes/RSLobbyGameMode.h"
#include "GameFramework/GameStateBase.h"

void ARSLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (!IsValid(GameState))
	{
		return;
	}

	int32 NumberOfPlayers = GameState->PlayerArray.Num();
	if (NumberOfPlayers == 2)
	{
		UWorld* World = GetWorld();
		if (IsValid(World))
		{
			bUseSeamlessTravel = true;
			World->ServerTravel(PathGame);
		}
	}
}
