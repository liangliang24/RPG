// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/RAction_Gideon_Portal.h"

#include "ObjectStringName.h"
#include "RCharacter.h"
#include "RShowingAimTarget.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Character.h"

#include "Gideon/RGideon_Portal.h"

URAction_Gideon_Portal::URAction_Gideon_Portal()
	:isAiming(false)
{
	actionName = "Gideon_Portal";
}

void URAction_Gideon_Portal::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);
	ARCharacter* owner = Cast<ARCharacter>(instigator);
	if (!Aim)
	{
		Aim = NewObject<UShowingAimTarget>(this,AimTarget);
	}
	if (isAiming)
	{
		UDecalComponent* DecalActor = Aim->Stop();
        
        if (owner)
        {
        	float x = owner->PlayAnimMontage(PortalStartAnimMontage);
        	
        	UE_LOG(LogTemp,Log,TEXT("%f"),x);
        	FTimerHandle StartAction_TimerHandle;
        	FTimerDelegate ElaspedDelegate;
        	ElaspedDelegate.BindUFunction(this,"StartAction_Elasped",owner,DecalActor);
        	GetWorld()->GetTimerManager().SetTimer(StartAction_TimerHandle,ElaspedDelegate,0.17,false);
        	
        }
		isAiming = false;
	}
	else
	{

		Aim->Start(owner);
		isAiming = true;
		
	}
	
	
}

void URAction_Gideon_Portal::StartAction_Elasped(ACharacter* instigator, UDecalComponent* BindingPortalSpcifier)
{
	FVector tempLocation = instigator->GetMesh()->GetSocketLocation(Gideon_HandSocketName);
	FRotator tempRotation = instigator->GetViewRotation();
	
	ARGideon_Portal* portal1 = GetWorld()->SpawnActor<ARGideon_Portal>(Portal,tempLocation,tempRotation);
	ARGideon_Portal* portal2 = GetWorld()->SpawnActor<ARGideon_Portal>(Portal,
		BindingPortalSpcifier->GetComponentLocation() + BindingPortalSpcifier->GetComponentRotation().Vector()*(-200),
		tempRotation);

	portal1->BindingPortal = portal2;
	portal2->BindingPortal = portal1;

	BindingPortalSpcifier->DestroyComponent();
	//StopAction(instigator);
}

void URAction_Gideon_Portal::StopAction_Implementation(AActor* instigator)
{
	Super::StopAction_Implementation(instigator);
}


