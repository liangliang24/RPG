// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RAIController.generated.h"

/**
 * NPC的AI控制器
 */
UCLASS()
class RPG_API ARAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	/*
	 * 此控制器运行的行为树（相当于AI的大脑）
	 */
	UPROPERTY(EditDefaultsOnly,Category = "AI")
	UBehaviorTree* behaviorTree;
	
	virtual void BeginPlay() override;

	
};
