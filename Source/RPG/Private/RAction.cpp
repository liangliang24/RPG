// Fill out your copyright notice in the Description page of Project Settings.


#include "RAction.h"

#include "RActionComponent.h"
#include "Net/UnrealNetwork.h"
#include "RPG/RPG.h"




void URAction::InitializeActionComp(URActionComponent* newActionComp)
{
	actionComp = newActionComp;
}


void URAction::PreAction_Implementation(AActor* instigatorActor)
{
	
}

void URAction::StartAction_Implementation(AActor* instigator)
{
	//UE_LOG(LogTemp,Log,TEXT("Running:%s"),*GetNameSafe(instigator));
	//LogOnScreen(this,FString::Printf(TEXT("Running:%s"),*GetNameSafe(instigator)),FColor::Green);
	URActionComponent* Comp = GetOwningComponent();

	Comp->activeGameplayTags.AppendTags(grantTags);

	repData.bIsRunning = true;
	repData.instigator = instigator;
	
}

void URAction::StopAction_Implementation(AActor* instigator)
{
	//UE_LOG(LogTemp,Log,TEXT("Stop:%s"),*GetNameSafe(instigator));
	//LogOnScreen(this,FString::Printf(TEXT("Stop:%s"),*GetNameSafe(instigator)),FColor::White);
	//ensureAlways(bIsRunning);
	
	URActionComponent* Comp = GetOwningComponent();
	
	Comp->activeGameplayTags.RemoveTags(grantTags);

	repData.bIsRunning = false;
}

URAction::URAction()
{
	bAutoStart = false;
	hasPreAction = false;
	
}

URActionComponent* URAction::GetOwningComponent() const
{
	return actionComp;
}



bool URAction::IsRunning()
{
	return repData.bIsRunning;
}

bool URAction::CanStart_Implementation(AActor* instigator)
{
	URActionComponent* comp = GetOwningComponent();

	if (comp->activeGameplayTags.HasAny(blockedTags)||IsRunning())
	{
		return false;
	}

	return true;
}

void URAction::ShowForAllClient_Implementation(AActor* instigator)
{
}

UWorld* URAction::GetWorld() const
{
	AActor* actor = Cast<AActor>(GetOuter());
	if (actor)
	{
		return actor->GetWorld();
	}
	return nullptr;
}

bool URAction::IsSupportedForNetworking() const
{
	return true;
}



void URAction::OnRep_RepData_Implementation()
{
	if (repData.bIsRunning)
	{
		StartAction(repData.instigator);
	}
	else
	{
		StopAction(repData.instigator);
	}
}

void URAction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URAction,repData);
	DOREPLIFETIME(URAction,actionComp);
}


