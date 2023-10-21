// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RActionEffect.h"
#include "RAttributeComponent.h"
#include "RActionEffect_Thorns.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URActionEffect_Thorns : public URActionEffect
{
	GENERATED_BODY()
public:
	URActionEffect_Thorns();
	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* instigator) override;

	UFUNCTION()
	void OnOwnerHealthChanged(AActor* InstigatorActor, URAttributeComponent* OwningComp, float NewHealth, float Delta);
protected:
	virtual void ExecutePeriodicEffect_Implementation(AActor* instigator) override;

	UPROPERTY()
	URAttributeComponent* bindAttributeComp;
};


