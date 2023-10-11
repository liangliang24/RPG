// Fill out your copyright notice in the Description page of Project Settings.


#include "Gideon/RGideon_Portal.h"

#include "Components/SphereComponent.h"

void ARGideon_Portal::Interact_Implementation(APawn* instigatorPawn)
{
	IRGameplayInterface::Interact_Implementation(instigatorPawn);
}

// Sets default values
ARGideon_Portal::ARGideon_Portal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Portal Mesh");
	RootComponent = BaseMesh;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARGideon_Portal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARGideon_Portal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

