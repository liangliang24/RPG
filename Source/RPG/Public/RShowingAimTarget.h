// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RShowingAimTarget.generated.h"

class UCameraComponent;
class ARCharacter;
/**
 * 
 */
UCLASS(Blueprintable)
class RPG_API UShowingAimTarget : public UObject
{
	GENERATED_BODY()
public:
	//UPlayerInput
	FVector TraceAimLine(ARCharacter* Instigator);
	UCameraComponent* InstigatorCameraComponent;
	UDecalComponent* DecalActor;
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* PortalDecalMaterial;
	void Start(ARCharacter* Instigator);
	UDecalComponent* Stop();
	UFUNCTION()
	void SetDecalLocation(ARCharacter* Instigator);

	void DestroyDecal();
protected:
private:
	FTimerHandle SkillTarget_TimerHandle;
};
