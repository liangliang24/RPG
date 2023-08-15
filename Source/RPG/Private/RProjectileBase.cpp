// Fill out your copyright notice in the Description page of Project Settings.


#include "RProjectileBase.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ARProjectileBase::ARProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	sphere->SetCollisionProfileName("Projectile");
	sphere->OnComponentHit.AddDynamic(this,&ARProjectileBase::OnActorHit);
	RootComponent = sphere;
	


	effectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	effectComp->SetupAttachment(RootComponent);

	moveComp = CreateDefaultSubobject<UProjectileMovementComponent>("MoveComp");
	moveComp->bRotationFollowsVelocity = true;
	moveComp->bInitialVelocityInLocalSpace = true;
	moveComp->ProjectileGravityScale = 0.0f;
	moveComp->InitialSpeed = 1000.0f;
}

// Called when the game starts or when spawned
void ARProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	sphere->IgnoreActorWhenMoving(GetInstigator(),true);
}

void ARProjectileBase::Explode_Implementation()
{
	if(ensure(!IsPendingKill()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this,impactVFX,GetActorLocation(),GetActorRotation());

		Destroy();
	}
}

void ARProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void ARProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called every frame
void ARProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

