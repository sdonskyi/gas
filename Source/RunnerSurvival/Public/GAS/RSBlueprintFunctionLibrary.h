// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "RSBlueprintFunctionLibrary.generated.h"

UCLASS()
class RUNNERSURVIVAL_API URSBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="Gas")
	static int32 GetAmountLevelsForLevelUp();
	
};
