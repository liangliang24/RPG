// Fill out your copyright notice in the Description page of Project Settings.


#include "RInteractionComponent.h"

#include "RGameplayInterface.h"

// Sets default values for this component's properties
URInteractionComponent::URInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void URInteractionComponent::PrimaryInteract()
{
	FHitResult hitResult;
	AActor* owner = GetOwner();
	FVector eyesLocation;
	FRotator eyesRotation;
	owner->GetActorEyesViewPoint(eyesLocation,eyesRotation);
	
	FVector end = eyesLocation + (eyesRotation.Vector()*1000);
	FCollisionObjectQueryParams objectQueryParams;
	objectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	GetWorld()->LineTraceSingleByObjectType(hitResult,eyesLocation,end,objectQueryParams);

	AActor* hitActor = hitResult.GetActor();
	if (hitActor)
	{
		if(hitActor->Implements<URGameplayInterface>())
		{
			APawn* instigatorPawn = Cast<APawn>(hitActor);

			IRGameplayInterface::Execute_Interact(hitActor,instigatorPawn);
		}
	}
}


// Called every frame
void URInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

;