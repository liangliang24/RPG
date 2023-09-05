// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RGamePlayFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URGamePlayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category = "Gameplay")
	static bool ApplyDamage(AActor* DamageCauser,AActor* TargetActor,float DamageAmount);

	UFUNCTION(BlueprintCallable,Category = "Gameplay")
	static bool ApplyDirectionDamage(AActor* DamageCauser,AActor* TargetActor,float DamageAmount,const FHitResult& HitResult);
};
