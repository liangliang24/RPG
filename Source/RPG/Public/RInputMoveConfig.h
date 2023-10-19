// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RInputMoveConfig.generated.h"

class UInputAction;
/**
 * 
 */
UCLASS()
class RPG_API URInputMoveConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* Forward;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* BackWard;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* Left;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* Right;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* Jump;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* TurnUp;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* TurnHorizon;
};
