// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "Blueprint/UserWidget.h"
#include "RSLeaderboardTimeRowWidget.generated.h"

class UTextBlock;

UCLASS()
class RUNNERSURVIVAL_API URSLeaderboardTimeRowWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimeTextBlock = nullptr;
		
};
