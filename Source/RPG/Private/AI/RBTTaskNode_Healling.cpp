// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RBTTaskNode_Healling.h"

#include "AIController.h"
#include "RAttributeComponent.h"

URBTTaskNode_Healling::URBTTaskNode_Healling()
{
	
}

void URBTTaskNode_Healling::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

EBTNodeResult::Type URBTTaskNode_Healling::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* pawn = AIController->GetPawn();
	URAttributeComponent* AIAttribute = URAttributeComponent::GetAttributeComponent(pawn);
	if(AIAttribute)
	{
		return AIAttribute->ApplyHealthChange(pawn,100.0f-AIAttribute->GetHealth())?EBTNodeResult::Succeeded:EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}
