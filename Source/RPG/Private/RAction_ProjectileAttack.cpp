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


void URAction_ProjectileAttack::AttackDelay_Elasped(ARCharacter* instigator)
{
	if(ensureAlways(projectileClass))
	{
		
		FActorSpawnParameters spawnParameters;
		spawnParameters.Instigator = instigator;
		spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FVector LocationSpawn = instigator->GetMesh()->GetSocketLocation("Muzzle_01");
		AActor* projectile = GetWorld()->SpawnActor<AActor>(projectileClass,LocationSpawn,(SpawnHit-LocationSpawn).Rotation(),spawnParameters);
		//DrawDebugLine(GetWorld(),LocationSpawn,SpawnHit,FColor::Red,false,2.0f,0,2);
		//LogOnScreen(instigator,FString::Printf(TEXT("Spawn Projectile %s"),*GetNameSafe(projectile)));
		//GetWorld()->GetTimerManager().ClearTimer(primaryAttackHandle);
	}
	
	
	StopAction_Implementation(instigator);
}

void URAction_ProjectileAttack::NetMultiCastAnimation_Implementation(ACharacter* instigator)
{
	instigator->PlayAnimMontage(attackAnim);
}


void URAction_ProjectileAttack::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);
	
	ACharacter* player = Cast<ACharacter>(instigator);
	if (!player)
	{
		return ;
	}
	NetMultiCastAnimation(player);
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
	DOREPLIFETIME(URAction_ProjectileAttack,SpawnHit);
}



void URAction_ProjectileAttack::SetSpawnHit_Implementation(const FVector & HitPoint)
{
	SpawnHit = HitPoint;
}

void URAction_ProjectileAttack::PreAction_Implementation(AActor* instigatorActor)
{
	Super::PreAction_Implementation(instigatorActor);

	ACharacter* instigator = Cast<ACharacter>(instigatorActor);
	if (!instigator)
	{
		return ;	
	}
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
	//FRotator spawnWay;
	if(queryResult)
	{
		end = hit.Location;
	}
	/*else
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
			
	}*/
	SetSpawnHit(end);
	//LogOnScreen(this,"");
	
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

void URAction_ProjectileAttack::OnRep_RepData_Implementation()
{
	Super::OnRep_RepData_Implementation();
	/*if (repData.bIsRunning)
	{
		ACharacter* instigator = Cast<ACharacter>(repData.instigator);
        instigator->PlayAnimMontage(attackAnim);
	}*/
	
}
