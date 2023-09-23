// Fill out your copyright notice in the Description page of Project Settings.


#include "RAction_ProjectileAttack.h"

#include "RCharacter.h"
#include "RMagicProjectile.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "RPG/RPG.h"

URAction_ProjectileAttack::URAction_ProjectileAttack()
{
	attackAnimDelay = 0.17f;

	handSocketName = "Muzzle_01";

	actionName = "PrimaryAttack";

	hasPreAction = true;
}


void URAction_ProjectileAttack::AttackDelay_Elasped_Implementation(ARCharacter* instigator)
{
	if(ensureAlways(projectileClass))
	{
		
		UE_LOG(LogTemp,Log,TEXT("Spawn %s"),*GetNameSafe(projectileClass));
		FVector locationSpawn =  instigator->GetMesh()->GetSocketLocation("Muzzle_01");
		
		//spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
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
			start = locationSpawn;
			end = locationSpawn + instigator->GetActorRotation().Vector()*10000;
		}
		

		
		FCollisionQueryParams params;
		params.AddIgnoredActor(instigator);
		bool queryResult = GetWorld()->LineTraceSingleByChannel(hit,start,end,ECollisionChannel::ECC_Visibility,params);
		FRotator spawnWay;
		if(queryResult)
		{
			spawnWay = (hit.ImpactPoint-locationSpawn).Rotation();
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

		//LogOnScreen(this,"");
		FActorSpawnParameters spawnParameters;
		spawnParameters.Instigator = instigator;
		//spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		GetWorld()->SpawnActor<AActor>(projectileClass,locationSpawn,spawnWay,spawnParameters);
		
		//GetWorld()->GetTimerManager().ClearTimer(primaryAttackHandle);
	}
	
	
	StopAction_Implementation(instigator);
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
	FTimerDelegate delegateForShow;
	delegateForShow.BindUFunction(this,"ShowForAllClient",instigator);
	GetWorld()->GetTimerManager().SetTimer(primaryAttackHandle,delegate,attackAnimDelay,false);

	FTimerHandle showHandle;
	GetWorld()->GetTimerManager().SetTimer(showHandle,delegateForShow,attackAnimDelay,false);
}

void URAction_ProjectileAttack::StopAction_Implementation(AActor* instigator)
{
	Super::StopAction_Implementation(instigator);

	GetWorld()->GetTimerManager().ClearTimer(primaryAttackHandle);
}



void URAction_ProjectileAttack::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	
}

void URAction_ProjectileAttack::PreAction_Implementation(AActor* instigator)
{
	Super::PreAction_Implementation(instigator);
	
}

void URAction_ProjectileAttack::ShowForAllClient_Implementation(AActor* instigator)
{
	Super::ShowForAllClient_Implementation(instigator);
	ARCharacter* character = Cast<ARCharacter>(instigator);
	if (character)
	{
		UGameplayStatics::SpawnEmitterAttached(castingEffect,character->GetMesh(),"Muzzle_01",FVector::ZeroVector,FRotator::ZeroRotator,EAttachLocation::SnapToTarget);
	}
	
}


