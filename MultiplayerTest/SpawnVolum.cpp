// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolum.h"
#include "Components/BoxComponent.h"
#include "kismet/KismetMathLibrary.h"
#include "MyStaticMeshActor.h"
#include "TimerManager.h"

// Sets default values
ASpawnVolum::ASpawnVolum()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (Role == ROLE_Authority)
	{
		WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawnvolume"));
		RootComponent = WhereToSpawn;

		SpawnDelayRangeLow = 1.f;
		SpawnDelayRangeHigh = 4.5f;
	}
	
}

// Called when the game starts or when spawned
void ASpawnVolum::BeginPlay()
{
	Super::BeginPlay();

	SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolum::SpawnPickup, SpawnDelay, false);
	
}

// Called every frame
void ASpawnVolum::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolum::GetRandomPointInVolume()
{
	if (WhereToSpawn != NULL)
	{
		FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
		FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;
		return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
	}
	return FVector();
}

void ASpawnVolum::SpawnPickup()
{
	if (Role == ROLE_Authority && WhatToSpawn != NULL)
	{
		if (UWorld* const World = GetWorld())
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			FVector SpawnLocation = GetRandomPointInVolume();

			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.f;
			SpawnRotation.Pitch = FMath::FRand() * 360.f;
			SpawnRotation.Roll = FMath::FRand() * 360.f;

			AMyStaticMeshActor* const SpawnedPickup = World->SpawnActor<AMyStaticMeshActor>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
			
			SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolum::SpawnPickup, SpawnDelay, false);
		}
	}
}

