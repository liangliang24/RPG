// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RAttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API URAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URAttributeComponent();

protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Attributes")
	float health;
	


public:
	UFUNCTION(BlueprintCallable,Category="Attributes")
	bool ApplyHealthChange(float delta);
		
};
