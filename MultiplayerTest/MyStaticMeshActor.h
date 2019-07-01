// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MyStaticMeshActor.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERTEST_API AMyStaticMeshActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMyStaticMeshActor();
	// 如果使用了Replicated，则需要重写这个函数
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;
	//判断actor的激活状态
	UFUNCTION(BlueprintPure, Category = "test")
	bool IsActive();
	//设置激活状态
	UFUNCTION(BlueprintCallable, Category = "test")
	void SetActive(bool ActiveState);
	//使用native宏编写被收集的函数，可以在蓝图中重写
	UFUNCTION(BlueprintNativeEvent, Category = "test")
	void WasCollected();
	virtual void WasCollected_Implementation();

	// UFUNCTION(BlueprintAuthorityOnly, Category = "test")
	virtual void PickUpBy(APawn* Pawn);

protected:
	//当属性被复制修改时（从服务器端复制该属性到客户端），触发函数（只有客户端会调用）
	UPROPERTY(ReplicatedUsing = OnRep_IsActive)
	bool bIsActive;

	UFUNCTION()
	void OnRep_IsActive();
	//用于记录哪个人物收集了当前Actor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "test")
	APawn* PickupInstigator;
	
private:
	//使用NetMulticast宏表示客户端和服务端都会调用该函数
	UFUNCTION(NetMulticast, Unreliable)
	void ClientOnPickedUpBy(APawn* Pawn);
};
