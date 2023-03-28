// RunnerSurvival. All Rights Reserved. SDonskyi

#include "UI/RSPlayerHUDWidget.h"
#include "GameModes/RSGameModeBase.h"
#include "GAS/RSAttributeSet.h"
#include "Components/RSHealthComponent.h"
#include "Components/TextBlock.h"
#include "Player/RSBaseCharacter.h"
#include "PlayerStates/RSPlayerState.h"
#include "RSUtils.h"

float URSPlayerHUDWidget::GetHealthPercent() const
{
	if (IsValid(GetOwningPlayerPawn()) == false)
	{
		return 0.0f;
	}

	const auto* HealthComponent = Cast<URSHealthComponent>(GetOwningPlayerPawn()->GetComponentByClass(RSHealthComponent));
	
	if (IsValid(HealthComponent) == false)
	{
		return 0.0f;
	}

	return HealthComponent->GetHealthPercent();
}

float URSPlayerHUDWidget::GetManaPercent() const
{
	if (IsValid(GetOwningPlayerPawn()) == false)
	{
		return 0.0f;
	}

	const auto* Owner = Cast<ARSBaseCharacter>(GetOwningPlayerPawn());

	if (IsValid(Owner) == false)
	{
		return 0.0f;
	}

	const auto* RSAttributeSet = Owner->AttributeSet;

	if (IsValid(RSAttributeSet) == false)
	{
		return 0.0f;
	}

	return RSAttributeSet->GetManaPercent();
}

void URSPlayerHUDWidget::SetGameTime()
{
	if (IsValid(GameTime) == false || IsValid(GetWorld()) == false)
	{
		return;
	}

	const auto* Player = GetOwningPlayer();
	if (!IsValid(Player))
	{
		return;
	}
	const auto* PlayerState = Cast<ARSPlayerState>(Player->PlayerState);
	if (!IsValid(PlayerState))
	{
		return;
	}
	GameTime->SetText(RSUtils::FormatTime(static_cast<int32>(PlayerState->GetLifeTime())));
}

