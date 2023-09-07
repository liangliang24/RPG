// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RActionComponent.generated.h"


class URAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API URActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category="Action")
	void AddAction(TSubclassOf<URAction> actionClass);

	UFUNCTION(BlueprintCallable,Category="Action")
	bool StartActionByName(AActor* instigator, FName actionName);

	UFUNCTION(BlueprintCallable,Category="Action")
	bool StopActionByName(AActor* instigator, FName actionName);
	// Sets default values for this component's properties
	URActionComponent();

protected:
	UPROPERTY()
	TArray<URAction*> actions;
	
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Action")
	TArray<TSubclassOf<URAction>> defaultActions;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
