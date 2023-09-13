// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RAction.h"
#include "RActionEffect.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URActionEffect : public URAction
{
	GENERATED_BODY()
public:
	URActionEffect();
		
	virtual void StartAction_Implementation(AActor* instigator) override;

	virtual void StopAction_Implementation(AActor* instigator) override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Effect")
	float duration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Effect")
	float period;

	FTimerHandle periodHandle;
	FTimerHandle durationHandle;

	UFUNCTION(BlueprintNativeEvent, Category="Effect")
	void ExecutePeriodicEffect(AActor* instigator);
};