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
	// ���ʹ����Replicated������Ҫ��д�������
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;
	//�ж�actor�ļ���״̬
	UFUNCTION(BlueprintPure, Category = "test")
	bool IsActive();
	//���ü���״̬
	UFUNCTION(BlueprintCallable, Category = "test")
	void SetActive(bool ActiveState);
	//ʹ��native���д���ռ��ĺ�������������ͼ����д
	UFUNCTION(BlueprintNativeEvent, Category = "test")
	void WasCollected();
	virtual void WasCollected_Implementation();

	// UFUNCTION(BlueprintAuthorityOnly, Category = "test")
	virtual void PickUpBy(APawn* Pawn);

protected:
	//�����Ա������޸�ʱ���ӷ������˸��Ƹ����Ե��ͻ��ˣ�������������ֻ�пͻ��˻���ã�
	UPROPERTY(ReplicatedUsing = OnRep_IsActive)
	bool bIsActive;

	UFUNCTION()
	void OnRep_IsActive();
	//���ڼ�¼�ĸ������ռ��˵�ǰActor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "test")
	APawn* PickupInstigator;
	
private:
	//ʹ��NetMulticast���ʾ�ͻ��˺ͷ���˶�����øú���
	UFUNCTION(NetMulticast, Unreliable)
	void ClientOnPickedUpBy(APawn* Pawn);
};
