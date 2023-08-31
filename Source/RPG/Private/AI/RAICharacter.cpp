// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RAICharacter.h"

#include "AIController.h"
#include "RAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ARAICharacter::ARAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComponent");

	attributeComp = CreateDefaultSubobject<URAttributeComponent>("AttributeComponent");
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

void ARAICharacter::Die()
{
	Destroy();
}

void ARAICharacter::OnHealthChange(AActor* InstigatorActor, URAttributeComponent* OwningComp, float NewHealth,
                                   float Delta)
{
	if(NewHealth <= 0)
	{
		FTimerHandle dieHandle;
		GetWorldTimerManager().SetTimer(dieHandle,this,&ARAICharacter::Die,3.0f);
	}
}

void ARAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	pawnSensingComp->OnSeePawn.AddDynamic(this,&ARAICharacter::OnSeePawn);
	attributeComp->OnHealthChange.AddDynamic(this,&ARAICharacter::OnHealthChange);
}




