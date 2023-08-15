// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RProjectileBase.h"
#include "RGideonDashProjectile.generated.h"

/**
 * 
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

	void teleportInstigator();

	virtual void BeginPlay() override;

public:
	//virtual void Tick(float DeltaSeconds) override;
};
