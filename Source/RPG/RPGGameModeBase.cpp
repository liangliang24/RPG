// Copyright Epic Games, Inc. All Rights Reserved.


#include "RPGGameModeBase.h"

#include "EngineUtils.h"
#include "RActionComponent.h"
#include "RAttributeComponent.h"
#include "RCharacter.h"
#include "RGameplayInterface.h"
#include "RMonsterData.h"
#include "RPG.h"
#include "RPlayerState.h"
#include "RSaveGame.h"
#include "RWorldUserWidget.h"
#include "AI/RAICharacter.h"
#include "Blueprint/UserWidget.h"
#include "Engine/AssetManager.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "GameFramework/GameState.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

ARPGGameModeBase::ARPGGameModeBase()
{
	spawnTimerInterval = 2.0f;
	interationSpawnInRate = 10.0f;

	SlotName = "SaveGame";
}




void ARPGGameModeBase::StartPlay()
{
	Super::StartPlay();

	SetActorTransformFromSaved();
	
	GetWorldTimerManager().SetTimer(timerHandle_SpawnBots,this,&ARPGGameModeBase::SpawnBotTimerElasped,spawnTimerInterval,true);

	GetWorldTimerManager().SetTimer(timerHandle_SpawnInteration,this,&ARPGGameModeBase::SpawnInterationTimerElasped,interationSpawnInRate,true);
}

void ARPGGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	LoadSaveGame();
}

void ARPGGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	
	ARPlayerState* playerState = NewPlayer->GetPlayerState<ARPlayerState>();
	if (playerState)
	{
		playerState->LoadSaveGame(currentSaveGame);
	}
}


