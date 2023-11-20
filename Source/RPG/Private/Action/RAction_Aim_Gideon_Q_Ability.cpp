// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/RAction_Aim_Gideon_Q_Ability.h"

#include "ObjectStringName.h"
#include "RCharacter.h"

URAction_Aim_Gideon_Q_Ability::URAction_Aim_Gideon_Q_Ability()
{
	ActionName = Gideon_QAbility;
	ActionKey = 'Q';
}

void URAction_Aim_Gideon_Q_Ability::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);
	
}

void URAction_Aim_Gideon_Q_Ability::SpawnMeteor()
{
	GetWorld()->SpawnActor<AActor>(Damage_Meteor,ResultLocation,FRotator::ZeroRotator);
}

void URAction_Aim_Gideon_Q_Ability::StopAction_Implementation(AActor* instigator)
{
	Super::StopAction_Implementation(instigator);
	if (ResultLocation == FVector::Zero())
	{
		return ;
	}
	ARCharacter* owner = Cast<ARCharacter>(instigator);
	NetMulticastAnimMontage(owner);
	FTimerHandle SpawnMeteor_TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(SpawnMeteor_TimerHandle,this,&URAction_Aim_Gideon_Q_Ability::SpawnMeteor,0.17,false);
	
}

void URAction_Aim_Gideon_Q_Ability::NetMulticastAnimMontage_Implementation(ARCharacter* Instigator)
{
	//Instigator->PlayAnimMontage(AnimMontage);
}
