
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS(ABSTRACT)
class RPG_API ARProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	 * 球体组件，用于碰撞检测
	 */
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components");
	USphereComponent* sphere;

	/*
	 * 粒子系统
	 */
	UPROPERTY(VisibleAnywhere,Category="Effects")
	UParticleSystem* impactVFX;

	/*
	 * 移动组件
	 */
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	UProjectileMovementComponent* moveComp;

	/*
	 * 位移组件
	 */
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	UParticleSystemComponent* effectComp;

	
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/*
	 * 爆炸，并不一定是爆炸操作，对于各种特定的投射物，在Explode里面完成特定的操作
	 */
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Explode();

	virtual void PostInitializeComponents() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
