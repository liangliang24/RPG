// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"



void URBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* blackboardComp = OwnerComp.GetBlackboardComponent();

	if (ensure(blackboardComp))
	{
		AActor* targetActor = Cast<AActor>(blackboardComp->GetValueAsObject("TargetActor"));
		if (targetActor)
		{
			AAIController* myController = OwnerComp.GetAIOwner();
			if (ensure(myController))
			{
				APawn* AIPawn = myController->GetPawn();

				if (ensure(AIPawn))
				{
					float dis = FVector::Distance(targetActor->GetActorLocation(),AIPawn->GetActorLocation());

					bool bWithinRange = (dis < 2000.0f)&&(myController->LineOfSightTo(targetActor));

					blackboardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName,bWithinRange);
				}
			}
		}
		
	}
}
