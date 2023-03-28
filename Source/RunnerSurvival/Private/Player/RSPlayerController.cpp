// RunnerSurvival. All Rights Reserved. SDonskyi


#include "Player/RSPlayerController.h"
#include "RSUtils.h"
#include "Engine.h"

void ARSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void ARSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (IsValid(InputComponent) == false)
	{
		return;
	}

	InputComponent->BindAction("CheckSimple", IE_Pressed, this, &ARSPlayerController::CheckSimple);
	InputComponent->BindAction("Exit", IE_Pressed, this, &ARSPlayerController::Exit);
	InputComponent->BindAction("ExitToMenu", IE_Pressed, this, &ARSPlayerController::ExitToMenu);
	InputComponent->BindAction("StartGame", IE_Pressed, this, &ARSPlayerController::StartGame);
}

void ARSPlayerController::CheckSimple() 
{
	int64 CheckedNumber = 655360001;
	
	if (RSUtils::CheckSimple(CheckedNumber))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Number %dll is simple"), CheckedNumber));
		return;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Number %dll is not simple"), CheckedNumber));
		return;
	}
}

void ARSPlayerController::Exit()
{
	UKismetSystemLibrary::QuitGame(this, this, EQuitPreference::Quit, true);
}

void ARSPlayerController::ExitToMenu()
{
	UGameplayStatics::OpenLevel(this, LeaderboardLevelName);
}

void ARSPlayerController::StartGame()
{
	if (HasAuthority())
	{
		UWorld* World = GetWorld();
		if (IsValid(World))
		{
			World->ServerTravel(PathGame);
		}
	}
}