// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RBTTaskNode_Healling.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URBTTaskNode_Healling : public UBTTaskNode
{
	GENERATED_BODY()
public:
	URBTTaskNode_Healling();
protected:
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
