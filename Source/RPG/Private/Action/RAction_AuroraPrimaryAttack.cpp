// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/RAction_AuroraPrimaryAttack.h"
#include "ObjectStringName.h"
#include "GameFramework/Character.h"

URAction_AuroraPrimaryAttack::URAction_AuroraPrimaryAttack()
{
	ActionName = LeftButtonPrimaryAttack;

	AbilityResult = true;

}

void URAction_AuroraPrimaryAttack::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);

	ACharacter* InstigatorCharacter = Cast<ACharacter>(instigator);
	if (InstigatorCharacter)
	{
		NetMultiCastAnimation(InstigatorCharacter);
	}
}

void URAction_AuroraPrimaryAttack::StopAction_Implementation(AActor* instigator)
{
	Super::StopAction_Implementation(instigator);

	
}

void URAction_AuroraPrimaryAttack::NetMultiCastAnimation_Implementation(ACharacter* Instigator)
{
	Instigator->PlayAnimMontage(PrimaryAttackMontage);
	StopAction(Instigator);
}
