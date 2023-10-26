// Fill out your copyright notice in the Description page of Project Settings.


#include "RPlayerCameraManager.h"

ARPlayerCameraManager::ARPlayerCameraManager()
{
	CameraBehavior = CreateDefaultSubobject<USkeletalMeshComponent>("CameraBehavior");
	CameraBehavior->SetupAttachment(RootComponent);
}
