// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/RAction_Aurora_E_Ability.h"

#include "ObjectStringName.h"
#include "RPG/RPG.h"

URAction_Aurora_E_Ability::URAction_Aurora_E_Ability()
{
	ActionName = EActionName;
	
	ActionKey = 'E';

	AbilityResult = true;
}

void URAction_Aurora_E_Ability::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);

	FTimerHandle StopActionHandle;
	FTimerDelegate StopActionDelegate;
	StopActionDelegate.BindUFunction(this,"StopAction",instigator);
	GetWorld()->GetTimerManager().SetTimer(StopActionHandle,StopActionDelegate,2.0f,false);
	//StopAction(instigator);
}

void URAction_Aurora_E_Ability::StopAction_Implementation(AActor* instigator)
{
	Super::StopAction_Implementation(instigator);
	
	//LogOnScreen(this,"estop");
}
