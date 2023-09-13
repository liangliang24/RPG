// Fill out your copyright notice in the Description page of Project Settings.


#include "RActionEffect.h"

#include "RActionComponent.h"

void URActionEffect::ExecutePeriodicEffect_Implementation(AActor* instigator)
{
	
}

URActionEffect::URActionEffect()
{
	bAutoStart = true;
}

void URActionEffect::StartAction_Implementation(AActor* instigator)
{
	Super::StartAction_Implementation(instigator);

	if (duration > 0.0f)
	{
		FTimerDelegate delegate;
		delegate.BindUFunction(this,"StopAction", instigator);
		GetWorld()->GetTimerManager().SetTimer(durationHandle,delegate, duration, false);
	}

	if (period > 0.0f)
	{
		FTimerDelegate delegate;
		delegate.BindUFunction(this,"ExecutePeriodicEffect", instigator);
		GetWorld()->GetTimerManager().SetTimer(periodHandle, delegate, period, true);
	}
}

void URActionEffect::StopAction_Implementation(AActor* instigator)
{
	if (GetWorld()->GetTimerManager().GetTimerRemaining(periodHandle)< KINDA_SMALL_NUMBER)
	{
		ExecutePeriodicEffect(instigator);
	}
	
	Super::StopAction_Implementation(instigator);

	GetWorld()->GetTimerManager().ClearTimer(periodHandle);
	GetWorld()->GetTimerManager().ClearTimer(durationHandle);

	URActionComponent* comp = GetOwningComponent();
	if (comp)
	{
		comp->RemoveAction(this);
	}
}
