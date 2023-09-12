// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "RActionComponent.h"
#include "RAttributeComponent.h"
#include "RCharacter.h"
#include "RWorldUserWidget.h"
#include "AI/RAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ARAICharacter::ARAICharacter():materialParamName("TimeToHit")
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComponent");

	attributeComp = CreateDefaultSubobject<URAttributeComponent>("AttributeComponent");

	actionComp = CreateDefaultSubobject<URActionComponent>("ActionComponent");
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
}

void ARAICharacter::OnSeePawn(APawn* Pawn)
{
	AAIController* myController = Cast<AAIController>(GetController());

	if (myController)
	{
		if(Pawn&&Pawn->StaticClass()!=StaticClass())
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
	//UE_LOG(LogTemp,Log,TEXT("Hit By %s"),*GetNameSafe(InstigatorActor));
	ARAIController* AIController = Cast<ARAIController>(GetController());
	if(healthBar == nullptr)
	{
		healthBar = Cast<URWorldUserWidget>(CreateWidget<URWorldUserWidget>(GetWorld(),healthBarWidget));
		if (healthBar)
        {
			healthBar->attachedActor = this;
            healthBar->AddToViewport();
        }
	}
	
	
	AIController->GetBlackboardComponent()->SetValueAsFloat("Health",NewHealth);
	if(NewHealth <= 0)
	{
		GetCharacterMovement()->DisableMovement();

		URAttributeComponent* instigatorAttributeComp = URAttributeComponent::GetAttributeComponent(InstigatorActor);

		if (instigatorAttributeComp)
		{
			instigatorAttributeComp->ApplyCreditChange(this,20);
		}
		
		if(AIController)
			AIController->GetBrainComponent()->StopLogic("Die");

		GetMesh()->SetAllBodiesSimulatePhysics(true);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCharacterMovement()->DisableMovement();
		FTimerHandle dieHandle;
		GetWorldTimerManager().SetTimer(dieHandle,this,&ARAICharacter::Die,3.0f);
	}

	if (Delta < 0)
	{
		GetMesh()->SetScalarParameterValueOnMaterials(materialParamName,GetWorld()->TimeSeconds);
		if(InstigatorActor->StaticClass()!=StaticClass())
			AIController->GetBlackboardComponent()->SetValueAsObject("TargetActor",InstigatorActor);
	}
}

void ARAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	pawnSensingComp->OnSeePawn.AddDynamic(this,&ARAICharacter::OnSeePawn);
	attributeComp->OnHealthChange.AddDynamic(this,&ARAICharacter::OnHealthChange);
}




