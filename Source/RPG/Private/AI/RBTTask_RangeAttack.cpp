// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RBTTask_RangeAttack.h"

#include "AIController.h"
#include "RAttributeComponent.h"
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
		
		if(targetActor == nullptr||!URAttributeComponent::GetActorAlive(targetActor)) return EBTNodeResult::Failed;
		FActorSpawnParameters spawnParameters;
		//spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		spawnParameters.Instigator = myPawn;
		FRotator spawnRotation = (targetActor->GetActorLocation()-muzzleLocation).Rotation();
		spawnRotation.Pitch+=FMath::RandRange(-MaxBulletSpread,MaxBulletSpread);
		spawnRotation.Yaw+=FMath::RandRange(-MaxBulletSpread,MaxBulletSpread);
		//UE_LOG(LogTemp,Log,TEXT("Shoot by %s"),*GetNameSafe(myPawn));
		AActor* spawnActor = GetWorld()->SpawnActor<AActor>(projectile,
		                                                    muzzleLocation,
		                                                    spawnRotation,
		                                                    spawnParameters);
		//UE_LOG(LogTemp,Log,TEXT("Spawn %s from %s control by %s"),*GetNameSafe(spawnActor),*GetNameSafe(myPawn),*GetNameSafe(myController));
		//DrawDebugSphere(GetWorld(),myPawn->GetActorLocation(),30,16,FColor::Red,false,2);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
