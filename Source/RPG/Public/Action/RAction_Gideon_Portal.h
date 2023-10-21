// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RAction.h"
#include "RAction_Aim.h"
#include "UObject/NoExportTypes.h"
#include "RAction_Gideon_Portal.generated.h"

class ARGideon_Portal;
class ARCharacter;
class UShowingAimTarget;
/**
 * 
 */
UCLASS()
class RPG_API URAction_Gideon_Portal : public URAction_Aim
{
	GENERATED_BODY()

public:
	URAction_Gideon_Portal();
	virtual void StartAction_Implementation(AActor* instigator) override;
	UFUNCTION(Server,Reliable)
	void SpawnPortal(ARCharacter* Instigator);
	virtual void StopAction_Implementation(AActor* instigator) override;
	UFUNCTION(NetMulticast,Reliable)
	void NetMulticast_PlayAnimMontage(ARCharacter* Instigator);
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ARGideon_Portal> Portal;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* Anim;
private:
};
