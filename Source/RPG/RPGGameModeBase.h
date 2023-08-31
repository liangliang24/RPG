// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "RPGGameModeBase.generated.h"

class UEnvQueryInstanceBlueprintWrapper;
class UEnvQuery;
/**
 * 游戏模式
 */
UCLASS()
class RPG_API ARPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ARPGGameModeBase();
	virtual void StartPlay() override;
protected:
	//生成AI的定时器句柄
	FTimerHandle timerHandle_SpawnBots;
	//生成AI的延迟
	float spawnTimerInterval;

	//AI生成的EQS
	UPROPERTY(EditDefaultsOnly,Category="AI")
	UEnvQuery* spawnBotQuery;

	//生成的AI
	UPROPERTY(EditDefaultsOnly,Category="AI")
	TSubclassOf<AActor> minion;

	//难度曲线，生成AI数量的根据
	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* difficultyCurve;
	
	UFUNCTION()
	void SpawnBotTimerElasped();
	
	UFUNCTION()
	void SpawnAIMinion(UEnvQueryInstanceBlueprintWrapper* EnvQueryInstanceBlueprintWrapper, EEnvQueryStatus::Type Arg);

	
};
