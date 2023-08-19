// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "RHealthPotion.generated.h"

UCLASS()
class RPG_API ARHealthPotion : public AActor,public IRGameplayInterface
{
	GENERATED_BODY()
	virtual void Interact_Implementation(APawn* instigatorPawn) override;
public:	
	// Sets default values for this actor's properties
	ARHealthPotion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* staticMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
