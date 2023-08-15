// Fill out your copyright notice in the Description page of Project Settings.


#include "RGideonDashProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
//#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ARGideonDashProjectile::ARGideonDashProjectile()
{
	teleportDelay = 0.2f;
	detonateDelay = 0.2f;

	moveComp->InitialSpeed = 6000.0f;
}
void ARGideonDashProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(timeHandle_Delay,this,&ARGideonDashProjectile::Explode,detonateDelay);
	UE_LOG(LogTemp,Log,TEXT("SpawnDash"));
}
void ARGideonDashProjectile::Explode_Implementation()
{
	Super::Explode_Implementation();

	
	

	UGameplayStatics::SpawnEmitterAtLocation(this,impactVFX,GetActorLocation(),GetActorRotation());

	effectComp->DeactivateSystem();

	moveComp->StopMovementImmediately();
	SetActorEnableCollision(false);
	UE_LOG(LogTemp,Log,TEXT("Dash_Explode"));
	
	//GetWorldTimerManager().SetTimer(timerHandle_Teleport,this,&ARGideonDashProjectile::teleportInstigator,teleportDelay);
	teleportInstigator();
	GetWorldTimerManager().ClearTimer(timeHandle_Delay);
	
}

void ARGideonDashProjectile::teleportInstigator()
{
	UE_LOG(LogTemp,Log,TEXT("Teleport"));
	AActor* instigator = GetInstigator();
	if(ensure(instigator))
	{
		instigator->TeleportTo(GetActorLocation(),instigator->GetActorRotation(),false,false);
	}
}


