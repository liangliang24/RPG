// Copyright Epic Games, Inc. All Rights Reserved.


#include "RPGGameModeBase.h"

#include "EngineUtils.h"
#include "RAttributeComponent.h"
#include "AI/RAICharacter.h"
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
    	//UE_LOG(LogTemp,Log,TEXT("Spawn AI"));
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
	

	int existBots = 0;
	for(TActorIterator<ARAICharacter> it(GetWorld());it;++it)
	{
		ARAICharacter* AI = *it;
		URAttributeComponent* attributeComp = Cast<URAttributeComponent>(AI->GetComponentByClass(URAttributeComponent::StaticClass()));
		if (attributeComp&&attributeComp->IsAlive())
		{
			existBots++;
		}
	}
	UE_LOG(LogTemp,Log,TEXT("AI Nums:%d"),existBots);
	TArray<FVector> locations = EnvQueryInstanceBlueprintWrapper->GetResultsAsLocations();
	
	if(difficultyCurve)
	{
		if(difficultyCurve->GetFloatValue(GetWorld()->TimeSeconds) < existBots) return ;
	}
	if (locations.Num() > 0)
	{
		GetWorld()->SpawnActor<AActor>(minion,locations[0],FRotator::ZeroRotator);
	}
}
