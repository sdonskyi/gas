// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "GameFramework/HUD.h"
#include "RSGameHUD.generated.h"

class UUserWidget;

UCLASS()
class RUNNERSURVIVAL_API ARSGameHUD : public AHUD
{
	GENERATED_BODY()	

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY()
	UUserWidget* PlayerHUDWidget = nullptr;

	virtual void BeginPlay() override;

};
