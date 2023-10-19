// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RInputAbilityConfig.generated.h"

class UInputAction;
/**
 * 
 */
UCLASS()
class RPG_API URInputAbilityConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* PrimaryAttack;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* RightButtonSkill;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* E_Ability;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* F_Ability;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* Q_Ability;

	
	
	
};
