// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStaticMeshActor.h"
#include "Net/UnrealNetwork.h"
#include "Components/StaticMeshComponent.h"

AMyStaticMeshActor::AMyStaticMeshActor() 
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;

	//GetStaticMeshComponent()->bGenerateOverlapEvents = true;

	if (Role == ROLE_Authority)
	{
		bIsActive = true;
	}
}

void AMyStaticMeshActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyStaticMeshActor, bIsActive);
}

bool AMyStaticMeshActor::IsActive()
{
	return bIsActive;
}

void AMyStaticMeshActor::SetActive(bool ActiveState)
{
	if (Role == ROLE_Authority)
	{
		bIsActive = ActiveState;
	}
}

void AMyStaticMeshActor::WasCollected_Implementation()
{
	// UE_LOG(LogClass, Log, TEXT("WasCollected_Implementation %s"), *GetName());
}

void AMyStaticMeshActor::OnRep_IsActive()
{	
}

void AMyStaticMeshActor::PickUpBy(APawn* Pawn)
{
	if (Role == ROLE_Authority)
	{
		PickupInstigator = Pawn;
		ClientOnPickedUpBy(Pawn);
	}
}

void AMyStaticMeshActor::ClientOnPickedUpBy_Implementation(APawn* Pawn)
{
	// PickupInstigator = Pawn;
	WasCollected();
}