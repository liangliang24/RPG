// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RAction.h"
#include "Engine/DataAsset.h"
#include "RMonsterData.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URMonsterData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="SpawnInfo")
	TSubclassOf<AActor> MonsterClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="SpawnInfo")
	TArray<TSubclassOf<URAction>> Actions;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="SpawnInfo")
	UTexture2D* Icon;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
