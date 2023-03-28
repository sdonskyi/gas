// RunnerSurvival. All Rights Reserved. SDonskyi


#include "UI/OverheadWidget.h"
#include "Components/TextBlock.h"

void UOverheadWidget::SetDisplayText(FString TextToDisplay)
{
	if (IsValid(DisplayText))
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverheadWidget::ShowPlayerNetRole(APawn* InPawn)
{
	if (!IsValid(InPawn))
	{
		return;
	}
	ENetRole RemoteRole = InPawn->GetRemoteRole();
	FString Role;
	switch (RemoteRole)
	{
	case ENetRole::ROLE_Authority:
		Role = FString("Authority");
		break;
	case ENetRole::ROLE_AutonomousProxy:
		Role = FString("Autonomous Proxy");
		break;
	case ENetRole::ROLE_SimulatedProxy:
		Role = FString("Simulated Proxy");
		break;
	case ENetRole::ROLE_None:
		Role = FString("None");
		break;
	default:
		checkNoEntry();
	}
	ENetRole LocalRole = InPawn->GetLocalRole();
	FString RoleString;
	switch (LocalRole)
	{
	case ENetRole::ROLE_Authority:
		RoleString = FString("Authority");
		break;
	case ENetRole::ROLE_AutonomousProxy:
		RoleString = FString("Autonomous Proxy");
		break;
	case ENetRole::ROLE_SimulatedProxy:
		RoleString = FString("Simulated Proxy");
		break;
	case ENetRole::ROLE_None:
		RoleString = FString("None");
		break;
	default:
		checkNoEntry();
	}
	FString RemoteRoleString = FString::Printf(TEXT("Remote Role: %s; Local Role: %s"), *Role, *RoleString);
	SetDisplayText(RemoteRoleString);
}

void UOverheadWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	RemoveFromParent();
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
}