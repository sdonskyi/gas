// RunnerSurvival. All Rights Reserved. SDonskyi

#include "UI/RSReloadingWidget.h"
#include "Components/TextBlock.h"
#include "RSUtils.h"

void URSReloadingWidget::SetTimer(int32 Time)
{
	if (IsValid(TimerTextBlock) == false || Time == 0)
	{
		return;
	}

	TimerTextBlock->SetText(RSUtils::FormatTime(Time));
}

void URSReloadingWidget::SetTimerVisible(bool bVisible)
{
	if (IsValid(TimerTextBlock) == false)
	{
		return;
	}

	TimerTextBlock->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}