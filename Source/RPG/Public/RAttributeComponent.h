// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RAttributeComponent.generated.h"
class URAction;
class URSaveGame;
static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("rpg.DamageMultiplier"),1.0f,TEXT("Global Damage Modifier for Attribute Component."),ECVF_Cheat);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, instigatorActor, URAttributeComponent*, owningComp, float, newHealth, float, delta);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCreditChanged, AActor*, instigatorActor, URAttributeComponent*, owningComp, int , newCredit, int, delta);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRageChanged, AActor*, instigatorActor, URAttributeComponent*, owningComp, int , newRage, int, delta);
/*
 * 属性组件，处理角色属性信息
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API URAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URAttributeComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	static URAttributeComponent* GetAttributeComponent(AActor* targetActor);
	
	UFUNCTION(BlueprintCallable)
	static bool GetActorAlive(AActor* targetActor);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="attributes")
	bool haveRage;
	
	/*生命值*/
	UPROPERTY(EditDefaultsOnly,Replicated,BlueprintReadOnly,Category="Attributes")
	float health;

	/*最大生命值*/
	UPROPERTY(EditDefaultsOnly,Replicated,BlueprintReadOnly,Category="Attributes")
	float maxHealth;

	UPROPERTY(EditDefaultsOnly,Replicated,BlueprintReadOnly,Category="Attributes")
	int credit;

	UPROPERTY(EditDefaultsOnly,Replicated,BlueprintReadOnly,Category="Attributes")
	int rage;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastHealthChanged(AActor* instigatorActor, float newHealth, float delta);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastCreditChanged(AActor* instigatorActor, int newCredit, int delta);
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRageChanged(AActor* instigatorActor, int newRage, int delta);
public:
	/*
	 * 判断角色生命值是否大于0
	 */
	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	bool IsStunned() const;
	
	UFUNCTION(BlueprintCallable)
	bool IsSprintting() const;

	/*
	 * 事件，当血量更改的时候
	 */
	UPROPERTY(BlueprintAssignable,EditAnywhere)
	FOnHealthChanged OnHealthChange;

	UPROPERTY(BlueprintAssignable,EditAnywhere)
	FOnCreditChanged OnCreditChanged;

	UPROPERTY(BlueprintAssignable, EditAnywhere)
	FOnRageChanged OnRageChanged;
	/*
	 * 更改血量
	 */
	UFUNCTION(BlueprintCallable,Category="Attributes")
	bool ApplyHealthChange(AActor* instigatorActor, float delta);

	UFUNCTION(BlueprintCallable,Category="Attributes")
	bool ApplyCreditChange(AActor* instigatorActor, int delta);

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool ApplyRageChange(AActor* instigatorActor, int delta);

	UFUNCTION()
	void OnActionStart(URActionComponent* OwningComp,URAction* Action);
	
	float GetHealth();

	bool Kill();
	
	void SetCredit(int credit);
};
