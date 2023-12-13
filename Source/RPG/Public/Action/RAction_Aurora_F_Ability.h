// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RAction.h"
#include "RAction_Aurora_F_Ability.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URAction_Aurora_F_Ability : public URAction
{
	GENERATED_BODY()
public:
	URAction_Aurora_F_Ability();
	virtual void StartAction_Implementation(AActor* instigator) override;
	virtual void StopAction_Implementation(AActor* instigator) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	float power;

	FVector SpawnLocation;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> IceAurora;
};
