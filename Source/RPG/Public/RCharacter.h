// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RCharacter.generated.h"

class URActionComponent;
class URAttributeComponent;
class URInteractionComponent;
class UCameraComponent;
class USpringArmComponent;

/*
 * 玩家角色，用于玩家操控
 */
UCLASS()
class RPG_API ARCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	// Sets default values for this character's properties
	ARCharacter();

protected:
	FTimerHandle primaryAttackHandle;
	FTimerHandle dashTimerHandle;
	FTimerHandle blackHoleTimerHandle;
	UPROPERTY(EditDefaultsOnly,Category="Effect")
	UParticleSystem* spawnProjectileVFX;
	UPROPERTY(EditDefaultsOnly,Category="Attack")
	//发射黑洞所需的愤怒值
	int blackHoleCostRage;
	UUserWidget* playerUIInstance;
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> playerUIClass;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	 * 机械臂组件
	 * 用于连接、绑定摄像头和角色，使得连接一致
	 */
	UPROPERTY(VisibleAnywhere,Category="Components")
	USpringArmComponent* springArmComp;

	/*
	 * 摄像机组件
	 */
	UPROPERTY(VisibleAnywhere,Category="Components")
	UCameraComponent* cameraComp;

	/*
	 * 投掷物
	 */
	UPROPERTY(EditAnywhere,Category="Attack")
	TSubclassOf<AActor> projectile;
	
	UPROPERTY(EditAnywhere,Category="Attack")
	TSubclassOf<AActor> dashProjectile;

	UPROPERTY(EditAnywhere,Category="Attack")
	TSubclassOf<AActor> blackHoleProjectile;

	/*
	 * 普通攻击动画
	 */
	UPROPERTY(EditAnywhere,Category="Attack")
	UAnimMontage* primaryAttackAnimation;

	/*
	 * 交互组件，用于和世界物体进行交互
	 */
	UPROPERTY(VisibleAnywhere)
	URInteractionComponent* interactComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	URAttributeComponent* attributeComp;


	/*
	 * 前后移动
	 */
	void MoveForward(float X);
	/*
	 * 左右移动
	 */
	void MoveRight(float X);
	/*
	 * 普通攻击操作绑定函数
	 */
	void PrimaryAttack();
	/*
	 * 绑定交互操作
	 */
	void PrimaryInteract();
	
	/*
	 * 冲刺操作
	 */
	void Dash();
	/*
	 * 发射黑洞操作
	 */
	void BlackHole();

	void SprintStart();

	void SprintStop();
	
	/*
	 * 角色死亡
	 */
	void Die();
public:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	URActionComponent* actionComp;
	UFUNCTION(BlueprintCallable)
	void LoadFromState();
	
	UFUNCTION(BlueprintCallable)
	void SpawnUI();
	
	UFUNCTION(Exec)
	void HealSelf(float delta);

	UFUNCTION()
	void OnCreditChanged(AActor* InstigatorActor, URAttributeComponent* OwningComp, int NewCredit, int Delta);
	
	virtual void PostInitializeComponents() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	/*
	 * 绑定事件，当血量属性发生变化时被调用
	 */
	UFUNCTION()
	void OnHealthChange(AActor* InstigatorActor, URAttributeComponent* OwningComp, float NewHealth, float Delta);
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