void ARPGGameModeBase::SpawnInterationTimerElasped()
{
	if (!CVarSpawnInteractor.GetValueOnGameThread())
	{
		UE_LOG(LogTemp,Log,TEXT("Spawn Interactor is false"));
		return ;
	}
	UEnvQueryInstanceBlueprintWrapper* result = UEnvQueryManager::RunEQSQuery(this,spawnInterationQuery,this,EEnvQueryRunMode::RandomBest25Pct,nullptr);

	if (ensure(result))
	{
		result->GetOnQueryFinishedEvent().AddDynamic(this,&ARPGGameModeBase::SpawnInteration);
	}
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

void ARPGGameModeBase::OnMonsterLoaded(FPrimaryAssetId LoadedId, FVector SpawnLocation)
{
	LogOnScreen(this,"Finished Loading!");
	UAssetManager* Manager = UAssetManager::GetIfValid();
	if (Manager)
	{
		URMonsterData* MonsterData = Cast<URMonsterData>(Manager->GetPrimaryAssetObject(LoadedId));
		if (MonsterData)
		{
			AActor* NewBot = GetWorld()->SpawnActor<AActor>(MonsterData->MonsterClass,SpawnLocation,FRotator::ZeroRotator);

			if (NewBot)
			{
				LogOnScreen(this,FString::Printf(TEXT("Spawned enemy: %s (%s)")
					,*GetNameSafe(NewBot),*GetNameSafe(MonsterData)));

				URActionComponent* ActionComp = Cast<URActionComponent>(NewBot->GetComponentByClass(URActionComponent::StaticClass()));

				if (ActionComp)
				{
					for (TSubclassOf<URAction> ActionClass:MonsterData->Actions)
					{
						ActionComp->AddAction(ActionClass,NewBot);
					}
				}
			}
		}
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
		if (MonsterTable)
		{
			TArray<FMonsterInfoRow*> Rows;
			MonsterTable->GetAllRows("",Rows);

			int32 RandomIndex = FMath::RandRange(0,Rows.Num()-1);
			FMonsterInfoRow* SelectedRow = Rows[RandomIndex];

			UAssetManager* Manager = UAssetManager::GetIfValid();
			if (Manager)
			{
				TArray<FName> Bundles;

				FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(
					this,
					&ARPGGameModeBase::OnMonsterLoaded,
					SelectedRow->MonsterData,
					locations[0]);
				LogOnScreen(this,"Loading Monster...");
				Manager->LoadPrimaryAsset(SelectedRow->MonsterData, Bundles, Delegate);
			}
			
			
		}
		
	}
}

void ARPGGameModeBase::RespawnPlayerElasped(AController* controller)
{
	if (ensure(controller))
	{
		controller->UnPossess();
		RestartPlayer(controller);
		ARCharacter* player = Cast<ARCharacter>(controller->GetPawn());
		if (player)
		{
			player->SpawnUI();
			player->LoadFromState();
		}
		
		/*URWorldUserWidget* UI = Cast<URWorldUserWidget>(CreateWidget<URWorldUserWidget>(GetWorld(),mainHUD));
		if (ensure(UI))
		{
			UI->AddToViewport();
		}*/
	}
}

void ARPGGameModeBase::SpawnInteration(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
	EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp,Log,TEXT("Query interation failed"));
		return ;		
	}


	TArray<FVector> results;
	QueryInstance->GetQueryResultsAsLocations(results);

	if (results.Num()>0)
	{
		UE_LOG(LogTemp,Log,TEXT("Spawn interation success"));
		GetWorld()->SpawnActor<AActor>(interationActors[FMath::RandRange(0,interationActors.Num()-1)],
			results[0],FRotator::ZeroRotator);
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

void ARPGGameModeBase::WriteSaveGame()
{
	for (int i = 0; i < GameState->PlayerArray.Num(); ++i)
	{
		ARPlayerState* playerState = Cast<ARPlayerState>(GameState->PlayerArray[i]);
		if (playerState)
		{
			playerState->WriteSaveGame(currentSaveGame);
		}
	}

	currentSaveGame->savedActors.Empty();
	
	for (FActorIterator it(GetWorld());it;++it)
	{
		AActor* actor = *it;
		if (!actor->Implements<URGameplayInterface>())
		{
			continue;
		}

		FActorSaveData temp;
		temp.actorName = actor->GetName();
		temp.transform = actor->GetActorTransform();
		
		//LogOnScreen(this,temp.actorName);

		FMemoryWriter memWriter(temp.byteData);
		FObjectAndNameAsStringProxyArchive archive(memWriter,true);
		archive.ArIsSaveGame = true;
		actor->Serialize(archive);
		currentSaveGame->savedActors.Add(temp);
	}
	
	UGameplayStatics::SaveGameToSlot(currentSaveGame,SlotName,0);
	
}

void ARPGGameModeBase::LoadSaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName,0))
	{
		currentSaveGame = Cast<URSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName,0));
		if (currentSaveGame == nullptr)
		{
			UE_LOG(LogTemp,Log,TEXT("Failed to load SaveGame Data"));
			return ;
		}
		UE_LOG(LogTemp,Log,TEXT("Loaded SaveGameData."))


		
	}
	else
	{
		currentSaveGame = Cast<URSaveGame>(UGameplayStatics::CreateSaveGameObject(URSaveGame::StaticClass()));

		UE_LOG(LogTemp,Log,TEXT("Created New SaveGame Data"));
	}

	
}

void ARPGGameModeBase::SetActorTransformFromSaved()
{
	for (FActorIterator it(GetWorld());it;++it)
	{
		AActor* actor = *it;
			
		if (!actor->Implements<URGameplayInterface>())
		{
			continue;
		}
			
		for (FActorSaveData i:currentSaveGame->savedActors)
		{
			if (i.actorName == actor->GetName())
			{
				actor->SetActorTransform(i.transform);
				//LogOnScreen()
				//UE_LOG(LogTemp,Log,TEXT("match actor %s"),*actor->GetName());
				FMemoryReader memReader(i.byteData);
				FObjectAndNameAsStringProxyArchive archive(memReader,true);
				archive.ArIsSaveGame = true;
				actor->Serialize(archive);

				IRGameplayInterface::Execute_OnActorLoaded(actor);
				break;
			}
		}
	}
}
