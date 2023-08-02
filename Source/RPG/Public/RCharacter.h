// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RCharacter.generated.h"

class URInteractionComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class RPG_API ARCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARCharacter();

protected:
	FTimerHandle primaryAttackHandle;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* springArmComp;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* cameraComp;

	UPROPERTY(EditAnywhere,Category="Attack")
	TSubclassOf<AActor> projectile;
	
	UPROPERTY(EditAnywhere,Category="Attack")
	UAnimMontage* primaryAttackAnimation;
	
	UPROPERTY(VisibleAnywhere)
	URInteractionComponent* interactComp;

	void MoveForward(float X);
	void MoveRight(float X);
	void PrimaryAttack();
	UFUNCTION()
	void SpawnProjectile();
	void PrimaryInteract();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
