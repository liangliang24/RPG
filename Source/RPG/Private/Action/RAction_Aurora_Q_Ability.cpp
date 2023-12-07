
// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/RAction_Aurora_Q_Ability.h"

#include "ObjectStringName.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "RPG/RPG.h"

URAction_Aurora_Q_Ability::URAction_Aurora_Q_Ability()
{
	ActionName = QActionName;
	ActionKey = 'Q';
	AbilityResult = true;
}

void URAction_Aurora_Q_Ability::SpawnIce_Implementation(AActor* instigator)
{
	/*FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AActor>(IceSpawn,Foot_R->GetSocketLocation(InstigatorSkeletalMeshComponent),instigator->GetActorRotation(),Param);*/
}

void URAction_Aurora_Q_Ability::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);
	
	LogOnScreen(this,"StartActionQ");
	ACharacter* InstigatorCharacter = Cast<ACharacter>(instigator);
	if (InstigatorCharacter)
	{
		InstigatorSkeletalMeshComponent =
			Cast<USkeletalMeshComponent>(
				InstigatorCharacter->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
		Foot_R = InstigatorCharacter->GetMesh()->GetSocketByName("Foot_R");
	}
	StartLocation = instigator->GetActorLocation();
	FTimerHandle StopActionHandle;
	FTimerDelegate StopActionDelegate;
	StopActionDelegate.BindUFunction(this,"StopAction",instigator);
	GetWorld()->GetTimerManager().SetTimer(StopActionHandle,StopActionDelegate,1.33f,false);
	InstigatorCharacterMovement = Cast<UCharacterMovementComponent>(instigator->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	InstigatorForwardVector = instigator->GetActorForwardVector();
	InstigatorUpVector = instigator->GetActorUpVector();
	UKismetMathLibrary::Vector_Normalize(InstigatorForwardVector);
	UKismetMathLibrary::Vector_Normalize(InstigatorUpVector);
	FTimerDelegate MoveDelegate;
	MoveDelegate.BindUFunction(this,"MoveTick",instigator);
	GetWorld()->GetTimerManager().SetTimer(MoveHandle,MoveDelegate,GetWorld()->GetDeltaSeconds(),true,0.33f);
	FTimerHandle SpawnIceHandle;

	FTimerDelegate SpawnDelegate;
	SpawnDelegate.BindUFunction(this,"SpawnIce",instigator);
	GetWorld()->GetTimerManager().SetTimer(SpawnIceHandle,SpawnDelegate,0.5,false);
}

void URAction_Aurora_Q_Ability::StopAction_Implementation(AActor* instigator)
{
	Super::StopAction_Implementation(instigator);
	LogOnScreen(this,"StopActionQ");
	
}

void URAction_Aurora_Q_Ability::MoveTick(AActor* Instigator)
{
	
	if (FVector::Distance(StartLocation,Instigator->GetActorLocation())>=MoveLength)
	{
		LogOnScreen(this,"Clear");
		GetWorld()->GetTimerManager().ClearTimer(MoveHandle);
		InstigatorCharacterMovement->AddForce(-((InstigatorForwardVector)*speed+upspeed*InstigatorUpVector));
		InstigatorCharacterMovement->StopMovementImmediately();
		return ;
	}
	
	InstigatorCharacterMovement->AddForce((InstigatorForwardVector)*speed);
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AActor>(IceSpawn,Foot_R->GetSocketLocation(InstigatorSkeletalMeshComponent),Instigator->GetActorRotation(),Param);
}