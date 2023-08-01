// Fill out your copyright notice in the Description page of Project Settings.


#include "RExplosiveActor.h"

#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ARExplosiveActor::ARExplosiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>("baseMesh");
	RootComponent = baseMesh;

	pulseComp = CreateDefaultSubobject<URadialForceComponent>("pulseComp");
	pulseComp->SetupAttachment(baseMesh);
	
	
}

// Called when the game starts or when spawned
void ARExplosiveActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARExplosiveActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	baseMesh->OnComponentHit.AddDynamic(this,&ARExplosiveActor::OnActorHit);
}

void ARExplosiveActor::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	pulseComp->FireImpulse();
}

// Called every frame
void ARExplosiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

