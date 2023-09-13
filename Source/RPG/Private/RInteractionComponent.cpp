// Fill out your copyright notice in the Description page of Project Settings.


#include "RInteractionComponent.h"

#include "RAttributeComponent.h"
#include "RGameplayInterface.h"
#include "RWorldUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"

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

void URInteractionComponent::FindBestToInteract()
{
	AActor* owner = GetOwner();
	UCameraComponent* ownerCameraComp = Cast<UCameraComponent>(owner->GetComponentByClass(UCameraComponent::StaticClass()));
	FVector eyesLocation;
	FRotator eyesRotation;
	if(ownerCameraComp)
	{
		eyesLocation = ownerCameraComp->GetComponentLocation();
		eyesRotation = ownerCameraComp->GetComponentRotation();
	}
	else
	{
		owner->GetActorEyesViewPoint(eyesLocation, eyesRotation);
	}
	
	FVector end = eyesLocation + (eyesRotation.Vector() * 1000);
	FCollisionObjectQueryParams objectQueryParams;
	objectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	//GetWorld()->LineTraceSingleByObjectType(hitResult,eyesLocation,end,objectQueryParams);

	TArray<FHitResult> hits;
	FCollisionShape collisionShape;
	collisionShape.SetSphere(30);
	bool hitsuccess = GetWorld()->SweepMultiByObjectType(hits, eyesLocation, end, FQuat::Identity, objectQueryParams,
	                                                     collisionShape);
	
	FocusActor = nullptr;
	for (FHitResult i:hits)
	{
		AActor* hitActor = i.GetActor();
		if (hitActor)
		{
			if (hitActor->Implements<URGameplayInterface>())
			{
				FocusActor = hitActor;
				
				if (CVarDebugDrawInteraction.GetValueOnGameThread())
					DrawDebugSphere(GetWorld(),hits[0].ImpactPoint,30,8,FColor::Purple,false,2,0,1);

				break;
			}
		}
	}

	if (FocusActor)
	{
		if (defaultWidgetClass&&defaultWidgetInstance==nullptr)
		{
			defaultWidgetInstance = CreateWidget<URWorldUserWidget>(GetWorld(),defaultWidgetClass);
		}

		if (defaultWidgetInstance)
		{
			defaultWidgetInstance->attachedActor = FocusActor;

			if (!defaultWidgetInstance->IsInViewport())
			{
				defaultWidgetInstance->AddToViewport();
			}
			
		}
	}
	else
	{
		if (defaultWidgetInstance)
		{
			defaultWidgetInstance->RemoveFromParent();
		}
	}
	
	if (CVarDebugDrawInteraction.GetValueOnGameThread())
	{
		FColor debugLineColor = hitsuccess ? (FColor::Red) : (FColor::Green);
		DrawDebugLine(GetWorld(), eyesLocation, end, debugLineColor, false, 2, 0, 2);
	}
}


// Called every frame
void URInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FindBestToInteract();
	// ...
}

void URInteractionComponent::PrimaryInteract()
{
	if (FocusActor == nullptr)
	{
		return ;
	}
	APawn* instigatorPawn = Cast<APawn>(GetOwner());

				
	IRGameplayInterface::Execute_Interact(FocusActor, instigatorPawn);
	UE_LOG(LogTemp,Log,TEXT("Interaction:%s"),*GetNameSafe(FocusActor));
}

