// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RProjectileBase.h"
#include "RGideonDashProjectile.generated.h"

/**
 * 冲刺投射物，当发射此投射物之后，角色会在0.2秒后传送至投射物所处位置
 */
UCLASS()
class RPG_API ARGideonDashProjectile : public ARProjectileBase
{
	GENERATED_BODY()
public:
	ARGideonDashProjectile();
	
protected:
	
	UPROPERTY(EditDefaultsOnly,Category="Teleport")
    float teleportDelay;
    
    UPROPERTY(EditDefaultsOnly,Category="Teleport")
    float detonateDelay;

	FTimerHandle timeHandle_Delay;
	FTimerHandle timerHandle_Teleport;

	virtual void Explode_Implementation() override;

	/*
	 * 将发射者传送到当前位置
	 */
	void teleportInstigator();

	virtual void BeginPlay() override;

public:
	//virtual void Tick(float DeltaSeconds) override;
};
