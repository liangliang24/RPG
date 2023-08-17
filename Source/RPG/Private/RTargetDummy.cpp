// Fill out your copyright notice in the Description page of Project Settings.


#include "RTargetDummy.h"

#include "RAttributeComponent.h"

// Sets default values
ARTargetDummy::ARTargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = staticMesh;

	attributeComp = CreateDefaultSubobject<URAttributeComponent>("AttributeComponent");
}

// Called when the game starts or when spawned
void ARTargetDummy::BeginPlay()
{
	Super::BeginPlay();
	
}



void ARTargetDummy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	attributeComp->OnHealthChange.AddDynamic(this,&ARTargetDummy::OnHealthChange);
}


void ARTargetDummy::OnHealthChange(AActor* InstigatorActor, URAttributeComponent* OwningComp, float NewHealth,
	float Delta)
{
	if (Delta < 0)
	{
		staticMesh->SetScalarParameterValueOnMaterials("TimeToHit",GetWorld()->TimeSeconds);
	}
	
}

// Called every frame
void ARTargetDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



