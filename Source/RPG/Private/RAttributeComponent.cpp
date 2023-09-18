// Fill out your copyright notice in the Description page of Project Settings.


#include "RAttributeComponent.h"

#include "Net/UnrealNetwork.h"
#include "RPG/RPGGameModeBase.h"

// Sets default values for this component's properties
URAttributeComponent::URAttributeComponent()
{

	health = 100.0f;
	maxHealth = 100.0f;
	credit = 0.0f;
	rage = 0;
	haveRage = true;
	// ...

	SetIsReplicatedByDefault(true);
}

URAttributeComponent* URAttributeComponent::GetAttributeComponent(AActor* targetActor)
{
	return targetActor?Cast<URAttributeComponent>(targetActor->GetComponentByClass(URAttributeComponent::StaticClass())):nullptr;
}

bool URAttributeComponent::GetActorAlive(AActor* targetActor)
{
	if(targetActor)
	{
		return GetAttributeComponent(targetActor)->IsAlive();
	}
	UE_LOG(LogTemp,Log,TEXT("%s no AttributeComponent"),*GetNameSafe(targetActor));
	return false;
}


void URAttributeComponent::MulticastHealthChanged_Implementation(AActor* instigatorActor, float newHealth, float delta)
{
	OnHealthChange.Broadcast(instigatorActor,this,newHealth,delta);
}

bool URAttributeComponent::IsAlive() const
{
	return health>0;
}

bool URAttributeComponent::ApplyHealthChange(AActor* instigatorActor, float delta)
{
	if (health <= 0)
	{
		return false;
	}
	if (delta < 0)
	{
		delta*=CVarDamageMultiplier.GetValueOnGameThread();
	}
	health+=delta;
	health = FMath::Clamp(health,0,maxHealth);
	MulticastHealthChanged(instigatorActor,health,delta);
	//OnHealthChange.Broadcast(instigatorActor,this,health,delta);
	UE_LOG(LogTemp,Log,TEXT("Owner:%s Health:%f"),*GetNameSafe(GetOwner()),health);
	if(health <= 0)
	{
		ARPGGameModeBase* GM = GetWorld()->GetAuthGameMode<ARPGGameModeBase>();
		if(GM)
		{
			GM->OnActorKill(GetOwner(),instigatorActor);
		}
	}
	return true;
}

bool URAttributeComponent::ApplyCreditChange(AActor* instigatorActor, int delta)
{
	if (credit + delta < 0)
	{
		return false;
	}
	credit+=delta;
	
	OnCreditChanged.Broadcast(instigatorActor, this, credit, delta);

	return true;
}

bool URAttributeComponent::ApplyRageChange(AActor* instigatorActor, int delta)
{
	
	if (!haveRage)
	{
		return false;
	}

	if (rage + delta < 0)
	{
		return false;
	}
	rage+=delta;
	rage = FMath::Clamp(rage,0,100);
	OnRageChanged.Broadcast(instigatorActor,this,rage,delta);
	return true;
}

float URAttributeComponent::GetHealth()
{
	return health;
}

bool URAttributeComponent::Kill()
{
	return ApplyHealthChange(nullptr,-maxHealth);
}

void URAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URAttributeComponent,health);
	DOREPLIFETIME(URAttributeComponent,maxHealth);

	//DOREPLIFETIME_CONDITION(URAttributeComponent,maxHealth,COND_OwnerOnly)

	//DOREPLIFETIME(URAttributeComponent,credit);
}