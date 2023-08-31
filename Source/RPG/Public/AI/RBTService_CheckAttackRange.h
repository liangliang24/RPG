// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "RBTService_CheckAttackRange.generated.h"

/**
 * 行为树服务，判断
 */
UCLASS()
class RPG_API URBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()
public:
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

protected:
	/*
	 * BlackBoard中的变量
	 */
	UPROPERTY(EditAnywhere,Category = "AI")
	FBlackboardKeySelector AttackRangeKey;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
