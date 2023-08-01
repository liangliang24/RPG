// Fill out your copyright notice in the Description page of Project Settings.


#include "RMagicProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ARMagicProjectile::ARMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sphereComp = CreateDefaultSubobject<USphereComponent>("sphereComp");
	RootComponent = sphereComp;

	particleComp = CreateDefaultSubobject<UParticleSystemComponent>("particleComp");
	particleComp->SetupAttachment(sphereComp);

	projectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("projectileMovementComp");

	projectileMovementComp->InitialSpeed = 1000.0f;
	projectileMovementComp->ProjectileGravityScale = 0;
	projectileMovementComp->bRotationFollowsVelocity = true;
	projectileMovementComp->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void ARMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

