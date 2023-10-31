// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RALS_GetInfo.generated.h"

class ARCharacter;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URALS_GetInfo : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPG_API IRALS_GetInfo
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void GetALSInfo(ARCharacter* player,EMovementState& MovementState,EMovementAction& MovementAction,EGait& Gait);
};
