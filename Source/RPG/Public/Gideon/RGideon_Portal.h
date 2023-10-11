// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "RGideon_Portal.generated.h"

class USphereComponent;

UCLASS()
class RPG_API ARGideon_Portal : public AActor, public IRGameplayInterface
{
	GENERATED_BODY()
	
	virtual void Interact_Implementation(APawn* instigatorPawn) override;
public:	
	// Sets default values for this actor's properties
	ARGideon_Portal();

	UPROPERTY(EditAnywhere)
	ARGideon_Portal* BindingPortal;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
