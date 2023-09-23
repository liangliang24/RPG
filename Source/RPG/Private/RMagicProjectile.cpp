// Fill out your copyright notice in the Description page of Project Settings.


#include "RMagicProjectile.h"

#include "RActionComponent.h"
#include "RAttributeComponent.h"
#include "RGamePlayFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "RPG/RPG.h"


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
	sphereComp->IgnoreActorWhenMoving(this,true);

	bReplicates = true;
	//SetReplicates(true);
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
	LogOnScreen(this,FString::Printf(TEXT("Projectil Hit %s"),*GetNameSafe(OtherActor)));
	UGameplayStatics::PlaySoundAtLocation(this,explodeAudio,GetActorLocation());
	UGameplayStatics::PlayWorldCameraShake(this,shake,GetActorLocation(),500,2000,0.5);
	//UE_LOG(LogTemp,Log,TEXT("other actor %s\nhit actor %s"),*GetNameSafe(OtherActor),*GetNameSafe(hitResult.GetActor()));
	if(OtherActor&&OtherActor != GetInstigator())
	{
		
		URActionComponent* actionComp = Cast<URActionComponent>(OtherActor->GetComponentByClass(URActionComponent::StaticClass()));
		//UE_LOG(LogTemp,Log,TEXT("hit %s ActionComp %s"),*GetNameSafe(OtherActor),*GetNameSafe(actionComp));
		if (actionComp&&actionComp->activeGameplayTags.HasTag(Tag))
		{
			projectileMovementComp->Velocity = -projectileMovementComp->Velocity;
			SetInstigator(Cast<APawn>(OtherActor));

			return ;
		}
		//URActionComponent* actionComp = Cast<URActionComponent>(OtherActor->GetComponentByClass(URActionComponent::StaticClass()));
		if (actionComp)
		{
			actionComp->AddAction(burningActionClass,GetInstigator());
		}
		URGamePlayFunctionLibrary::ApplyDirectionDamage(GetInstigator(),OtherActor,damage,hitResult);
		UGameplayStatics::SpawnEmitterAtLocation(this,explodeEmitter,GetActorLocation(),GetActorRotation());
		Destroy();
	}
}

void ARMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass() == GetClass())
	{
		return ;
	}
	DoDamage(OtherActor, SweepResult);
}

void ARMagicProjectile::ActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp,Log,TEXT("Hit"));
	if (OtherActor->GetClass() == GetClass())
	{
		return ;
	}
	DoDamage(OtherActor, Hit);
}

