// Fill out your copyright notice in the Description page of Project Settings.


#include "RAttributeComponent.h"

// Sets default values for this component's properties
URAttributeComponent::URAttributeComponent()
{

	health = 100.0f;
	maxHealth = 100.0f;
	// ...
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
