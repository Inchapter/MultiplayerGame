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
	// replicated属性需要重写该函数
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;
	// 只有拥有网络权限的才能执行该函数
	UFUNCTION(BlueprintAuthorityOnly, Category = "test")
	void PickUpBy(APawn* Pawn) override;

	float GetPower();

protected:
	//复制该属性，让这个类所有实例的初始值保持相同
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "test", Meta = (BlueprintProtected = "true"))
	float BatteryPower;

};
