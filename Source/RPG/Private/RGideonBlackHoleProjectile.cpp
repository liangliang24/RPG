// Fill out your copyright notice in the Description page of Project Settings.


#include "RGideonBlackHoleProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

ARGideonBlackHoleProjectile::ARGideonBlackHoleProjectile()
{
	isExplode = false;
	moveComp->InitialSpeed = 6000.0f;

	suckComp = CreateDefaultSubobject<URadialForceComponent>("SuckComponent");
	suckComp->SetupAttachment(RootComponent);

	suckComp->Radius = 1000.0f;
	suckComp->ForceStrength = -20000000.0f;
	//suckComp->AddCollisionChannelToAffect(ECC_Pawn);
	//suckComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
	suckComp->AddCollisionChannelToAffect(ECC_PhysicsBody);
	suckComp->bImpulseVelChange = true;
	suckComp->SetAutoActivate(false);
	
	blackHole = CreateDefaultSubobject<UParticleSystemComponent>("BlackHole");
	blackHole->SetupAttachment(RootComponent);
	blackHole->SetAutoActivate(false);
	sphere->IgnoreActorWhenMoving(GetInstigator(),true);
}


void ARGideonBlackHoleProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!isExplode)
	{
		Explode();
		return ;
	}
	
	if(OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
}

void ARGideonBlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay(); 

	GetWorldTimerManager().SetTimer(timerHandle_Explode,this,&ARGideonBlackHoleProjectile::Explode,2.0f);
}

void ARGideonBlackHoleProjectile::Explode_Implementation()
{
	if(isExplode) return;
	//if(ensure(IsPendingKill())) return;
	//Super::Explode_Implementation();
	UE_LOG(LogTemp,Log,TEXT("Explode"));
	isExplode = true;
	effectComp->DeactivateSystem();
	blackHole->ActivateSystem();
	
	moveComp->StopMovementImmediately();
	
	suckComp->Activate();

	
	GetWorldTimerManager().SetTimer(timerHandle_Destroy,this,FTimerDelegate::TMethodPtr<ARGideonBlackHoleProjectile>(&ARGideonBlackHoleProjectile::Destroy),5.0f);
	
	
	//blackHole
}

void ARGideonBlackHoleProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	sphere->OnComponentBeginOverlap.AddDynamic(this,&ARGideonBlackHoleProjectile::OnActorOverlap);
}
