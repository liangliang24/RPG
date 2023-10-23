// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RGideon_Suck.generated.h"

class USphereComponent;
class URadialForceComponent;

UCLASS()
class RPG_API ARGideon_Suck : public AActor
{
	GENERATED_BODY()
	
public:
	
	// Sets default values for this actor's properties
	ARGideon_Suck();

	virtual void PreInitializeComponents() override;
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly)
	URadialForceComponent* SuckComponent;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystemComponent* Particle;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* ColliMesh;

	UFUNCTION()
	void SuckImpulse();

	UFUNCTION()
	void DestroyDelay();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnSuckActorToCenter(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
