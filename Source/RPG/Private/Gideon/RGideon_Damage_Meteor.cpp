// Fill out your copyright notice in the Description page of Project Settings.


#include "Gideon/RGideon_Damage_Meteor.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ARGideon_Damage_Meteor::ARGideon_Damage_Meteor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	MeteorMove = CreateDefaultSubobject<UProjectileMovementComponent>("MeteorMovement");
	SetReplicates(true);

	ColliMesh = CreateDefaultSubobject<UCapsuleComponent>("CollisionMesh");
	ColliMesh->SetupAttachment(BaseMesh);
	BaseMesh->SetEnableGravity(true);
	MeteorMove->ProjectileGravityScale = 1.0f;
}

void ARGideon_Damage_Meteor::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	bReplicates = true;
}

// Called when the game starts or when spawned
void ARGideon_Damage_Meteor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARGideon_Damage_Meteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

