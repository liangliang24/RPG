// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeometryActors/GeneratedDynamicMeshActor.h"
#include "GeometryActors/GeneratedDynamicMeshActor.h"
#include "AuroraIceSpawn.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API AAuroraIceSpawn : public AGeneratedDynamicMeshActor
{
	GENERATED_BODY()
public:
	AAuroraIceSpawn();
	UPROPERTY(BlueprintReadOnly)
	float xLenth;
};
