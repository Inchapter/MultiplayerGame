// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MultiplayerTestGameMode.h"
#include "MultiplayerTestCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

AMultiplayerTestGameMode::AMultiplayerTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	DecayRate = 0.02f;

	PowerDrainDelay = 0.25f;

}

void AMultiplayerTestGameMode::BeginPlay()
{
	GetWorldTimerManager().SetTimer(PowerDrainTimer, this, &AMultiplayerTestGameMode::DrainPowerOverTime, PowerDrainDelay, true);

}

float AMultiplayerTestGameMode::GetDecayRate()
{
	return DecayRate;
}

void AMultiplayerTestGameMode::DrainPowerOverTime()
{
	UWorld* World = GetWorld();
	check(World)
	
	for (FConstControllerIterator It = World->GetControllerIterator(); It; ++It)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(*It))
		{
			if (AMultiplayerTestCharacter* BatteryCharacter = Cast<AMultiplayerTestCharacter>(PlayerController->GetPawn()))
			{
				if (BatteryCharacter->GetCurrentPower() > 0)
				{
					BatteryCharacter->UpdatePower(-PowerDrainDelay * DecayRate*(BatteryCharacter->GetInitialPower()));
				}
			}
		}
	}
}
