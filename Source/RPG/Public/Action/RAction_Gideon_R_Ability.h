// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RAction_Aim.h"
#include "RAction_Gideon_R_Ability.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URAction_Gideon_R_Ability : public URAction_Aim
{
	GENERATED_BODY()

public:
	URAction_Gideon_R_Ability();

	virtual void StartAction_Implementation(AActor* instigator) override;
	virtual void StopAction_Implementation(AActor* instigator) override;

protected:
	UPROPERTY(EditDefaultsOnly,Category="Animation")
	UAnimMontage* AnimStart;
	UPROPERTY(EditDefaultsOnly,Category="Animation")
	UAnimMontage* AnimLoop;
	
	UFUNCTION(NetMulticast,Reliable)
	void  NetMulticastAnimMontage(ACharacter* Instigator, UAnimMontage* AnimToPlay);
};
