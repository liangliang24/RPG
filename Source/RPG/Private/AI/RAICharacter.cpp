// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "RAttributeComponent.h"
#include "AI/RAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ARAICharacter::ARAICharacter():materialParamName("TimeToHit")
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
	
	ARAIController* AIController = Cast<ARAIController>(GetController());
	AIController->GetBlackboardComponent()->SetValueAsFloat("Health",NewHealth);
	if(NewHealth <= 0)
	{
		GetCharacterMovement()->DisableMovement();
		
		
		if(AIController)
			AIController->GetBrainComponent()->StopLogic("Die");

		GetMesh()->SetAllBodiesSimulatePhysics(true);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
		FTimerHandle dieHandle;
		GetWorldTimerManager().SetTimer(dieHandle,this,&ARAICharacter::Die,3.0f);
	}

	if (Delta < 0)
	{
		GetMesh()->SetScalarParameterValueOnMaterials(materialParamName,GetWorld()->TimeSeconds);
		if(InstigatorActor!=this)
			AIController->GetBlackboardComponent()->SetValueAsObject("TargetActor",InstigatorActor);
	}
}

void ARAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	pawnSensingComp->OnSeePawn.AddDynamic(this,&ARAICharacter::OnSeePawn);
	attributeComp->OnHealthChange.AddDynamic(this,&ARAICharacter::OnHealthChange);
}




