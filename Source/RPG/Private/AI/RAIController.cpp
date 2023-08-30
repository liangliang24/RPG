// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ARAIController::BeginPlay()
{
	Super::BeginPlay();

	if(ensureMsgf(behaviorTree, TEXT("Behavior Tree is nullptr!")))
	{
		RunBehaviorTree(behaviorTree);
	}
	
	

	/*APawn* playerPawn = UGameplayStatics::GetPlayerPawn(this,0);

	if (playerPawn)
	{
		GetBlackboardComponent()->SetValueAsObject("TargetActor",playerPawn);
	}*/
}
