// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RAIController.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API ARAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly,Category = "AI")
	UBehaviorTree* behaviorTree;
	
	virtual void BeginPlay() override;

	
};
