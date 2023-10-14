// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/RAction_Gideon_Portal.h"

#include "ObjectStringName.h"
#include "RCharacter.h"
#include "RShowingAimTarget.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Character.h"

#include "Gideon/RGideon_Portal.h"
#include "Net/UnrealNetwork.h"
#include "RPG/RPG.h"

URAction_Gideon_Portal::URAction_Gideon_Portal()
	:isAiming(false)
{
	actionName = "Gideon_Portal";
}

void URAction_Gideon_Portal::CreateAim_Implementation()
{
	Aim = NewObject<UShowingAimTarget>(this,AimTarget);
}

void URAction_Gideon_Portal::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);
	ARCharacter* owner = Cast<ARCharacter>(instigator);
	
	if (isAiming)
	{
        if (owner)
        {

        	AimStop();
        	float x = owner->PlayAnimMontage(PortalStartAnimMontage);
        	
        	//UE_LOG(LogTemp,Log,TEXT("%f"),x);
        	FTimerHandle StartAction_TimerHandle;
        	FTimerDelegate ElaspedDelegate;
        	ElaspedDelegate.BindUFunction(this,"StartAction_Elasped",owner);
        	GetWorld()->GetTimerManager().SetTimer(StartAction_TimerHandle,ElaspedDelegate,0.17,false);
        	
        }
		isAiming = false;
	}
	else
	{
		AimStart(owner);
		//Aim->Start(owner);
		isAiming = true;
		
	}
	
	
}

void URAction_Gideon_Portal::StartAction_Elasped(ACharacter* instigator)
{
	FVector tempLocation = instigator->GetMesh()->GetSocketLocation(Gideon_HandSocketName);
	FRotator tempRotation = instigator->GetViewRotation();
	
	ARGideon_Portal* portal1 = GetWorld()->SpawnActor<ARGideon_Portal>(Portal,tempLocation,tempRotation);
	ARGideon_Portal* portal2 = GetWorld()->SpawnActor<ARGideon_Portal>(Portal,
		Portal2SpawnLocation,
		tempRotation);

	portal1->BindingPortal = portal2;
	portal2->BindingPortal = portal1;
	
	//DecalActor->DestroyComponent();
	//StopAction(instigator);
}

void URAction_Gideon_Portal::AimStop_Implementation()
{
	SetPortal2SpawnLocation(Aim->Stop()->GetComponentLocation()+Aim->Stop()->GetComponentRotation().Vector()*(-200.0f));
}

void URAction_Gideon_Portal::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URAction_Gideon_Portal,Aim);
	DOREPLIFETIME(URAction_Gideon_Portal,Portal2SpawnLocation);
}

void URAction_Gideon_Portal::StopAction_Implementation(AActor* instigator)
{
	Super::StopAction_Implementation(instigator);
}

void URAction_Gideon_Portal::SetPortal2SpawnLocation_Implementation(FVector NewLocation)
{
	Portal2SpawnLocation = NewLocation;
}


void URAction_Gideon_Portal::AimStart_Implementation(ARCharacter* Instigator)
{
	if (!Aim)
	{
		CreateAim();
	}
	LogOnScreen(this,(TEXT("%s"),*GetNameSafe(Aim)));
	Aim->Start(Instigator);
}


