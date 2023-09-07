// Fill out your copyright notice in the Description page of Project Settings.


#include "RAction.h"

void URAction::StartAction_Implementation(AActor* instigator)
{
	UE_LOG(LogTemp,Log,TEXT("Running:%s"),*GetNameSafe(instigator));
}

void URAction::StopAction_Implementation(AActor* instigator)
{
}
