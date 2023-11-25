// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/RAction_Gideon_R_Ability.h"

#include "RAttributeComponent.h"
#include "Components/CapsuleComponent.h"
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

	FTimerDelegate DamageRepeatlyDelegate;
	DamageRepeatlyDelegate.BindUFunction(this,"DamageRepeatly",InstigatorCharacter);
	GetWorld()->GetTimerManager().SetTimer(DamageRepeatlyHandle,DamageRepeatlyDelegate,0.2,true);
	FTimerHandle StopDamageHandle;
	GetWorld()->GetTimerManager().SetTimer(StopDamageHandle,this,&URAction_Gideon_R_Ability::StopDamage,5,false,5);
}

void URAction_Gideon_R_Ability::DamageRepeatly(ACharacter* Instigator)
{
	TArray<FHitResult> OutHits;
	FVector Start;
	Start = Instigator->GetActorLocation();
	FVector End = Start;
	FCollisionShape CollisionShape;
	CollisionShape.SetCapsule(400,300);
	UE_LOG(LogTemp,Log,TEXT("5"));
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(Instigator);
	GetWorld()->SweepMultiByChannel(OutHits,Start,End,FQuat::Identity,ECC_Pawn,CollisionShape,CollisionQueryParams);

	for(FHitResult& i:OutHits)
	{
		AActor* HitPawn = i.GetActor();
		if (HitPawn)
		{
			URAttributeComponent* iAttribtueComp = Cast<URAttributeComponent>(HitPawn->GetComponentByClass(URAttributeComponent::StaticClass()));
			if (iAttribtueComp)
			{
				iAttribtueComp->ApplyHealthChange(Instigator,-10);
				DrawDebugSphere(GetWorld(),i.ImpactPoint,30,8,FColor::Purple,false,2,0,1);

			}
		}
	}
}

void URAction_Gideon_R_Ability::StopDamage()
{
	LogOnScreen(this,FString("StopDamage"));
	GetWorld()->GetTimerManager().ClearTimer(DamageRepeatlyHandle);
}

void URAction_Gideon_R_Ability::NetMulticastAnimMontage_Implementation(ACharacter* Instigator, UAnimMontage* AnimToPlay)
{
	LogOnScreen(this,FString::Printf(TEXT("AnimToPlay:%s"),*AnimToPlay->GetName()));
	Instigator->PlayAnimMontage(AnimToPlay);
}
