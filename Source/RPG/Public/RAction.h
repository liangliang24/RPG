// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RPG_API URAction : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent,Category="Action")
	void StartAction(AActor* instigator);

	UFUNCTION(BlueprintNativeEvent,Category="Action")
	void StopAction(AActor* instigator);
	
	UPROPERTY(EditDefaultsOnly, Category="Action")
	FName actionName;

	virtual UWorld* GetWorld() const override;
};
