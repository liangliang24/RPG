// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/RAnimInstance.h"

#include "RAttributeComponent.h"
#include "RCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

URAnimInstance::URAnimInstance()
{
	FAction = false;
}

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

float URAnimInstance::SetSpeed()
{
	if (!PawnOwner)
	{
		return 0.0f;
	}
	return PawnOwner->GetVelocity().Length();
}

FRotator URAnimInstance::SetRotation()
{
	if (!PawnOwner)
	{
		return FRotator::ZeroRotator;
	}
	return UKismetMathLibrary::NormalizedDeltaRotator(PawnOwner->GetBaseAimRotation(),PawnOwner->GetActorRotation());
	
}

float URAnimInstance::SetYawDelta(float DeltaTime)
{
	if (!PawnOwner)
	{
		return 0.0f;
	}
	float Target =
		UKismetMathLibrary::NormalizedDeltaRotator(RotationLastTick,
			PawnOwner->GetActorRotation()).Yaw /
		DeltaTime / 10;

	return UKismetMathLibrary::FInterpTo(YawDelta,Target,DeltaTime,6);
}


FRotator URAnimInstance::SetRotationLastTick()
{
	if (!PawnOwner)
	{
		return FRotator::ZeroRotator;
	}
	return PawnOwner->GetActorRotation();
}

bool URAnimInstance::SetIsAcceleration()
{
	UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(OwnerCharacterMovement);

	if (MovementComponent)
	{
		return MovementComponent->GetCurrentAcceleration().Length() > 0;
	}

	return false;
}

bool URAnimInstance::SetFAction()
{
	ARCharacter* CharacterOwner = Cast<ARCharacter>(PawnOwner);
	if (CharacterOwner)
	{
		return CharacterOwner->PressF;
	}
	return false;
}

bool URAnimInstance::SetEAction()
{
	ARCharacter* CharacterOwner = Cast<ARCharacter>(PawnOwner);
	if (CharacterOwner)
	{
		return CharacterOwner->PressE;
	}
	return false;
}

bool URAnimInstance::SetQAction()
{
	ARCharacter* CharacterOwner = Cast<ARCharacter>(PawnOwner);
	if (CharacterOwner)
	{
		return CharacterOwner->PressQ;
	}
	return false;
}

bool URAnimInstance::SetRAction()
{
	ARCharacter* CharacterOwner = Cast<ARCharacter>(PawnOwner);
	if (CharacterOwner)
	{
		return CharacterOwner->PressR;
	}
	return false;
}

bool URAnimInstance::SetLeftButtonAction()
{
	ARCharacter* CharacterOwner = Cast<ARCharacter>(PawnOwner);
	if (CharacterOwner)
	{
		return CharacterOwner->PressLeftbutton;
	}
	return false;
}

bool URAnimInstance::CanESuccess()
{
	ARCharacter* CharacterOwner = Cast<ARCharacter>(PawnOwner);
	if (CharacterOwner)
	{
		return CharacterOwner->EResult;
	}
	return false;
}

bool URAnimInstance::CanQSuccess()
{
	ARCharacter* CharacterOwner = Cast<ARCharacter>(PawnOwner);
	if (CharacterOwner)
	{
		return CharacterOwner->QResult;
	}
	return false;
}
