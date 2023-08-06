// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

/*
 * 魔法投掷物
 */
UCLASS()
class RPG_API ARMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARMagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	 * 根组件
	 */
	UPROPERTY(VisibleAnywhere)
	USphereComponent* sphereComp;

	/*
	 * 粒子效果组件
	 */
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* particleComp;

	/*
	 * 投掷物移动组件
	 */
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* projectileMovementComp;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
