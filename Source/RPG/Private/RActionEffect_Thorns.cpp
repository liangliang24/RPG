// Fill out your copyright notice in the Description page of Project Settings.


#include "RActionEffect_Thorns.h"

#include "RActionComponent.h"
#include "RAttributeComponent.h"


URActionEffect_Thorns::URActionEffect_Thorns()
{
	bAutoStart = false;
}

void URActionEffect_Thorns::StartAction_Implementation(AActor* Instigator)
{
	URActionComponent* actionComponent = GetOwningComponent();

	if (!actionComponent)
	{
		return ;
	}
	AActor* owner = actionComponent->GetOwner();
     
    if (!owner)
    {
     	return ;
    }

	bindAttributeComp = URAttributeComponent::GetAttributeComponent(owner);
	if (bindAttributeComp)
	{
		bindAttributeComp->OnHealthChange.AddDynamic(this,&URActionEffect_Thorns::OnOwnerHealthChanged);
	}

	FTimerHandle stop_TimerHandle;
	FTimerDelegate delegate;
	delegate.BindUFunction(this,"StopAction",Instigator);
	GetWorld()->GetTimerManager().SetTimer(stop_TimerHandle,delegate,10.0f,false);
}

void URActionEffect_Thorns::StopAction_Implementation(AActor* instigator)
{
	UE_LOG(LogTemp,Log,TEXT("Stop Thorns"));
	bindAttributeComp->OnHealthChange.RemoveDynamic(this,&URActionEffect_Thorns::OnOwnerHealthChanged);

	bindAttributeComp = nullptr;
}

void URActionEffect_Thorns::ExecutePeriodicEffect_Implementation(AActor* instigator)
{
	
}

void URActionEffect_Thorns::OnOwnerHealthChanged(AActor* InstigatorActor, URAttributeComponent* OwningComp, float NewHealth,
                                                 float Delta)
{
	if (!InstigatorActor||!OwningComp)
	{
		return ;
		
	}

	if (InstigatorActor == OwningComp->GetOwner())
	{
		return ;
	}
	
	
	URAttributeComponent* instigatorAttributeComp = URAttributeComponent::GetAttributeComponent(InstigatorActor);

	if (instigatorAttributeComp)
	{
		instigatorAttributeComp->ApplyHealthChange(InstigatorActor,(int)Delta);
	}
	
	
}
