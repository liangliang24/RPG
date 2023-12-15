// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RAction.h"
#include "RAction_Aurora_R_Ability.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URAction_Aurora_R_Ability : public URAction
{
	GENERATED_BODY()
public:
	URAction_Aurora_R_Ability();
	UFUNCTION(NetMulticast,Reliable)
	void SpawnDecalActor(AActor* instigator);
	UPROPERTY(EditDefaultsOnly)
	float DamageRadius;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URAction> ActionClass;
	UFUNCTION(Server,Reliable)
	void FireDamage(AActor* Instigator);
	virtual void StartAction_Implementation(AActor* instigator) override;
	UFUNCTION(NetMulticast,Reliable)
	void NetMulticast_StopDecalLogic();
	virtual void StopAction_Implementation(AActor* instigator) override;
	
	FVector TraceDecalSpawnLine(AActor* Actor);

	UDecalComponent* DecalActor;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* DecalMaterial;
	UPROPERTY(EditDefaultsOnly)
	FVector DecalSize;
	FTimerHandle SetDecalLocationHandle;

	UFUNCTION(NetMulticast,Reliable)
	void SetDecalLocation(AActor* Instigator);
};


