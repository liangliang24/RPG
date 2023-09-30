// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_STATS_GROUP(TEXT("RPG_Game"),STATGROUP_RPG,STATCAT_Advanced);

static void LogOnScreen(UObject* worldContext, FString msg, FColor color = FColor::White, float duration = 5.0f)
{
	if (!ensure(worldContext))
	{
		return ;
	}

	UWorld* world = worldContext->GetWorld();

	if (!ensure(world))
	{
		return ;
	}

	FString netPrefix = world->IsNetMode(NM_Client) ? "[CLIENT]" : "[SERVER]";

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,duration,color,netPrefix + msg);
	}
}