// Copyright Epic Games, Inc. All Rights Reserved.


#include "RPGGameModeBase.h"

#include "EnvironmentQuery/EnvQueryManager.h"

ARPGGameModeBase::ARPGGameModeBase()
{
	spawnTimerInterval = 2.0f;
}



void ARPGGameModeBase::StartPlay()
{
	Super::StartPlay();

	
	GetWorldTimerManager().SetTimer(timerHandle_SpawnBots,this,&ARPGGameModeBase::SpawnBotTimerElasped,spawnTimerInterval,true);
}




void ARPGGameModeBase::SpawnBotTimerElasped()
{
	UEnvQueryInstanceBlueprintWrapper* result = UEnvQueryManager::RunEQSQuery(this,spawnBotQuery,this,EEnvQueryRunMode::RandomBest5Pct,nullptr);
	if (ensure(result))
	{
		result->GetOnQueryFinishedEvent().AddDynamic(this,&ARPGGameModeBase::SpawnAIMinion);
	}
	
}

void ARPGGameModeBase::SpawnAIMinion(UEnvQueryInstanceBlueprintWrapper* EnvQueryInstanceBlueprintWrapper,
 	EEnvQueryStatus::Type Arg)
{
	if (Arg != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp,Warning,TEXT("Spawn bots failed"));
		return ;
	}
	TArray<FVector> locations = EnvQueryInstanceBlueprintWrapper->GetResultsAsLocations();

	if (locations.Num() > 0)
	{
		GetWorld()->SpawnActor<AActor>(minion,locations[0],FRotator::ZeroRotator);
	}
}
