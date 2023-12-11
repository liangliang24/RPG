// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RAction.h"
#include "RAction_Aurora_E_Ability.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URAction_Aurora_E_Ability : public URAction
{
	GENERATED_BODY()
public:
	URAction_Aurora_E_Ability();
	virtual void StartAction_Implementation(AActor* instigator) override;
	virtual void StopAction_Implementation(AActor* instigator) override;

protected:
	UPROPERTY(Replicated,BlueprintReadOnly)
	FVector SpawnCenter;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
