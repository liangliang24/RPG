// Fill out your copyright notice in the Description page of Project Settings.


#include "RAttributeComponent.h"

// Sets default values for this component's properties
URAttributeComponent::URAttributeComponent()
{

	health = 100.0f;
	// ...
}

bool URAttributeComponent::ApplyHealthChange(float delta)
{
	health+=delta;

	UE_LOG(LogTemp,Log,TEXT("Owner:%s Health:%f"),*GetNameSafe(GetOwner()),health);
	return true;
}