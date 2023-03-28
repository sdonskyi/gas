// RunnerSurvival. All Rights Reserved. SDonskyi

#include "GameStates/RSGameStateBase.h"
#include "Components/RSHealthComponent.h"
#include "GameModes/RSGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/RSBaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameStateBase, All, All);

void ARSGameStateBase::EndGame_Implementation()
{
	if (!IsSomePlayerAlive())
	{
		EndGameClient();
	}
}

void ARSGameStateBase::EndGameClient_Implementation()
{
	UGameplayStatics::OpenLevel(this, "Leaderboard", true, FString(TEXT("listen")));
}

bool ARSGameStateBase::IsSomePlayerAlive()
{
	TArray<AActor*> Players;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARSBaseCharacter::StaticClass(), Players);
	for (const AActor* Actor : Players)
	{
		if (const ARSBaseCharacter* Player = Cast<ARSBaseCharacter>(Actor))
		{
			if (const URSHealthComponent* HealthComponent = Cast<URSHealthComponent>(Player->GetComponentByClass(URSHealthComponent::StaticClass())))
			{
				if (!HealthComponent->IsDead())
				{
					return true;
				}
			}
		}
	}
	return false;
}