// Fill out your copyright notice in the Description page of Project Settings.


#include "RExplosiveActor.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ARExplosiveActor::ARExplosiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>("baseMesh");
	baseMesh->SetSimulatePhysics(true);
	RootComponent = baseMesh;
	
	pulseComp = CreateDefaultSubobject<URadialForceComponent>("pulseComp");
	pulseComp->SetupAttachment(baseMesh);
	
	pulseComp->SetAutoActivate(false);
	pulseComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
	pulseComp->bImpulseVelChange = true;
	
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



// Called every frame
void ARExplosiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARExplosiveActor::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	pulseComp->FireImpulse();

	UE_LOG(LogTemp,Log,TEXT("Pulse"));

	UE_LOG(LogTemp,Warning,TEXT("OtherActor:%s,At Game Time:%f"),*GetNameSafe(OtherActor),GetWorld()->TimeSeconds);

	DrawDebugString(GetWorld(),Hit.ImpactPoint,TEXT("this way"),nullptr,FColor::Red,2.0f,true);
}