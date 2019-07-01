// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MultiplayerTestGameMode.generated.h"

UCLASS(minimalapi)
class AMultiplayerTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMultiplayerTestGameMode();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Power")
	float GetDecayRate();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Power")
	float PowerDrainDelay;

	FTimerHandle PowerDrainTimer;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float DecayRate;

private:
	void DrainPowerOverTime();
};



