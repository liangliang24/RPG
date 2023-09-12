// Fill out your copyright notice in the Description page of Project Settings.


#include "RMagicProjectile.h"

#include "RAttributeComponent.h"
#include "RGamePlayFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"




// Sets default values
ARMagicProjectile::ARMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sphereComp = CreateDefaultSubobject<USphereComponent>("sphereComp");
	RootComponent = sphereComp;
	sphereComp->OnComponentBeginOverlap.AddDynamic(this,&ARMagicProjectile::OnActorOverlap);
	sphereComp->OnComponentHit.AddDynamic(this,&ARMagicProjectile::ActorHit);
	particleComp = CreateDefaultSubobject<UParticleSystemComponent>("particleComp");
	particleComp->SetupAttachment(sphereComp);

	projectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("projectileMovementComp");

	movingAudio = CreateDefaultSubobject<UAudioComponent>("MovingAudio");
	movingAudio->SetupAttachment(RootComponent);
	movingAudio->SetAutoActivate(true);
	projectileMovementComp->InitialSpeed = 8000.0f;
	projectileMovementComp->ProjectileGravityScale = 0;
	projectileMovementComp->bRotationFollowsVelocity = true;
	projectileMovementComp->bInitialVelocityInLocalSpace = true;

	damage = 20.0f;

	sphereComp->IgnoreActorWhenMoving(GetInstigator(),true);
}

// Called when the game starts or when spawned
void ARMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	sphereComp->IgnoreActorWhenMoving(GetInstigator(),true);
	//movingAudio->Play();
}



// Called every frame
void ARMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ARMagicProjectile::DoDamage(AActor* OtherActor, const FHitResult& hitResult)
{
	UGameplayStatics::PlaySoundAtLocation(this,explodeAudio,GetActorLocation());
	UGameplayStatics::PlayWorldCameraShake(this,shake,GetActorLocation(),500,2000,0.5);
	if(OtherActor)
	{
		/*URAttributeComponent* attributeComp = Cast<URAttributeComponent>(OtherActor->GetComponentByClass(URAttributeComponent::StaticClass()));
		if (attributeComp)
		{
			attributeComp->ApplyHealthChange(GetInstigator(), damage);
			UE_LOG(LogTemp,Log,TEXT("Apply Damage:-20.0f"));
			
			Destroy();
		}	*/

		URGamePlayFunctionLibrary::ApplyDirectionDamage(GetInstigator(),OtherActor,damage,hitResult);
		Destroy();
	}
}

void ARMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DoDamage(OtherActor, SweepResult);
}

void ARMagicProjectile::ActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	DoDamage(OtherActor, Hit);
}

