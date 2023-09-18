// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "RActionEffect.h"
#include "Components/ActorComponent.h"
#include "RActionComponent.generated.h"


class URAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API URActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tags")
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
	void ServerStartAction(AActor* instigator, FName actionName);
	
	UPROPERTY(Replicated)
	TArray<URAction*> actions;
	
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Action")
	TArray<TSubclassOf<URAction>> defaultActions;

	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
};


