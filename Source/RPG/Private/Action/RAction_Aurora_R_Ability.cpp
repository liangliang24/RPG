// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/RAction_Aurora_R_Ability.h"

#include "ObjectStringName.h"
#include "RActionComponent.h"
#include "RAttributeComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RPG/RPG.h"

URAction_Aurora_R_Ability::URAction_Aurora_R_Ability()
{
	ActionName = RActionName;
	ActionKey = 'R';
	AbilityResult = true;
}

void URAction_Aurora_R_Ability::SpawnDecalActor_Implementation(AActor* instigator)
{
	DecalActor = UGameplayStatics::SpawnDecalAtLocation(
		this,
		DecalMaterial,
		DecalSize,
		TraceDecalSpawnLine(instigator));

	FTimerDelegate SetDecalLocationDelegate;
	SetDecalLocationDelegate.BindUFunction(this,"SetDecalLocation",instigator);
	GetWorld()->GetTimerManager().SetTimer(SetDecalLocationHandle,SetDecalLocationDelegate,GetWorld()->GetDeltaSeconds(),true);

	
}

void URAction_Aurora_R_Ability::FireDamage_Implementation(AActor* Instigator)
{
	NetMulticast_StopDecalLogic();

	TArray<FHitResult> hit;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(DamageRadius);
	//UKismetSystemLibrary::DrawDebugSphere(this,Instigator->GetActorLocation(),DamageRadius,8,FColor::Red,2);
	GetWorld()->SweepMultiByObjectType(hit,
	                                   Instigator->GetActorLocation(),
	                                   Instigator->GetActorLocation(),
	                                   FQuat(),
	                                   ECC_Pawn,
	                                   CollisionShape);
	TArray<AActor*> HitActors;
	for(FHitResult& i:hit)
	{
		AActor* HitActor = i.GetActor();
		//LogOnScreen(this,FString::Printf(TEXT("%s"),*GetNameSafe(HitActor)));
		if (HitActor&&!HitActors.Contains(HitActor))
		{
			HitActors.Add(HitActor);
			URActionComponent* HitActionComp = Cast<URActionComponent>(HitActor->GetComponentByClass(URActionComponent::StaticClass()));
			if (HitActionComp)
			{
				HitActionComp->AddAction(ActionClass,Instigator);
			}
		}
	}
}


void URAction_Aurora_R_Ability::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);

	
	SpawnDecalActor(instigator);


	FTimerHandle FireDamageHandle;
	FTimerDelegate FireDamageDelegate;
	FireDamageDelegate.BindUFunction(this,"FireDamage",instigator);
	GetWorld()->GetTimerManager().SetTimer(FireDamageHandle,FireDamageDelegate,0.6,false);
}

void URAction_Aurora_R_Ability::NetMulticast_StopDecalLogic_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(SetDecalLocationHandle);
	if (ensure(DecalActor))
	{
		DecalActor->DestroyComponent();
	}
}

void URAction_Aurora_R_Ability::StopAction_Implementation(AActor* instigator)
{
	Super::StopAction_Implementation(instigator);

	//NetMulticast_StopDecalLogic();
	
}

FVector URAction_Aurora_R_Ability::TraceDecalSpawnLine(AActor* Instigator)
{
	FVector Start = Instigator->GetActorLocation();
	FVector End = Start - FVector(0,0,500);

	FHitResult hit;
	bool TraceResult = GetWorld()->LineTraceSingleByChannel(hit,Start,End,ECC_Visibility);
	if (TraceResult)
	{
		return hit.ImpactPoint;
	}

	return FVector::Zero();
}

void URAction_Aurora_R_Ability::SetDecalLocation_Implementation(AActor* Instigator)
{
	DecalActor->SetWorldLocation(TraceDecalSpawnLine(Instigator));
}
