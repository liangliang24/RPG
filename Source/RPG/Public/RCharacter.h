// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "RAction.h"
#include "GameFramework/Character.h"
#include "RCharacter.generated.h"

class URInputAbilityConfig;
class URInputMoveConfig;
class UShowingAimTarget;
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

	//virtual void SetALSMovementAction_Implementation(EMovementAction NewMovementAction) override;
	//virtual void SetALSMovementState_Implementation(EMovementState NewMovementState) override;
public:
	// Sets default values for this character's properties
	ARCharacter();

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="EnhancedInput")
	URInputMoveConfig* InputMoveAction;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="EnhancedInput")
	URInputAbilityConfig* InputAbilityAction;
	UPROPERTY(EditAnywhere,Category="EnhancedInput")
	UInputMappingContext* InputMapping;
	/*UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UShowingAimTarget> AimTarget;*/
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
	UPROPERTY(EditAnywhere)
	const UInputAction* IA_P;



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	 * 机械臂组件
	 * 用于连接、绑定摄像头和角色，使得连接一致
	 */
	UPROPERTY(VisibleAnywhere,Category="Components")
	USpringArmComponent* springArmComp;

	

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
	void MoveForward(const FInputActionValue& InputActionValue);
	void MoveBackWard(const FInputActionValue& InputActionValue);
	/*
	 * 左右移动
	 */
	void MoveLeft(const FInputActionValue& InputActionValue);
	void MoveRight(const FInputActionValue& InputActionValue);
	/*
	 * 普通攻击操作绑定函数
	 */
	void PrimaryAttack(const FInputActionValue& InputActionValue);
	/*
	 * 绑定交互操作
	 */
	void PrimaryInteract();
	
	/*
	 * 冲刺操作
	 */
	void Dash_Start();
	
	void Dash_Stop();
	/*
	 * 发射黑洞操作
	 */
	void BlackHole_Start(const FInputActionValue& InputActionValue);

	void BlackHole_Stop(const FInputActionValue& InputActionValue);
	void SprintStart(const FInputActionValue& InputActionValue);

	void SprintStop(const FInputActionValue& InputActionValue);
	
	/*
	 * 角色死亡
	 */
	void Die();
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	URActionComponent* ActionComp;
	
	/*
	 * 摄像机组件
	 */
	UPROPERTY(VisibleAnywhere,Category="Components")
	UCameraComponent* cameraComp;
	UFUNCTION(BlueprintCallable)
	void LoadFromState();
	
	UFUNCTION(BlueprintCallable)
	void SpawnUI();
	
	UFUNCTION(Exec)
	void HealSelf(float delta);

	UFUNCTION()
	void OnCreditChanged(AActor* InstigatorActor, URAttributeComponent* OwningComp, int NewCredit, int Delta);

	UFUNCTION()
	void OnActionStart(URActionComponent* OwningComp, URAction* Action);
	UFUNCTION()
	void OnActionStop(URActionComponent* OwningComp, URAction* Action);
	virtual void PostInitializeComponents() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool PressF;
	bool PressE;
	bool PressQ;
	bool PressR;
	bool PressLeftbutton;

	/*
	 * 绑定事件，当血量属性发生变化时被调用
	 */
	UFUNCTION()
	void OnHealthChange(AActor* InstigatorActor, URAttributeComponent* OwningComp, float NewHealth, float Delta);

	void P(const FInputActionInstance& InputActionInstance);

	void Input_Jump(const FInputActionValue& InputActionValue);
	void Input_TurnHorizon(const FInputActionValue& InputActionValue);
	void Input_TurnUp(const FInputActionValue& InputActionValue);
	void SetCharacterSpeedShortly(float Speed, float time);
	UFUNCTION()
	void CharacterSpeedSet(float Speed);
	void Q_AbilityStart(const FInputActionValue& InputActionValue);
	void Q_AbilityStop(const FInputActionValue& InputActionValue);
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
