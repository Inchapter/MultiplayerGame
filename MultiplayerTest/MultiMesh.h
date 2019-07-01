// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyStaticMeshActor.h"
#include "MultiMesh.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERTEST_API AMultiMesh : public AMyStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMultiMesh();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

	UFUNCTION(BlueprintAuthorityOnly, Category = "test")
	void PickUpBy(APawn* Pawn) override;

	float GetPower();

protected:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "test", Meta = (BlueprintProtected = "true"))
	float BatteryPower;

};
