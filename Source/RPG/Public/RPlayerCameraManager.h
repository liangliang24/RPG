// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "RPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API ARPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	ARPlayerCameraManager();
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USkeletalMeshComponent* CameraBehavior;
};
