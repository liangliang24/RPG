// Fill out your copyright notice in the Description page of Project Settings.


#include "RActionComponent.h"

#include "RAction.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"
#include "RPG/RPG.h"

DECLARE_CYCLE_STAT(TEXT("StartActionByName"), STAT_StartActionByName, STATGROUP_RPG);
// Sets default values for this component's properties
URActionComponent::URActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
	// ...
}

void URActionComponent::ServerStopAction_Implementation(AActor* instigator, URAction* action)
{
	action->StopAction(instigator);
	OnActionStoped.Broadcast(this,action);
}

void URActionComponent::AddAction(TSubclassOf<URAction> actionClass, AActor* instigator)
{
	if (!ensure(actionClass))
	{
		return ;
	}

	URAction* newAction = NewObject<URAction>(GetOwner(),actionClass);

	if (ensure(newAction))
	{
		newAction->InitializeActionComp(this);
		actions.Add(newAction);
		if (newAction->bAutoStart&&ensure(newAction->CanStart(instigator)))
		{
			newAction->StartAction(instigator);
		}
	}
	
}

bool URActionComponent::StartActionByName(AActor* instigator, FName actionName)
{
	SCOPE_CYCLE_COUNTER(STAT_StartActionByName);
	for (URAction* action:actions)
	{
		if (action&&action->ActionName == actionName)
		{
			if(action->CanStart(instigator))
			{
				if (action->hasPreAction)
				{
					action->PreAction(instigator);
				}
				OnActionStarted.Broadcast(this,action);
				ServerStartAction(instigator,action);
				
				TRACE_BOOKMARK(TEXT("StartAction::%s"), *GetNameSafe(action));
				//action->StartAction(instigator);
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
		if (action&&action->ActionName == actionName)
		{
			ServerStopAction(instigator,action);
			/*if (action->IsRunning())
			{
				action->StopAction(instigator);
                return true;
			}*/
			
		}
	}
	return false;
}

void URActionComponent::RemoveAction(URAction* action)
{
	if (!ensure(action&&!action->IsRunning()))
	{
		return ;
	}
	
	actions.Remove(action);
}



void URActionComponent::ServerStartAction_Implementation(AActor* instigator, URAction* action)
{
	
	action->StartAction(instigator);
	
	
}


// Called when the game starts
void URActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (GetOwner()->HasAuthority())
	{
		for (TSubclassOf<URAction> actionClass:defaultActions)
        {
        	AddAction(actionClass, GetOwner());
        }
	}
	
}


void URActionComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URActionComponent, actions);
	DOREPLIFETIME(URActionComponent, activeGameplayTags);
}

// Called every frame
void URActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	// ...

	/*for (URAction* action:actions)
	{
		FColor textColor = action->IsRunning() ? FColor::Blue : FColor::White;

		FString actionMsg = FString::Printf(TEXT("[%s] Action: %s : IsRunning: %s : Outer: %s"),
			*GetNameSafe(GetOwner()),
			*action->actionName.ToString(),
			action->IsRunning() ? TEXT("True") : TEXT("False"),
			*GetNameSafe(action->GetOuter()));

		LogOnScreen(this,actionMsg,textColor, 0.0f);
	}*/
}

bool URActionComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch,
	FReplicationFlags* RepFlags)
{
	bool wroteSth = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	for (URAction* action:actions)
	{
		if (action)
		{
			wroteSth |= Channel->ReplicateSubobject(action,*Bunch,*RepFlags);
		}
	}

	return wroteSth;
}