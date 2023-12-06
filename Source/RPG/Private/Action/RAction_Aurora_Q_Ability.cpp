
// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/RAction_Aurora_Q_Ability.h"

#include "ObjectStringName.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "RPG/RPG.h"

URAction_Aurora_Q_Ability::URAction_Aurora_Q_Ability()
{
	ActionName = QActionName;
	ActionKey = 'Q';
	AbilityResult = true;
}

void URAction_Aurora_Q_Ability::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);
	LogOnScreen(this,"StartActionQ");
	StartLocation = instigator->GetActorLocation();
	FTimerHandle StopActionHandle;
	FTimerDelegate StopActionDelegate;
	StopActionDelegate.BindUFunction(this,"StopAction",instigator);
	GetWorld()->GetTimerManager().SetTimer(StopActionHandle,StopActionDelegate,2,false);
	UCharacterMovementComponent* InstigatorCharacterMovement = Cast<UCharacterMovementComponent>(instigator->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	InstigatorForwardVector = instigator->GetActorForwardVector();
	UKismetMathLibrary::Vector_Normalize(InstigatorForwardVector);
	FTimerDelegate MoveDelegate;
	MoveDelegate.BindUFunction(this,"MoveTick",instigator,InstigatorCharacterMovement);
	GetWorld()->GetTimerManager().SetTimer(MoveHandle,MoveDelegate,GetWorld()->GetDeltaSeconds(),true,0.33);
}

void URAction_Aurora_Q_Ability::StopAction_Implementation(AActor* instigator)
{
	Super::StopAction_Implementation(instigator);
	LogOnScreen(this,"StopActionQ");
}

void URAction_Aurora_Q_Ability::MoveTick(AActor* Instigator, UCharacterMovementComponent* InstigatorCharacterMovement)
{
	
	if (FVector::Distance(StartLocation,Instigator->GetActorLocation())>=MoveLength)
	{
		LogOnScreen(this,"Clear");
		GetWorld()->GetTimerManager().ClearTimer(MoveHandle);
		return ;
	}
	InstigatorCharacterMovement->AddForce(InstigatorForwardVector*speed);
}