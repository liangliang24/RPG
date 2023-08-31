// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, instigatorActor, URAttributeComponent*, owningComp, float, newHealth, float, delta);

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

	UFUNCTION(BlueprintCallable)
	static URAttributeComponent* GetAttributeComponent(AActor* targetActor);
	
	UFUNCTION(BlueprintCallable)
	static bool GetActorAlive(AActor* targetActor);
protected:

	
	/*生命值*/
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Attributes")
	float health;

	/*最大生命值*/
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Attributes")
	float maxHealth;

public:
	/*
	 * 判断角色生命值是否大于0
	 */
	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	/*
	 * 事件，当血量更改的时候
	 */
	UPROPERTY(BlueprintAssignable,EditAnywhere)
	FOnHealthChanged OnHealthChange;

	/*
	 * 更改血量
	 */
	UFUNCTION(BlueprintCallable,Category="Attributes")
	bool ApplyHealthChange(AActor* instigatorActor, float delta);
		
};
