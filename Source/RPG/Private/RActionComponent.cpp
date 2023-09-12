// Fill out your copyright notice in the Description page of Project Settings.


#include "RActionComponent.h"

#include "RAction.h"

void URActionComponent::AddAction(TSubclassOf<URAction> actionClass)
{
	if (!ensure(actionClass))
	{
		return ;
	}

	URAction* newAction = NewObject<URAction>(this,actionClass);

	if (ensure(newAction))
	{
		actions.Add(newAction);
	}
	
}

bool URActionComponent::StartActionByName(AActor* instigator, FName actionName)
{
	for (URAction* action:actions)
	{
		if (action&&action->actionName == actionName)
		{
			if(action->CanStart(instigator))
			{
				action->StartAction(instigator);
				return true;
			}
		}
	}
	return false;
}

bool URActionComponent::StopActionByName(AActor* instigator, FName actionName)
{
	for (URAction* action:actions)
	{
		if (action&&action->actionName == actionName)
		{
			if (action->IsRunning())
			{
				action->StopAction(instigator);
                return true;
			}
			
		}
	}
	return false;
}

// Sets default values for this component's properties
URActionComponent::URActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	for (TSubclassOf<URAction> actionClass:defaultActions)
	{
		AddAction(actionClass);
	}
}


// Called every frame
void URActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

