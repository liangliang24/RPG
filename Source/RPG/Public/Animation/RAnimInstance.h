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
	URAnimInstance();
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

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool SetFAction();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool SetEAction();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool SetQAction();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool SetRAction();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool SetLeftButtonAction();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool CanESuccess();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool CanFSuccess();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool CanRSuccess();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool CanQSuccess();

	UPROPERTY(BlueprintReadWrite,Category="Component")
    APawn* PawnOwner;

protected:

	
	
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

	UPROPERTY(BlueprintReadWrite,Category="CharacterState")
	bool FAction;

	UPROPERTY(BlueprintReadWrite,Category="CharacterState")
	bool EAction;

	UPROPERTY(BlueprintReadWrite,Category="CharacterState")
	bool QAction;

	UPROPERTY(BlueprintReadWrite,Category="CharacterState")
	bool RAction;

	UPROPERTY(BlueprintReadWrite,Category="CharacterState")
	bool LeftButtonAction;

	UPROPERTY(BlueprintReadWrite,Category="CharacterResult")
	bool QResult;

	UPROPERTY(BlueprintReadWrite,Category="CharacterResult")
	bool EResult;

	UPROPERTY(BlueprintReadWrite,Category="CharacterResult")
	bool FResult;

	UPROPERTY(BlueprintReadWrite,Category="CharacterResult")
	bool RResult;

private:
	
};
