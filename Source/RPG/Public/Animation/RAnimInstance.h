// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RAnimInstance.generated.h"

class UCharacterMovementComponent;
class URAttributeComponent;
/**
 * 
 */
UCLASS()
class RPG_API URAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,BlueprintPure)
	URAttributeComponent* SetAttributeComponent(APawn* pawn);
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	UPawnMovementComponent* SetCharacterMovementComponent(APawn* pawn);

	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool SetIsAlive();
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool SetIsStunned();
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool SetIsSprint();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool SetIsInAir();
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	float SetSpeed();
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	FRotator SetRotation();
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	float SetYawDelta(float DeltaTime);
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	FRotator SetRotationLastTick();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool SetIsAcceleration();

protected:

	UPROPERTY(BlueprintReadWrite,Category="Component")
	APawn* PawnOwner;
	
	UPROPERTY(BlueprintReadWrite,Category="Component")
	URAttributeComponent* OwnerAttributeComponent;

	UPROPERTY(BlueprintReadWrite,Category="Component")
	UPawnMovementComponent* OwnerCharacterMovement;
	
	UPROPERTY(BlueprintReadWrite,Category="CharacterInfo")
	float Speed;

	UPROPERTY(BlueprintReadWrite,Category="CharacterInfo")
	bool IsInAir;

	UPROPERTY(BlueprintReadWrite,Category="CharacterInfo")
	float Pitch;

	UPROPERTY(BlueprintReadWrite,Category="CharacterInfo")
	float Roll;

	UPROPERTY(BlueprintReadWrite,Category="CharacterInfo")
	float Yaw;
	
	UPROPERTY(BlueprintReadWrite,Category="CharacterInfo")
	float YawDelta;
	
	UPROPERTY(BlueprintReadWrite,Category="CharacterInfo")
	FRotator RotationLastTick;

	UPROPERTY(BlueprintReadWrite,Category="CharacterInfo")
	bool IsAccelerating;

	UPROPERTY(BlueprintReadWrite,Category="CharacterInfo")
	bool FullBody;

	UPROPERTY(BlueprintReadWrite,Category="CharacterState")
	bool IsAlive;

	UPROPERTY(BlueprintReadWrite,Category="CharacterState")
	bool IsStunned;

	UPROPERTY(BlueprintReadWrite,Category="CharacterState")
	bool IsSprinting;

private:
	
};
