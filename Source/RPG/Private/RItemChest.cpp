// Fill out your copyright notice in the Description page of Project Settings.


#include "RItemChest.h"

#include "RAttributeComponent.h"


// Sets default values
ARItemChest::ARItemChest() : opened(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>("baseMesh");
	RootComponent = baseMesh;

	lidMesh = CreateDefaultSubobject<UStaticMeshComponent>("lidMesh");
	lidMesh->SetupAttachment(baseMesh);
}

// Called when the game starts or when spawned
void ARItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARItemChest::Interact_Implementation(APawn* instigatorPawn)
{
	IRGameplayInterface::Interact_Implementation(instigatorPawn);
	URAttributeComponent* pawnAttributeComp = URAttributeComponent::GetAttributeComponent(instigatorPawn);
	if (pawnAttributeComp)
	{
		if(pawnAttributeComp->ApplyCreditChange(instigatorPawn, -50))
		{
			lidMesh->SetRelativeRotation(FRotator((opened)?(0):(110),0,0));
		}
	}
	

	opened = !opened;
}

