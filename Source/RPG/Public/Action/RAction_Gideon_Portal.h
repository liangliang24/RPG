// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RAction.h"
#include "UObject/NoExportTypes.h"
#include "RAction_Gideon_Portal.generated.h"

class UShowingAimTarget;
/**
 * 
 */
UCLASS()
class RPG_API URAction_Gideon_Portal : public URAction
{
	GENERATED_BODY()

public:
	bool isAiming;
	URAction_Gideon_Portal();
	virtual void StartAction_Implementation(AActor* instigator) override;
	virtual void StopAction_Implementation(AActor* instigator) override;
	
protected:
	UShowingAimTarget* Aim;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UShowingAimTarget> AimTarget;
	UPROPERTY(EditDefaultsOnly,Category="Animation")
	UAnimMontage* PortalStartAnimMontage;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> Portal;

	UFUNCTION()
	void StartAction_Elasped(ACharacter* instigator, UDecalComponent* BindingPortalSpcifier);
private:
};