// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/RAction_AuroraPrimaryAttack.h"

URAction_AuroraPrimaryAttack::URAction_AuroraPrimaryAttack()
{
	ActionName = "PrimaryAttack";
}

void URAction_AuroraPrimaryAttack::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);
}

void URAction_AuroraPrimaryAttack::StopAction_Implementation(AActor* instigator)
{
	Super::StopAction_Implementation(instigator);
}
