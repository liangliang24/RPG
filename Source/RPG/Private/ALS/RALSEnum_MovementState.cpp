// Fill out your copyright notice in the Description page of Project Settings.


#include "ALS/RALSEnum_MovementState.h"

URALSEnum_MovementState::URALSEnum_MovementState()
{
	DisplayNameMap.Add(FName("None"));
	DisplayNameMap.Add(FName("Grounded"));
	DisplayNameMap.Add(FName("In Air"));
	DisplayNameMap.Add(FName("Mantling"));
	DisplayNameMap.Add(FName("Ragdoll"));
	
}
