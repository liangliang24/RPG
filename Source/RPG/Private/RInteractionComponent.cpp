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




// Called every frame
void URInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URInteractionComponent::PrimaryInteract()
{
	FHitResult hitResult;
	AActor* owner = GetOwner();
	FVector eyesLocation;
	FRotator eyesRotation;
	owner->GetActorEyesViewPoint(eyesLocation, eyesRotation);

	FVector end = eyesLocation + (eyesRotation.Vector() * 1000);
	FCollisionObjectQueryParams objectQueryParams;
	objectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	//GetWorld()->LineTraceSingleByObjectType(hitResult,eyesLocation,end,objectQueryParams);

	TArray<FHitResult> hits;
	FCollisionShape collisionShape;
	collisionShape.SetSphere(30);
	bool hitsuccess = GetWorld()->SweepMultiByObjectType(hits, eyesLocation, end, FQuat::Identity, objectQueryParams,
	                                                     collisionShape);
	
	AActor* hitActor = (hits.IsEmpty())?nullptr:hits[0].GetActor();
	if (hitActor)
	{
		if (hitActor->Implements<URGameplayInterface>())
		{
			APawn* instigatorPawn = Cast<APawn>(hitActor);

			IRGameplayInterface::Execute_Interact(hitActor, instigatorPawn);
			DrawDebugSphere(GetWorld(),hits[0].ImpactPoint,30,8,FColor::Purple,false,2,0,1);
		}
	}
	

	FColor debugLineColor = hitsuccess ? (FColor::Red) : (FColor::Green);
	DrawDebugLine(GetWorld(), eyesLocation, end, debugLineColor, false, 2, 0, 2);

	
}

