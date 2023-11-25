// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RAction_Aim.h"
#include "RAction_Gideon_R_Ability.generated.h"

class UCapsuleComponent;
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
	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* BlackHole;
	UPROPERTY(EditDefaultsOnly,Category="Animation")
	UAnimMontage* AnimStart;
	UPROPERTY(EditDefaultsOnly,Category="Animation")
	UAnimMontage* AnimLoop;
	FTimerHandle DamageRepeatlyHandle;
	UFUNCTION(NetMulticast,Reliable)
	void NetMulticastAnimMontage(ACharacter* Instigator, UAnimMontage* AnimToPlay);
	UFUNCTION(NetMulticast,Reliable)
	void NetMulticastEmitter(FVector SpawnLocation);
	UFUNCTION()
	void DamageRepeatly(ACharacter* Instigator);

	UFUNCTION()
	void StopDamage();
};


