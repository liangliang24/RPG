// Fill out your copyright notice in the Description page of Project Settings.


#include "RAttributeComponent.h"

// Sets default values for this component's properties
URAttributeComponent::URAttributeComponent()
{

	health = 100.0f;
	maxHealth = 100.0f;
	// ...
}

bool URAttributeComponent::ApplyHealthChange(AActor* instigatorActor, float delta)
{
	
	health+=delta;

	if(health < 0) health = 0;
	if(health > maxHealth) health = maxHealth;
	OnHealthChange.Broadcast(instigatorActor,this,health,delta);
	UE_LOG(LogTemp,Log,TEXT("Owner:%s Health:%f"),*GetNameSafe(GetOwner()),health);
	return true;
}