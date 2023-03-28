// RunnerSurvival. All Rights Reserved. SDonskyi

#include "GameModes/RSGameModeBase.h"
#include "GameInstance/RSGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/RSSaveLoadManager.h"
#include "Managers/RSHealthPickupSpawnManager.h"
#include "Player/RSPlayerController.h"
#include "Player/RSBaseCharacter.h"
#include "UI/RSGameHUD.h"

ARSGameModeBase::ARSGameModeBase()
{
	if (IsValid(GetWorld()) == false)
	{
		return;
	}
	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	SaveLoadManager =  GetWorld()->SpawnActor<ARSSaveLoadManager>(Location, Rotation, SpawnInfo);
	if (IsValid(SaveLoadManager))
	{
		SaveLoadManager->LoadBestTime();
	}
	
	HealthPickupSpawnManager = GetWorld()->SpawnActor<ARSHealthPickupSpawnManager>(Location, Rotation, SpawnInfo);
}

void ARSGameModeBase::LoadLeaderboard()
{
	if (IsValid(GetWorld()) == false)
	{
		return;
	}

	URSGameInstance* RSGameInstance = GetWorld()->GetGameInstance<URSGameInstance>();
	if (IsValid(RSGameInstance) == false)
	{
		return;
	}
		
	const int32 TimeSeconds = static_cast<int32>(GetWorld()->GetTimeSeconds());
	auto& BestResults = RSGameInstance->BestResults;
	if (TimeSeconds > BestResults[BestResults.Num()-1])
	{
		BestResults[BestResults.Num() - 1] = TimeSeconds;
		Algo::Sort(BestResults, [](const auto& a, const auto& b) { return a > b; });
		if (IsValid(SaveLoadManager))
		{
			SaveLoadManager->SaveBestTime();
		}
	}	

	UGameplayStatics::OpenLevel(this, LeaderboardLevelName);
}