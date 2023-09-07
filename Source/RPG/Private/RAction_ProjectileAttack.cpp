// Fill out your copyright notice in the Description page of Project Settings.


#include "RAction_ProjectileAttack.h"

#include "RCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

URAction_ProjectileAttack::URAction_ProjectileAttack()
{
	attackAnimDelay = 0.17f;

	handSocketName = "Muzzle_01";

	actionName = "PrimaryAttack";
}

void URAction_ProjectileAttack::AttackDelay_Elasped(ARCharacter* instigator)
{

	if(ensureAlways(projectileClass))
	{
		UE_LOG(LogTemp,Log,TEXT("Spawn %s"),*GetNameSafe(projectileClass));
		FVector location =  instigator->GetMesh()->GetSocketLocation("Muzzle_01");
		FActorSpawnParameters spawnParameters;
		spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		spawnParameters.Instigator = instigator;
		FHitResult hit;
		FVector start;
		FVector end;
		UCameraComponent* cameraComp = Cast<UCameraComponent>(instigator->GetComponentByClass(UCameraComponent::StaticClass()));
		if (cameraComp)
		{
			
			start = cameraComp->GetComponentLocation();
			end = start + cameraComp->GetComponentRotation().Vector()*10000;
		}
		else
		{
			UE_LOG(LogTemp,Log,TEXT("Can't not find CameraComp"));
			start = location;
			end = location + instigator->GetActorRotation().Vector()*10000;
		}
		

		
		FCollisionQueryParams params;
		params.AddIgnoredActor(instigator);
		bool queryResult = GetWorld()->LineTraceSingleByChannel(hit,start,end,ECollisionChannel::ECC_Visibility,params);
		FRotator spawnWay;
		UGameplayStatics::SpawnEmitterAttached(castingEffect,instigator->GetMesh(),"Muzzle_01",FVector::ZeroVector,FRotator::ZeroRotator,EAttachLocation::SnapToTarget);
		if(queryResult)
		{
			spawnWay = (hit.ImpactPoint-location).Rotation();
		}
		else
		{
			if (cameraComp)
			{
				spawnWay = cameraComp->GetComponentRotation();
				//GetWorld()->SpawnActor<AActor>(projectileClass,location,cameraComp->GetComponentRotation(),spawnParameters);
			}
			else
			{
				spawnWay = (end-start).Rotation();
				//GetWorld()->SpawnActor<AActor>(projectileClass,location,(end-start).Rotation(),spawnParameters);
			}
			
		}
	
		GetWorld()->SpawnActor<AActor>(projectileClass,location,spawnWay,spawnParameters);
		//GetWorld()->GetTimerManager().ClearTimer(primaryAttackHandle);
	}

	StopAction(instigator);
}

void URAction_ProjectileAttack::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);

	ACharacter* player = Cast<ACharacter>(instigator);
	if (!player)
	{
		return ;
	}
	player->PlayAnimMontage(attackAnim);
	FTimerDelegate delegate;
	delegate.BindUFunction(this,"AttackDelay_Elasped",instigator);
	GetWorld()->GetTimerManager().SetTimer(primaryAttackHandle,delegate,attackAnimDelay,false);
}

void URAction_ProjectileAttack::StopAction_Implementation(AActor* instigator)
{
	Super::StopAction_Implementation(instigator);

	GetWorld()->GetTimerManager().ClearTimer(primaryAttackHandle);
}
