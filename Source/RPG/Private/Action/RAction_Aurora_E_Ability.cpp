// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/RAction_Aurora_E_Ability.h"

#include "ObjectStringName.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
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
	GetWorld()->GetTimerManager().SetTimer(StopActionHandle,StopActionDelegate,1.0f,false);
	FHitResult hit;
	FVector end = instigator->GetActorLocation() + (-instigator->GetActorUpVector())*300;
	//StopAction(instigator);
	
	if (GetWorld()->LineTraceSingleByChannel(hit,instigator->GetActorLocation(),end,ECC_Visibility))
	{
		SpawnCenter = hit.Location;
	}
	
}



void URAction_Aurora_E_Ability::StopAction_Implementation(AActor* instigator)
{
	Super::StopAction_Implementation(instigator);
}

void URAction_Aurora_E_Ability::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URAction_Aurora_E_Ability,SpawnCenter);
}
