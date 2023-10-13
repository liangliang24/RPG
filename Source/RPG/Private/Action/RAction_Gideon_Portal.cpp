// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/RAction_Gideon_Portal.h"

#include "ObjectStringName.h"
#include "GameFramework/Character.h"

#include "Gideon/RGideon_Portal.h"

URAction_Gideon_Portal::URAction_Gideon_Portal()
{
	actionName = "Gideon_Portal";
}

void URAction_Gideon_Portal::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);
	ACharacter* owner = Cast<ACharacter>(instigator);

	if (owner)
	{
		owner->PlayAnimMontage(PortalStartAnimMontage);

		FVector tempLocation = owner->GetMesh()->GetSocketLocation(Gideon_HandSocketName);
		FRotator tempRotation = owner->GetActorRotation();
		ARGideon_Portal* portal1 = GetWorld()->SpawnActor<ARGideon_Portal>(Portal,tempLocation,tempRotation);
		ARGideon_Portal* portal2 = GetWorld()->SpawnActor<ARGideon_Portal>(Portal,tempLocation + tempRotation.Vector()*1500,tempRotation);

		portal1->BindingPortal = portal2;
		portal2->BindingPortal = portal1;
	}
	StopAction(instigator);
}

void URAction_Gideon_Portal::StopAction_Implementation(AActor* instigator)
{
	Super::StopAction_Implementation(instigator);
}
