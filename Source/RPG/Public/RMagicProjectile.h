// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "RAction.h"
#include "GameFramework/Actor.h"
#include "RMagicProjectile.generated.h"

class URActionEffect;
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
	UFUNCTION()
	void ActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	// Sets default values for this actor's properties
	ARMagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	 * 根组件
	 */
	UPROPERTY(VisibleAnywhere,Category="Components")
	USphereComponent* sphereComp;

	UPROPERTY(EditDefaultsOnly,Category="Particle")
	UParticleSystem* explodeEmitter;
	
	/*
	 * 粒子效果组件
	 */
	UPROPERTY(VisibleAnywhere,Category="Components")
	UParticleSystemComponent* particleComp;

	/*
	 * 投掷物移动组件
	 */
	UPROPERTY(VisibleAnywhere,Category="Components")
	UProjectileMovementComponent* projectileMovementComp;
	
	UPROPERTY(VisibleAnywhere,Category="Components")
	UAudioComponent* movingAudio;

	UPROPERTY(EditDefaultsOnly,Category="Sounds")
	USoundBase* explodeAudio;
	
	UPROPERTY(EditDefaultsOnly,Category="Effect")
	TSubclassOf<UCameraShakeBase> shake;

	UPROPERTY(EditDefaultsOnly,Category="Attack")
	float damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tags")
	FGameplayTag Tag;
	UPROPERTY(EditDefaultsOnly,Category="Attack")
	TSubclassOf<URActionEffect> burningActionClass;

	//UPROPERTY(VisibleAnywhere,Category="Effect")
	
	/*
	 * 对碰撞并且含有属性组件的Actor造成伤害
	 */
	void DoDamage(AActor* OtherActor, const FHitResult& hitResult);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void PostInitializeComponents() override;
};
