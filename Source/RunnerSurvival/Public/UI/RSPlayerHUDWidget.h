// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "Blueprint/UserWidget.h"
#include "RSPlayerHUDWidget.generated.h"

class URSHealthComponent;
class UProgressBar;
class UTextBlock;

UCLASS()
class RUNNERSURVIVAL_API URSPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetManaPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetGameTime();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	TSubclassOf<URSHealthComponent> RSHealthComponent;

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameTime = nullptr;
};
