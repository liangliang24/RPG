// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RPlayerState.generated.h"

class URSaveGame;
/**
 * 
 */
UCLASS()
class RPG_API ARPlayerState : public APlayerState
{
	GENERATED_BODY()
private:
	int credit;

public:
	UFUNCTION(BlueprintCallable)
	int GetCredit() const;
	void SetCredit(int Credit);

	UFUNCTION(BlueprintNativeEvent)
	void WriteSaveGame(URSaveGame* saveObject);
	UFUNCTION(BlueprintNativeEvent)
	void LoadSaveGame(URSaveGame* saveObject);
};
