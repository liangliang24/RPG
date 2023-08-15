// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RProjectileBase.h"
#include "RGideonBlackHoleProjectile.generated.h"

class URadialForceComponent;
/**
 * 
 */
UCLASS()
class RPG_API ARGideonBlackHoleProjectile : public ARProjectileBase
{
	GENERATED_BODY()
public:
	ARGideonBlackHoleProjectile();
protected:

	bool isExplode;
	
	//virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,Category="Component")
	URadialForceComponent* suckComp;

	UPROPERTY(VisibleAnywhere,Category="Component")
	UParticleSystemComponent* blackHole;


	FTimerHandle timerHandle_Destroy;
	FTimerHandle timerHandle_Explode;

	virtual void Explode_Implementation() override;

	virtual void PostInitializeComponents() override;
	//virtual void Destroyed() override;
};
