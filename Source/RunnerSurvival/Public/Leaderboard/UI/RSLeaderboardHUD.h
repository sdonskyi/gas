// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "GameFramework/HUD.h"
#include "RSLeaderboardHUD.generated.h"

UCLASS()
class RUNNERSURVIVAL_API ARSLeaderboardHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> LeaderboardWidgetClass;

	UPROPERTY()
	UUserWidget* LeaderboardWidget = nullptr;

	virtual void BeginPlay() override;
};
