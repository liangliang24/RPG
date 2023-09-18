// Fill out your copyright notice in the Description page of Project Settings.


#include "RAction.h"

#include "RActionComponent.h"
#include "Net/UnrealNetwork.h"
#include "RPG/RPG.h"

void URAction::InitializeActionComp(URActionComponent* newActionComp)
{
	actionComp = newActionComp;
}

void URAction::StartAction_Implementation(AActor* instigator)
{
	//UE_LOG(LogTemp,Log,TEXT("Running:%s"),*GetNameSafe(instigator));
	LogOnScreen(this,FString::Printf(TEXT("Running:%s"),*GetNameSafe(instigator)),FColor::Green);
	URActionComponent* Comp = GetOwningComponent();

	Comp->activeGameplayTags.AppendTags(grantTags);

	bIsRunning = true;
	
}

void URAction::StopAction_Implementation(AActor* instigator)
{
	//UE_LOG(LogTemp,Log,TEXT("Stop:%s"),*GetNameSafe(instigator));
	LogOnScreen(this,FString::Printf(TEXT("Stop:%s"),*GetNameSafe(instigator)),FColor::White);
	//ensureAlways(bIsRunning);
	
	URActionComponent* Comp = GetOwningComponent();
	
	Comp->activeGameplayTags.RemoveTags(grantTags);

	bIsRunning = false;
}

URAction::URAction()
{
	bAutoStart = false;
}

URActionComponent* URAction::GetOwningComponent() const
{
	return actionComp;
}



bool URAction::IsRunning()
{
	return bIsRunning;
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

UWorld* URAction::GetWorld() const
{
	AActor* actor = Cast<AActor>(GetOuter());
	if (actor)
	{
		return actor->GetWorld();
	}
	return GetOuter()->GetWorld();
}

bool URAction::IsSupportedForNetworking() const
{
	return true;
}

void URAction::OnRep_IsRunning_Implementation()
{
	if (bIsRunning)
	{
		StartAction(nullptr);
	}
	else
	{
		StopAction(nullptr);
	}
}

void URAction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URAction,bIsRunning);
	DOREPLIFETIME(URAction,actionComp);
}


