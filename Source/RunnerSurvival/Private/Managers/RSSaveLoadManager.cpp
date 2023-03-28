// RunnerSurvival. All Rights Reserved. SDonskyi


#include "Managers/RSSaveLoadManager.h"
#include "GameInstance/RSGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveLoad/RSSaveGame.h"

ARSSaveLoadManager::ARSSaveLoadManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARSSaveLoadManager::SaveBestTime()
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

	URSSaveGame* RSSaveGame = Cast<URSSaveGame>(UGameplayStatics::CreateSaveGameObject(URSSaveGame::StaticClass()));
	if (IsValid(RSSaveGame) == false)
	{
		return;
	}

	auto& SaveBestTimes = RSSaveGame->BestTimes;
	const auto& BestTimes = RSGameInstance->BestResults;
	for (int32 i = 0; i < BestTimes.Num(); i++)
	{
		SaveBestTimes.Add(BestTimes[i]);
	}

	UGameplayStatics::SaveGameToSlot(RSSaveGame, NameSaveSlot, 0);
}

void ARSSaveLoadManager::LoadBestTime()
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

	URSSaveGame* RSSaveGame = Cast<URSSaveGame>(UGameplayStatics::CreateSaveGameObject(URSSaveGame::StaticClass()));
	if (IsValid(RSSaveGame) == false)
	{
		return;
	}
	RSSaveGame = Cast<URSSaveGame>(UGameplayStatics::LoadGameFromSlot(NameSaveSlot, 0));
	if (IsValid(RSSaveGame) == false)
	{
		return;
	}
	const auto& LoadBestTimes = RSSaveGame->BestTimes;
	auto& BestTimes = RSGameInstance->BestResults;
	for (int32 i = 0; i < LoadBestTimes.Num(); i++)
	{
		BestTimes[i] = LoadBestTimes[i];
	}
}