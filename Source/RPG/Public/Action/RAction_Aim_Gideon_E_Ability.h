// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/RAction_Aim.h"
#include "RAction_Aim_Gideon_E_Ability.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URAction_Aim_Gideon_E_Ability : public URAction_Aim
{
	GENERATED_BODY()

public:
	URAction_Aim_Gideon_E_Ability();
	virtual void StartAction_Implementation(AActor* instigator) override;
	virtual void StopAction_Implementation(AActor* instigator) override;

	
protected:
	UFUNCTION(Server,Reliable)
	void SpawnBlackHole();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> BlackHole;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* SpawnAnimMontage;

	UFUNCTION(NetMulticast,Reliable)
	void NetMulticastAnimMontage(ARCharacter* Instigator);
private:
	
};
