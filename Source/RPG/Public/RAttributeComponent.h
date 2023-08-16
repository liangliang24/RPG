// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, instigatorActor, URAttributeComponent*, owningComp, float, newHealth, float, delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API URAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URAttributeComponent();

protected:

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChange;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Attributes")
	float health;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Attributes")
	float maxHealth;

public:
	UFUNCTION(BlueprintCallable,Category="Attributes")
	bool ApplyHealthChange(AActor* instigatorActor, float delta);
		
};
