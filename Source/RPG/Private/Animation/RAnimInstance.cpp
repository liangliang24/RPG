// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/RAnimInstance.h"

#include "RAttributeComponent.h"
#include "GameFramework/PawnMovementComponent.h"

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

UPawnMovementComponent* URAnimInstance::SetCharacterMovementComponent(APawn* pawn)
{
	if (!pawn)
	{
		return nullptr;
	}
	
	return pawn->GetMovementComponent();
}

bool URAnimInstance::SetIsAlive()
{
	if (OwnerAttributeComponent)
	{
		return OwnerAttributeComponent->IsAlive();
	}
	return false;
}

bool URAnimInstance::SetIsStunned()
{
	if (OwnerAttributeComponent)
	{
		return OwnerAttributeComponent->IsStunned();
	}
	return false;
}

bool URAnimInstance::SetIsSprint()
{
	if (OwnerAttributeComponent)
	{
		return OwnerAttributeComponent->IsSprintting();
	}
	return false;
}

bool URAnimInstance::SetIsInAir()
{
	if (OwnerCharacterMovement)
	{
		return OwnerCharacterMovement->IsFalling();
	}

	return false;
}

bool URAnimInstance::SetSpeed()
{
	
}

bool URAnimInstance::SetPitch()
{
}

bool URAnimInstance::SetYaw()
{
}

bool URAnimInstance::SetRoll()
{
}
