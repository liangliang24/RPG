// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RAction.h"
#include "RAction_Aim.generated.h"

class ARCharacter;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class RPG_API URAction_Aim : public URAction
{
	GENERATED_BODY()

public:
	URAction_Aim();
	virtual void StartAction_Implementation(AActor* Instigator) override;
	virtual void StopAction_Implementation(AActor* instigator) override;
	UFUNCTION(Client,Reliable)
	void SpawnDecalActor(ARCharacter* Instigator);
	UFUNCTION()
	void SetDecalLocation(ARCharacter* Instigator);
	FVector TraceAimLine(ARCharacter* Instigator);
	UFUNCTION(Client,Reliable)
	void SetClientLogicStop();
	UFUNCTION(Server,Reliable)
	void SetResultLocation(FVector FinalLocation);
	
protected:
	UCameraComponent* InstigatorCameraComponent;
    UDecalComponent* DecalActor;
    UPROPERTY(EditDefaultsOnly)
    UMaterialInterface* PortalDecalMaterial;
    FTimerHandle SkillTarget_TimerHandle;
	UPROPERTY(Replicated)
	FVector ResultLocation;
private:
	


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
