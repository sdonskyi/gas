// RunnerSurvival. All Rights Reserved. SDonskyi

#pragma once

#include "Managers/RSBaseManager.h"
#include "GameFramework/Actor.h"
#include "RSSaveLoadManager.generated.h"

UCLASS()
class RUNNERSURVIVAL_API ARSSaveLoadManager : public ARSBaseManager
{
	GENERATED_BODY()
	
public:	
	ARSSaveLoadManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveLoad")
	FString NameSaveSlot = "RSSlot";

	void SaveBestTime();
	void LoadBestTime();

};
