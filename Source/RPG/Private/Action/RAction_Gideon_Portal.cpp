// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/RAction_Gideon_Portal.h"

#include "ObjectStringName.h"
#include "RCharacter.h"
#include "Camera/CameraComponent.h"
#include "Gideon/RGideon_Portal.h"
#include "RPG/RPG.h"

URAction_Gideon_Portal::URAction_Gideon_Portal()
{
	ActionName = FActionName;
	ActionKey = 'F';
}

void URAction_Gideon_Portal::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);
}

void URAction_Gideon_Portal::SpawnPortal_Implementation(ARCharacter* Instigator)
{
	FVector Portal1Location = Instigator->GetMesh()->GetSocketLocation(Gideon_HandSocketName);
	FRotator SpawnRotator = Instigator->cameraComp->GetComponentRotation();
	SpawnRotator.Pitch = 0;
	FActorSpawnParameters spawnParam;
	spawnParam.Instigator = Instigator;
	spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ARGideon_Portal* Portal1 = GetWorld()->SpawnActor<ARGideon_Portal>(Portal,Portal1Location,SpawnRotator);
	ARGideon_Portal* Portal2 = GetWorld()->SpawnActor<ARGideon_Portal>(Portal,ResultLocation + FVector(0,0,50.0f),SpawnRotator);
	UE_LOG(LogTemp,Log,TEXT("%f,%f,%f"),ResultLocation.X,ResultLocation.Y,ResultLocation.Z);
	Portal1->BindingPortal = Portal2;
	Portal2->BindingPortal = Portal1;
}

void URAction_Gideon_Portal::StopAction_Implementation(AActor* instigator)
{
	Super::StopAction_Implementation(instigator);
	if (ResultLocation == FVector::Zero())
	{
		return ;
	}
	ARCharacter* owner = Cast<ARCharacter>(instigator);

	NetMulticast_PlayAnimMontage(owner);
	//LogOnScreen(this,(TEXT("Spawn Success : %s"),ResultLocation.ToString()));

	FTimerHandle SpawnPortal_TimerHandle;
	FTimerDelegate SpawnPortal_TimerDelegate;
	SpawnPortal_TimerDelegate.BindUFunction(this,"SpawnPortal",owner);
	GetWorld()->GetTimerManager().SetTimer(SpawnPortal_TimerHandle,SpawnPortal_TimerDelegate,0.17,false);
	
	
	
}

void URAction_Gideon_Portal::NetMulticast_PlayAnimMontage_Implementation(ARCharacter* Instigator)
{
	//Instigator->PlayAnimMontage(Anim);
}


