// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RExplosiveActor.generated.h"

class URadialForceComponent;

UCLASS()
class RPG_API ARExplosiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARExplosiveActor();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* baseMesh;
  
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
    URadialForceComponent* pulseComp;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnActorHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
