// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RAction.h"
#include "RAction_AuroraPrimaryAttack.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URAction_AuroraPrimaryAttack : public URAction
{
	GENERATED_BODY()
public:
	URAction_AuroraPrimaryAttack();
	virtual void StartAction_Implementation(AActor* instigator) override;
	virtual void StopAction_Implementation(AActor* instigator) override;
protected:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* PrimaryAttackMontage;

	UFUNCTION(NetMulticast,Reliable)
	void NetMultiCastAnimation(ACharacter* Instigator);
	
	FName WeaponSword_Base;
	FName WeaponSword_Mid;
	FName WeaponSword_Tip;
};
