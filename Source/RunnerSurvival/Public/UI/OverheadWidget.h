// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "Blueprint/UserWidget.h"
#include "OverheadWidget.generated.h"

UCLASS()
class RUNNERSURVIVAL_API UOverheadWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DisplayText;

	void SetDisplayText(FString TextToDisplay);

	UFUNCTION(BlueprintCallable)
	void ShowPlayerNetRole(APawn* InPawn);

protected:
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;
	
};
