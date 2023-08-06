// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RExplosiveActor.generated.h"

class URadialForceComponent;

/*
 * 可爆炸物体，受击后会发生爆炸，对范围内的物体击退并伤害
 */
UCLASS()
class RPG_API ARExplosiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARExplosiveActor();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	 * Actor的根组件
	 */
	UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* baseMesh;

	/*
	 * Actor爆炸相关组件
	 */
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
    URadialForceComponent* pulseComp;

	/*
	 * 后初始化，绑定事件
	 */
	virtual void PostInitializeComponents() override;

	/*
	 * 受击后反馈
	 */
	UFUNCTION()
	void OnActorHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
