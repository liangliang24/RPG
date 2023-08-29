// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RBTTask_RangeAttack.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URBTTask_RangeAttack : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
public:
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
protected:
	UPROPERTY(EditAnywhere,Category="Attack")
	TSubclassOf<AActor> projectile;
};
