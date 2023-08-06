// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RCharacter.generated.h"

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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	 * 机械臂组件
	 * 用于连接、绑定摄像头和角色，使得连接一致
	 */
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* springArmComp;

	/*
	 * 摄像机组件
	 */
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* cameraComp;

	/*
	 * 投掷物
	 */
	UPROPERTY(EditAnywhere,Category="Attack")
	TSubclassOf<AActor> projectile;

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
	 * 普通攻击操作绑定函数（生成并发射）
	 */
	UFUNCTION()
	void SpawnProjectile();
	/*
	 * 绑定交互操作
	 */
	void PrimaryInteract();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
