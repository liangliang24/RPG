// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "RItemChest.generated.h"

UCLASS()
class RPG_API ARItemChest : public AActor,public IRGameplayInterface
{
	GENERATED_BODY()
	void Interact_Implementation(APawn* instigatorPawn) override;
public:	
	// Sets default values for this actor's properties
	ARItemChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* baseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* lidMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
