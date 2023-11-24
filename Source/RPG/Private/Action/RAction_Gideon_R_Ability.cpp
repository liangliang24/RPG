// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/RAction_Gideon_R_Ability.h"

#include "GameFramework/Character.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "RPG/RPG.h"

URAction_Gideon_R_Ability::URAction_Gideon_R_Ability()
{
	ActionName = "Gideon_RAbility";
	ActionKey = 'R';
}

void URAction_Gideon_R_Ability::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);

	
}

void URAction_Gideon_R_Ability::StopAction_Implementation(AActor* instigator)
{
	Super::StopAction_Implementation(instigator);

	LogOnScreen(this,"StopRAction");

	ACharacter* InstigatorCharacter = Cast<ACharacter>(instigator);
	if (ResultLocation!=FVector::Zero())
	{
		instigator->TeleportTo(ResultLocation + FVector(0,0,100.0f),instigator->GetActorRotation());

		NetMulticastAnimMontage(InstigatorCharacter, AnimStart);

		//LogOnScreen(this,FString::Printf(TEXT("Rest time: %s"),*UKismetStringLibrary::Conv_DoubleToString(AnimStart->CalculateSequenceLength())));
		FTimerHandle AnimLoopTimerHandle;
		FTimerDelegate AnimLoopTimerDelegate;
		AnimLoopTimerDelegate.BindUFunction(this,"NetMulticastAnimMontage",InstigatorCharacter,AnimLoop);
		GetWorld()->GetTimerManager().SetTimer(AnimLoopTimerHandle,AnimLoopTimerDelegate,3.6,false,3.6);
		
	}
}

void URAction_Gideon_R_Ability::NetMulticastAnimMontage_Implementation(ACharacter* Instigator, UAnimMontage* AnimToPlay)
{
	LogOnScreen(this,FString::Printf(TEXT("AnimToPlay:%s"),*AnimToPlay->GetName()));
	Instigator->PlayAnimMontage(AnimToPlay);
}
