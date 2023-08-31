// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RBTTask_RangeAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type URBTTask_RangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// return Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* myController = OwnerComp.GetAIOwner();

	if(myController)
	{
		ACharacter* myPawn = Cast<ACharacter>(myController->GetPawn());
		if (myPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		FVector muzzleLocation = myPawn->GetMesh()->GetSocketLocation("Muzzle_01");

		AActor* targetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		
		if(targetActor == nullptr) return EBTNodeResult::Failed;

		FActorSpawnParameters spawnParameters;
		spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		spawnParameters.Instigator = myPawn;
		AActor* spawnActor = GetWorld()->SpawnActor<AActor>(projectile,muzzleLocation,(targetActor->GetActorLocation()-muzzleLocation).Rotation(),spawnParameters);
		DrawDebugSphere(GetWorld(),myPawn->GetActorLocation(),30,16,FColor::Red,false,2);
		return spawnActor?EBTNodeResult::Succeeded:EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}

void URBTTask_RangeAttack::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}
