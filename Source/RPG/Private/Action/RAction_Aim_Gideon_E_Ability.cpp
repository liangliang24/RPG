// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/RAction_Aim_Gideon_E_Ability.h"

#include "ObjectStringName.h"
#include "RCharacter.h"
#include "RPG/RPG.h"


URAction_Aim_Gideon_E_Ability::URAction_Aim_Gideon_E_Ability()
{
	ActionName = Gideon_BlackHole;
}

void URAction_Aim_Gideon_E_Ability::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);
}

void URAction_Aim_Gideon_E_Ability::StopAction_Implementation(AActor* instigator)
{
	Super::StopAction_Implementation(instigator);

	if (ResultLocation == FVector::Zero())
	{
		LogOnScreen(this,"Won't Spawn");
		return ;
	}
	ARCharacter* owner = Cast<ARCharacter>(instigator);
	NetMulticastAnimMontage(owner);
	FTimerHandle SpawnBlackHole_TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(SpawnBlackHole_TimerHandle,this,&URAction_Aim_Gideon_E_Ability::SpawnBlackHole,0.17,false);
}

void URAction_Aim_Gideon_E_Ability::NetMulticastAnimMontage_Implementation(ARCharacter* Instigator)
{
	Instigator->PlayAnimMontage(SpawnAnimMontage);
}


void URAction_Aim_Gideon_E_Ability::SpawnBlackHole_Implementation()
{
	
	
	GetWorld()->SpawnActor<AActor>(BlackHole,ResultLocation,FRotator::ZeroRotator);

	
}
