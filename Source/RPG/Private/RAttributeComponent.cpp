// Fill out your copyright notice in the Description page of Project Settings.


#include "RAttributeComponent.h"

// Sets default values for this component's properties
URAttributeComponent::URAttributeComponent()
{

	health = 100.0f;
	maxHealth = 100.0f;
	// ...
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

bool URAttributeComponent::IsAlive() const
{
	return health>0;
}

bool URAttributeComponent::ApplyHealthChange(AActor* instigatorActor, float delta)
{
	
	health+=delta;
	health = FMath::Clamp(health,0,maxHealth);
	OnHealthChange.Broadcast(instigatorActor,this,health,delta);
	UE_LOG(LogTemp,Log,TEXT("Owner:%s Health:%f"),*GetNameSafe(GetOwner()),health);
	return true;
}

float URAttributeComponent::GetHealth()
{
	return health;
}
