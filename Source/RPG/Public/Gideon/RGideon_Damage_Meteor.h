// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RGideon_Damage_Meteor.generated.h"

class UCapsuleComponent;
class UProjectileMovementComponent;

UCLASS()
class RPG_API ARGideon_Damage_Meteor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARGideon_Damage_Meteor();

	virtual void PreInitializeComponents() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* ColliMesh;
	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* MeteorMove;

	

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
