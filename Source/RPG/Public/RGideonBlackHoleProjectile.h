// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RProjectileBase.h"
#include "RGideonBlackHoleProjectile.generated.h"

class URadialForceComponent;
/**
 * 黑洞投射物类
 * 当发射之后，碰撞到物体就会产生黑洞，并且毁灭所有被吸入的物体
 * 如果一直没有碰撞，那么就会发射五秒后产生黑洞
 */
UCLASS()
class RPG_API ARGideonBlackHoleProjectile : public ARProjectileBase
{
	GENERATED_BODY()
public:
	ARGideonBlackHoleProjectile();
protected:

	/*
	 * 是否已经爆炸产生黑洞
	 */
	bool isExplode;
	
	//virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	/*
	 * 绑定与其他物体发生碰撞时候绑定的函数
	 */
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void BeginPlay() override;

	/*
	 * 提供吸力的组件
	 */
	UPROPERTY(VisibleAnywhere,Category="Component")
	URadialForceComponent* suckComp;

	/*
	 * 黑洞的粒子效果
	 */
	UPROPERTY(VisibleAnywhere,Category="Component")
	UParticleSystemComponent* blackHole;

	/*
	 * 绑定黑洞发生碰撞时候的函数
	 */
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	FTimerHandle timerHandle_Destroy;
	FTimerHandle timerHandle_Explode;
	
	virtual void Explode_Implementation() override;

	virtual void PostInitializeComponents() override;
	//virtual void Destroyed() override;
};
