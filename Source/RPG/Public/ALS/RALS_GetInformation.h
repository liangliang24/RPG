// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RALS_GetInformation.generated.h"
enum class EMovementAction : uint8;
enum class EMovementState : uint8;
class ARCharacter;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URALS_GetInformation : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPG_API IRALS_GetInformation
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	static void GetCurrentALSInfo(ARCharacter* player,EMovementState& MovementState,EMovementAction& MovementAction);
};
