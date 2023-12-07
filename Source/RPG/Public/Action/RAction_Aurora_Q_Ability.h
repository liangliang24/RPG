// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RAction.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RAction_Aurora_Q_Ability.generated.h"

class AAuroraIceSpawn;
class AGeneratedDynamicMeshActor;
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
	UFUNCTION(Server,Reliable)
	void SpawnIce(AActor* instigator);
	virtual void StartAction_Implementation(AActor* instigator) override;
	virtual void StopAction_Implementation(AActor* instigator) override;
	
	
protected:
	USkeletalMeshSocket const* Foot_R;
	USkeletalMeshComponent* InstigatorSkeletalMeshComponent;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> IceSpawn;
	
	FVector StartLocation;
	UPROPERTY(EditDefaultsOnly)
	float MoveLength;
	UPROPERTY(EditDefaultsOnly)
	float speed;
	FTimerHandle MoveHandle;
	FVector InstigatorUpVector;
	UPROPERTY(EditDefaultsOnly)
	float upspeed;
	UCharacterMovementComponent* InstigatorCharacterMovement;

	UFUNCTION()
	void MoveTick(AActor* Instigator);
	FVector InstigatorForwardVector;
	UPROPERTY(EditDefaultsOnly)
	float MoveDeltaTime; 
};


