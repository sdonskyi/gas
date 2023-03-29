// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "UObject/Interface.h"
#include "GameplayEffectTypes.h"
#include "RSGASInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URSGASInterface : public UInterface
{
	GENERATED_BODY()
};

class RUNNERSURVIVAL_API IRSGASInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="GAS")
	void LevelUpAbility(FGameplayTagContainer TagContainer, int32 NewLevel);
};
