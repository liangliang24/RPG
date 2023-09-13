// Fill out your copyright notice in the Description page of Project Settings.


#include "RAction.h"

#include "RActionComponent.h"

void URAction::StartAction_Implementation(AActor* instigator)
{
	UE_LOG(LogTemp,Log,TEXT("Running:%s"),*GetNameSafe(instigator));

	URActionComponent* Comp = GetOwningComponent();

	Comp->activeGameplayTags.AppendTags(grantTags);

	bIsRunning = true;
}

void URAction::StopAction_Implementation(AActor* instigator)
{
	UE_LOG(LogTemp,Log,TEXT("Stop:%s"),*GetNameSafe(instigator));

	ensureAlways(bIsRunning);
	
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
	return Cast<URActionComponent>(GetOuter());
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
	UActorComponent* comp = Cast<UActorComponent>(GetOuter());
	if (comp)
	{
		return comp->GetWorld();
	}
	return GetOuter()->GetWorld();
}
