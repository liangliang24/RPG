// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RAction.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RAction_Aurora_Q_Ability.generated.h"

class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class RPG_API URAction_Aurora_Q_Ability : public URAction
{
	GENERATED_BODY()
	
public:
	URAction_Aurora_Q_Ability();
	virtual void StartAction_Implementation(AActor* instigator) override;
	virtual void StopAction_Implementation(AActor* instigator) override;
	
	
protected:
	FVector StartLocation;
	UPROPERTY(EditDefaultsOnly)
	float MoveLength;
	UPROPERTY(EditDefaultsOnly)
	float speed;
	FTimerHandle MoveHandle;
	UFUNCTION()
	void MoveTick(AActor* Instigator, UCharacterMovementComponent* InstigatorCharacterMovement);
	FVector InstigatorForwardVector;
	UPROPERTY(EditDefaultsOnly)
	float MoveDeltaTime; 
};


