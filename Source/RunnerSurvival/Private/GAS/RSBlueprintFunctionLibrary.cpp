// RunnerSurvival. All Rights Reserved. SDonskyi


#include "GAS/RSBlueprintFunctionLibrary.h"

int32 URSBlueprintFunctionLibrary::GetStartLevel()
{
	return FMath::RandRange(1, 2);
}