// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"


AMultiMesh::AMultiMesh()
{
	bReplicateMovement = true;

	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	GetStaticMeshComponent()->SetSimulatePhysics(true);

	BatteryPower = 200.f;
	
}


void AMultiMesh::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMultiMesh, BatteryPower);

}

void AMultiMesh::PickUpBy(APawn * Pawn)
{
	Super::PickUpBy(Pawn);

	if (Role == ROLE_Authority)
	{
		SetLifeSpan(1.f);
	}
}

float AMultiMesh::GetPower()
{
	return BatteryPower;
}
