// RunnerSurvival. All Rights Reserved. SDonskyi


#include "GAS/RSBlueprintFunctionLibrary.h"

int32 URSBlueprintFunctionLibrary::GetAmountLevelsForLevelUp()
{
	return FMath::RandRange(1, 2);
}