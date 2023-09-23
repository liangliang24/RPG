// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RAction.h"
#include "RCharacter.h"
#include "RAction_ProjectileAttack.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URAction_ProjectileAttack : public URAction
{
	GENERATED_BODY()
public:
	URAction_ProjectileAttack();

protected:

	
	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> projectileClass;

	UPROPERTY(VisibleAnywhere,Category="Efects")
	FName handSocketName;

	UPROPERTY(EditDefaultsOnly, Category="Attack")
	float attackAnimDelay;

	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* attackAnim;

	UPROPERTY(EditAnywhere, Category="Attack")
	UParticleSystem* castingEffect;
	
	FTimerHandle primaryAttackHandle;

	UFUNCTION(Client,Reliable)
	void AttackDelay_Elasped(ARCharacter* instigator);
public:
	virtual void StartAction_Implementation(AActor* instigator) override;
	virtual void StopAction_Implementation(AActor* instigator) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAction_Implementation(AActor* instigator) override;
	virtual void ShowForAllClient_Implementation(AActor* instigator) override;
};
