// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "RAction.generated.h"

class URActionComponent;

USTRUCT()
struct FActionRepData
{
	GENERATED_BODY();

public:
	UPROPERTY()
	bool bIsRunning;
	UPROPERTY()
	AActor* instigator;
};


/**
 * 
 */
UCLASS(Blueprintable)
class RPG_API URAction : public UObject
{
	GENERATED_BODY()
protected:

	UPROPERTY(Replicated)
	URActionComponent* actionComp;
	
	URAction();
	
	UFUNCTION(BlueprintCallable, Category="Action")
	URActionComponent* GetOwningComponent() const;
	
	UPROPERTY(EditDefaultsOnly,Category="Tags")
	FGameplayTagContainer grantTags;

	UPROPERTY(EditDefaultsOnly, Category="Tags")
	FGameplayTagContainer blockedTags;

	UPROPERTY(ReplicatedUsing="OnRep_RepData")
	FActionRepData repData;

	UFUNCTION(NetMulticast,Reliable)
	void OnRep_RepData();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:

	bool hasPreAction;

	char ActionKey;
	
	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void PreAction(AActor* instigator);
	
	void InitializeActionComp(URActionComponent* newActionComp);
	
	
	UPROPERTY(EditDefaultsOnly)
	bool bAutoStart;
	
	UFUNCTION(BlueprintCallable, Category="Action")
	bool IsRunning();

	UFUNCTION(Server,Reliable)
	void SetIsRunning(bool in);
	
	UFUNCTION(BlueprintNativeEvent, Category="Action")
	bool CanStart(AActor* instigator);
	
	UFUNCTION(BlueprintNativeEvent,Category="Action")
	void StartAction(AActor* instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent,Category="Action")
	void StopAction(AActor* instigator);

	UFUNCTION(NetMulticast,Reliable)
	void ShowForAllClient(AActor* instigator);
	UPROPERTY(EditDefaultsOnly, Category="Action")
	FName ActionName;

	virtual UWorld* GetWorld() const override;

	virtual bool IsSupportedForNetworking() const override;

	virtual bool CallRemoteFunction(UFunction* Function, void* Parms, FOutParmRec* OutParms, FFrame* Stack) override;

	virtual int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack) override;
};





