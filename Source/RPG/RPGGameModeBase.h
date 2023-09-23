// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "RPGGameModeBase.generated.h"

class URSaveGame;
static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("rpg.SpawnBots"),false,TEXT("Enable spawning of bots via timer"),ECVF_Cheat);
static TAutoConsoleVariable<bool> CVarSpawnInteractor(TEXT("rpg.SpawnIterator"),false,TEXT("Enable spawning iterator"),ECVF_Default);
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

	void SpawnInterationTimerElasped();
	virtual void StartPlay() override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
protected:
	FString SlotName;
	
	UPROPERTY()
	URSaveGame* currentSaveGame;
	
	FTimerHandle timerHandle_SpawnInteration;
	
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
	
	float interationSpawnInRate;
	UPROPERTY(EditDefaultsOnly,Category="AI")
	UEnvQuery* spawnInterationQuery;


	UFUNCTION()
	void SpawnBotTimerElasped();
	
	UFUNCTION()
	void SpawnAIMinion(UEnvQueryInstanceBlueprintWrapper* EnvQueryInstanceBlueprintWrapper, EEnvQueryStatus::Type Arg);

	UFUNCTION()
	void RespawnPlayerElasped(AController* controller);

	
	UFUNCTION()
	void SpawnInteration(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AActor>> interationActors;
public:
	UFUNCTION(Exec)
	void KillAllAI();

	virtual void OnActorKill(AActor* victimActor,AActor* instigatorActor);

	UFUNCTION(BlueprintCallable,Category="SaveGame")
	void WriteSaveGame();

	void LoadSaveGame();

	void SetActorTransformFromSaved();
};


