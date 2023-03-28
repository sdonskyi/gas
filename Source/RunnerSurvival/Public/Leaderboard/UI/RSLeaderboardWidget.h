// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/EditableText.h"
#include "RSLeaderboardWidget.generated.h"

class UButton;
class UEditableText;
class UVerticalBox;

UCLASS()
class RUNNERSURVIVAL_API URSLeaderboardWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level")
	FName GameLevelName = "GameLevel";

	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinGameButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	UEditableText* EditableTextAddress = nullptr;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* BestTimesVerticalBox = nullptr;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnQuitGame();

	UFUNCTION()
	void OnJoinGame();

	void UpdateBestTime();
};
