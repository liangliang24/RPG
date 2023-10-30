// Fill out your copyright notice in the Description page of Project Settings.


#include "ALS/RALS_GetInformation.h"

#include "RCharacter.h"

// Add default functionality here for any IRALS_GetInformation functions that are not pure virtual.
void IRALS_GetInformation::GetCurrentALSInfo(ARCharacter* player, EMovementState& MovementState,
	EMovementAction& MovementAction)
{
	MovementState = player->MovementState;
	MovementAction = player->MovementAction;
}
