// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RAICharacter.generated.h"

class UPawnSensingComponent;

UCLASS()
class RPG_API ARAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARAICharacter();

protected:
	UPROPERTY(VisibleAnywhere,Category="Components")
	UPawnSensingComponent* pawnSensingComp;

	UFUNCTION()
	void OnSeePawn(APawn* Pawn);
public:
	
	
	virtual void PostInitializeComponents() override;
};
