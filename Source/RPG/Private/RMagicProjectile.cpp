// Fill out your copyright notice in the Description page of Project Settings.


#include "RMagicProjectile.h"

#include "RAttributeComponent.h"
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
	sphereComp->OnComponentBeginOverlap.AddDynamic(this,&ARMagicProjectile::OnActorOverlap);
	particleComp = CreateDefaultSubobject<UParticleSystemComponent>("particleComp");
	particleComp->SetupAttachment(sphereComp);

	projectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("projectileMovementComp");

	projectileMovementComp->InitialSpeed = 8000.0f;
	projectileMovementComp->ProjectileGravityScale = 0;
	projectileMovementComp->bRotationFollowsVelocity = true;
	projectileMovementComp->bInitialVelocityInLocalSpace = true;

	
}

// Called when the game starts or when spawned
void ARMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	sphereComp->IgnoreActorWhenMoving(GetInstigator(),true);
}

// Called every frame
void ARMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)
	{
		URAttributeComponent* attributeComp = Cast<URAttributeComponent>(OtherActor->GetComponentByClass(URAttributeComponent::StaticClass()));
		if (attributeComp)
		{
			attributeComp->ApplyHealthChange(GetInstigator(), -20.0f);
			UE_LOG(LogTemp,Log,TEXT("Apply Damage:-20.0f"));
			Destroy();
		}		
	}
}

