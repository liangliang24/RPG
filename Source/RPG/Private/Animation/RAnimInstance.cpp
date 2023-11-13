// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/RAnimInstance.h"

#include "RAttributeComponent.h"

URAttributeComponent* URAnimInstance::SetAttributeComponent(APawn* pawn)
{
	if (!pawn)
	{
		return nullptr;
	}
	URAttributeComponent* AttributeComp = Cast<URAttributeComponent>(pawn->GetComponentByClass(URAttributeComponent::StaticClass()));

	if (AttributeComp)
	{
		return AttributeComp;
	}
	return nullptr;
}

bool URAnimInstance::SetIsAlive(APawn* pawn)
{
	if (ensure(OwnerAttributeComponent))
	{
		
		return OwnerAttributeComponent->IsAlive();
		
	}
	return false;
}
