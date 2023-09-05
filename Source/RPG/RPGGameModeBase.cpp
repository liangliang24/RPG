// Copyright Epic Games, Inc. All Rights Reserved.


#include "RPGGameModeBase.h"

#include "EngineUtils.h"
#include "RAttributeComponent.h"
#include "RCharacter.h"
#include "RWorldUserWidget.h"
#include "AI/RAICharacter.h"
#include "Blueprint/UserWidget.h"
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
	if (!CVarSpawnBots.GetValueOnGameThread())
	{
		UE_LOG(LogTemp,Log,TEXT("CvarSpawnBots is false"));
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
	
	
	if(difficultyCurve)
	{
		if(difficultyCurve->GetFloatValue(GetWorld()->TimeSeconds) < existBots) return ;
	}
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
	

	
	TArray<FVector> locations = EnvQueryInstanceBlueprintWrapper->GetResultsAsLocations();
	if (locations.Num() > 0)
	{
		GetWorld()->SpawnActor<AActor>(minion,locations[0],FRotator::ZeroRotator);
	}
}

void ARPGGameModeBase::RespawnPlayerElasped(AController* controller)
{
	if (ensure(controller))
	{
		controller->UnPossess();
		RestartPlayer(controller);
		/*URWorldUserWidget* UI = Cast<URWorldUserWidget>(CreateWidget<URWorldUserWidget>(GetWorld(),mainHUD));
		if (ensure(UI))
		{
			UI->AddToViewport();
		}*/
	}
}

void ARPGGameModeBase::KillAllAI()
{
	for (TActorIterator<ARAICharacter> it(GetWorld());it;++it)
	{
		ARAICharacter* AI = *it;
		
		
		if (AI)
		{
			URAttributeComponent* AIAttributeComp = URAttributeComponent::GetAttributeComponent(AI);
			if(AIAttributeComp)
			{
				AIAttributeComp->Kill();
			}
		}
	}
}

void ARPGGameModeBase::OnActorKill(AActor* victimActor, AActor* instigatorActor)
{
	ARCharacter* player = Cast<ARCharacter>(victimActor);
	if (player)
	{
		FTimerHandle timerHandle_RespawnDelay;
		FTimerDelegate delegate;
		//AController* controller = Cast<AController>(PlayerControllerClass);
		delegate.BindUFunction(this,"RespawnPlayerElasped",player->GetController());
		UE_LOG(LogTemp,Log,TEXT("Restart Player:%s,controller:%s"),*GetNameSafe(player),*GetNameSafe(player->GetController()));
		GetWorldTimerManager().SetTimer(timerHandle_RespawnDelay,delegate,2.0f,false);
	}
	
}
