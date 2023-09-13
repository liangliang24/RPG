// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "RAction.generated.h"

class URActionComponent;
/**
 * 
 */
UCLASS(Blueprintable)
class RPG_API URAction : public UObject
{
	GENERATED_BODY()
protected:
	URAction();
	
	UFUNCTION(BlueprintCallable, Category="Action")
	URActionComponent* GetOwningComponent() const;
	
	UPROPERTY(EditDefaultsOnly,Category="Tags")
	FGameplayTagContainer grantTags;

	UPROPERTY(EditDefaultsOnly, Category="Tags")
	FGameplayTagContainer blockedTags;
	
	bool bIsRunning;

public:
	UPROPERTY(EditDefaultsOnly)
	bool bAutoStart;
	
	UFUNCTION(BlueprintCallable, Category="Action")
	bool IsRunning();
	
	UFUNCTION(BlueprintNativeEvent, Category="Action")
	bool CanStart(AActor* instigator);
	
	UFUNCTION(BlueprintNativeEvent,Category="Action")
	void StartAction(AActor* instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent,Category="Action")
	void StopAction(AActor* instigator);
	
	UPROPERTY(EditDefaultsOnly, Category="Action")
	FName actionName;

	virtual UWorld* GetWorld() const override;
};
