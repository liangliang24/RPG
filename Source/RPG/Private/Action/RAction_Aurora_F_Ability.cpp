// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/RAction_Aurora_F_Ability.h"

#include "ObjectStringName.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

URAction_Aurora_F_Ability::URAction_Aurora_F_Ability()
{
	ActionKey = 'F';
	ActionName = FActionName;
}

void URAction_Aurora_F_Ability::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);

	
	UCharacterMovementComponent* InstigatorCharacterMovementComp = Cast<UCharacterMovementComponent>(
		instigator->GetComponentByClass(UCharacterMovementComponent::StaticClass()));

	if (InstigatorCharacterMovementComp)
	{
		SpawnLocation = instigator->GetActorLocation();
		FVector impulse = instigator->GetActorForwardVector();
		UKismetMathLibrary::Vector_Normalize(impulse);
		InstigatorCharacterMovementComp->AddImpulse((-impulse)*power);
	}

	
	FTimerHandle StopActionHandle;
	FTimerDelegate StopActionDelegate;
	StopActionDelegate.BindUFunction(this,"StopAction",instigator);
	GetWorld()->GetTimerManager().SetTimer(StopActionHandle,StopActionDelegate,1.0f,false);
}

void URAction_Aurora_F_Ability::StopAction_Implementation(AActor* instigator)
{
	Super::StopAction_Implementation(instigator);

	GetWorld()->SpawnActor<AActor>(IceAurora,SpawnLocation,instigator->GetActorRotation());
}
