// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "Blueprint/UserWidget.h"
#include "RSReloadingWidget.generated.h"

class UTextBlock;

UCLASS()
class RUNNERSURVIVAL_API URSReloadingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetTimer(int32 Time);
	void SetTimerVisible(bool bVisible);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimerTextBlock = nullptr;

};
