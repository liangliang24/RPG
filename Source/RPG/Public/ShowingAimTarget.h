// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ShowingAimTarget.generated.h"

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
	
	FVector TraceAimLine(ARCharacter* Instigator);
	UCameraComponent* InstigatorCameraComponent;
	UDecalComponent* DecalActor;
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* PortalDecalMaterial;
	void Start(ARCharacter* Instigator);
	void Stop();
	UFUNCTION()
	void SetDecalLocation(ARCharacter* Instigator);
protected:
private:
	FTimerHandle SkillTarget_TimerHandle;
};
