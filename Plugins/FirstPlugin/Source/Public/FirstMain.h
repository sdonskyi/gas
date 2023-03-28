#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "FirstMain.generated.h"

UCLASS()
class FIRSTPLUGIN_API UFirstMain : public UBlueprintFunctionLibrary
{
  GENERATED_BODY()

public:
  UFUNCTION(BlueprintCallable, meta=(Category="FirstMain"))
  static void DoSomething();
};