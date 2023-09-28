// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "RActionEffect.h"
#include "Components/ActorComponent.h"
#include "RActionComponent.generated.h"


class URAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionStateChanged,URActionComponent*,OwningComp,URAction*,Action);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API URActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category="Tags")
	FGameplayTagContainer activeGameplayTags;
	
	UFUNCTION(BlueprintCallable,Category="Action")
	void AddAction(TSubclassOf<URAction> actionClass, AActor* instigator);

	UFUNCTION(BlueprintCallable,Category="Action")
	bool StartActionByName(AActor* instigator, FName actionName);

	UFUNCTION(BlueprintCallable,Category="Action")
	bool StopActionByName(AActor* instigator, FName actionName);

	UFUNCTION(BlueprintCallable, Category="Action")
	void RemoveAction(URAction* action);
	// Sets default values for this component's properties
	URActionComponent();

protected:

	UFUNCTION(Server,Reliable)
	void ServerStartAction(AActor* instigator, URAction* action);
	UFUNCTION(Server,Reliable)
	void ServerStopAction(AActor* instigator, URAction* action);
	
	UPROPERTY(Replicated,BlueprintReadOnly)
	TArray<URAction*> actions;
	
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Action")
	TArray<TSubclassOf<URAction>> defaultActions;

	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionStarted;
	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionStoped;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
};


