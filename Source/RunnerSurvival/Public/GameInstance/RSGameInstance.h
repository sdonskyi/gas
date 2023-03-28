// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "Engine/GameInstance.h"
#include "RSGameInstance.generated.h"

UCLASS()
class RUNNERSURVIVAL_API URSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	TStaticArray<int32, 5> BestResults;

};
