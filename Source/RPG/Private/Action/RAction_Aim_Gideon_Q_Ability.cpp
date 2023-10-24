// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/RAction_Aim_Gideon_Q_Ability.h"

URAction_Aim_Gideon_Q_Ability::URAction_Aim_Gideon_Q_Ability()
{
}

void URAction_Aim_Gideon_Q_Ability::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);
	
}

void URAction_Aim_Gideon_Q_Ability::StopAction_Implementation(AActor* instigator)
{
	Super::StopAction_Implementation(instigator);

	GetWorld()->SpawnActor<AActor>(Damage_Meteor,ResultLocation,FRotator::ZeroRotator);
}
