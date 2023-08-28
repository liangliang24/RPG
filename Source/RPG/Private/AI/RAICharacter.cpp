// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RAICharacter.h"

// Sets default values
ARAICharacter::ARAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

