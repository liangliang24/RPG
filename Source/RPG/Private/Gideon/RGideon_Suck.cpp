// Fill out your copyright notice in the Description page of Project Settings.


#include "Gideon/RGideon_Suck.h"

#include "RCharacter.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ARGideon_Suck::ARGideon_Suck()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
	
	//BaseMesh->OnComponentBeginOverlap.AddDynamic(this,&ARGideon_Suck::OnOverlap);

	Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
	Particle->SetupAttachment(BaseMesh);

	SuckComponent = CreateDefaultSubobject<URadialForceComponent>("SuckComponent");
	SuckComponent->SetupAttachment(BaseMesh);

	ColliMesh = CreateDefaultSubobject<USphereComponent>("ColliMesh");
	ColliMesh->SetupAttachment(BaseMesh);

	SetReplicates(true);

	ColliMesh->OnComponentHit.AddDynamic(this,&ARGideon_Suck::OnSuckActorToCenter);
}

void ARGideon_Suck::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	bReplicates = true;
}
FTimerHandle SuckImpulse_TimerHandle;
// Called when the game starts or when spawned
void ARGideon_Suck::BeginPlay()
{
	Super::BeginPlay();

	
	FTimerDelegate SuckImpulse_TimerDelegate;
	SuckImpulse_TimerDelegate.BindUFunction(this,"SuckImpulse");
	GetWorld()->GetTimerManager().SetTimer(SuckImpulse_TimerHandle,SuckImpulse_TimerDelegate,0.03,true);
	FTimerHandle Destroy_Impulse;
	FTimerDelegate DestroyDelay_TimerDelegate;
	DestroyDelay_TimerDelegate.BindUFunction(this,"DestroyDelay");
	GetWorld()->GetTimerManager().SetTimer(Destroy_Impulse,DestroyDelay_TimerDelegate,0.2,true);
}

void ARGideon_Suck::SuckImpulse()
{
	GetWorldTimerManager().ClearTimer(SuckImpulse_TimerHandle);
	SuckComponent->FireImpulse();
}

void ARGideon_Suck::DestroyDelay()
{
	Destroy();
}

// Called every frame
void ARGideon_Suck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SuckComponent->FireImpulse();
}

void ARGideon_Suck::OnSuckActorToCenter(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ARCharacter* character = Cast<ARCharacter>(OtherActor);
	
	/*if (character)
	{
		character->SetCharacterSpeedShortly(0,0.2f);
	}*/
}

