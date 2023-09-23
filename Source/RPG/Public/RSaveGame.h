// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RSaveGame.generated.h"

USTRUCT()
struct FActorSaveData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FString actorName;

	UPROPERTY()
	FTransform transform;
};
/**
 * 
 */
UCLASS()
class RPG_API URSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()
	int credit;

	UPROPERTY()
	TArray<FActorSaveData> savedActors;
};
