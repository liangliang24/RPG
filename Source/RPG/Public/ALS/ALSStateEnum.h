#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	ALS_MovementState_None UMETA(DisplayName = "None"),
	ALS_MovementState_Grounded UMETA(DisplayName = "Grounded"),
	ALS_MovementState_InAir UMETA(DisplayName = "InAir"),
	ALS_MovementState_Mantling UMETA(DispalyName = "Mantling"),
	ALS_MovementState_Ragdoll UMETA(DisplayName = "Ragdoll")
};

UENUM(BlueprintType)
enum class EMovementAction : uint8
{
	ALS_MovementAction_None UMETA(DisplayName = "None"),
	ALS_MovementAction_Jump UMETA(DisplayName = "Jump")
};