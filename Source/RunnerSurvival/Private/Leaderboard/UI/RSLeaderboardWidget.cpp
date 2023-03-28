// RunnerSurvival. All Rights Reserved. SDonskyi


#include "Leaderboard/UI/RSLeaderboardWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "GameInstance/RSGameInstance.h"
#include "GameModes/RSLeaderboardGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Leaderboard/UI/RSLeaderboardTimeRowWidget.h"
#include "Managers/RSSaveLoadManager.h"
#include "RSUtils.h"


void URSLeaderboardWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IsValid(StartGameButton))
	{
		StartGameButton->OnClicked.AddDynamic(this, &URSLeaderboardWidget::OnStartGame);
	}

	if (IsValid(QuitGameButton))
	{
#if !PLATFORM_SWITCH
		QuitGameButton->OnClicked.AddDynamic(this, &URSLeaderboardWidget::OnQuitGame);
#else
		QuitGameButton->SetVisibility(ESlateVisibility::Collapsed);
#endif
	}
	
	if (IsValid(JoinGameButton))
	{
		JoinGameButton->OnClicked.AddDynamic(this, &URSLeaderboardWidget::OnJoinGame);
	}

	UpdateBestTime();
}
	
void URSLeaderboardWidget::OnQuitGame()
{
#if !PLATFORM_SWITCH
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);	
#endif
}

void URSLeaderboardWidget::OnStartGame()
{
	UGameplayStatics::OpenLevel(this, GameLevelName, true, FString(TEXT("listen")));
}

void URSLeaderboardWidget::OnJoinGame()
{
	if (!IsValid(EditableTextAddress))
	{
		return;
	}
	UGameplayStatics::OpenLevel(this, FName(*EditableTextAddress->GetText().ToString()), true, FString(TEXT("listen")));
}

void URSLeaderboardWidget::UpdateBestTime()
{
	if (IsValid(GetWorld()) == false || IsValid(BestTimesVerticalBox) == false)
	{
		return;
	}

	auto* RSGameInstance = GetWorld()->GetGameInstance<URSGameInstance>();

	if (IsValid(RSGameInstance) == false)
	{
		return;
	}

	const auto& BestTimes = RSGameInstance->BestResults;
	const FText dash = FText::FromString(" - ");
	for (int32 i = 0; i < BestTimes.Num(); i++)
	{
		const URSLeaderboardTimeRowWidget* const BestTime = Cast<URSLeaderboardTimeRowWidget>(BestTimesVerticalBox->GetChildAt(i));
		if (IsValid(BestTime) == false)
		{
			break;
		}

		UTextBlock* TimeTextBlock = BestTime->TimeTextBlock;
		if (IsValid(TimeTextBlock))
		{			
			if (BestTimes[i] == 0)
			{
				TimeTextBlock->SetText(dash);
			}
			else
			{
				TimeTextBlock->SetText(RSUtils::FormatTime(BestTimes[i]));
			}
		}
	}
}