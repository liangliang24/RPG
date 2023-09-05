// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RBTTask_RangeAttack.generated.h"

/**
 * 行为树任务，发起攻击
 */
UCLASS()
class RPG_API URBTTask_RangeAttack : public UBTTaskNode
{
public:
	explicit URBTTask_RangeAttack()
		: MaxBulletSpread(3.0f)
	{
	}

private:
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	UPROPERTY(EditAnywhere,Category="Attack")
	TSubclassOf<AActor> projectile;
	
	UPROPERTY(EditAnywhere,Category="Attack")
	double MaxBulletSpread;
};
