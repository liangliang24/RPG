// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RAICharacter.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ARAICharacter::ARAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComponent");

}

void ARAICharacter::OnSeePawn(APawn* Pawn)
{
	AAIController* myController = Cast<AAIController>(GetController());

	if (myController)
	{
		myController->GetBlackboardComponent()->SetValueAsObject("TargetActor",Pawn);

		// UE_LOG(LogTemp,Log,TEXT("See %s"),*GetNameSafe(Pawn));
	}
	
}

void ARAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	pawnSensingComp->OnSeePawn.AddDynamic(this,&ARAICharacter::OnSeePawn);
}




