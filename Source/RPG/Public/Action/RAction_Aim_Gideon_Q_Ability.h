// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/RAction_Aim.h"
#include "RAction_Aim_Gideon_Q_Ability.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URAction_Aim_Gideon_Q_Ability : public URAction_Aim
{
	GENERATED_BODY()
public:
	URAction_Aim_Gideon_Q_Ability();

	virtual void StartAction_Implementation(AActor* instigator) override;
	UFUNCTION()
	void SpawnMeteor();
	virtual void StopAction_Implementation(AActor* instigator) override;

	UFUNCTION(NetMulticast,Reliable)
	void NetMulticastAnimMontage(ARCharacter* Instigator);

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AnimMontage;
protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> Damage_Meteor;
	
	virtual void AbilitySuccess_Implementation() override;
private:
};
