// Fill out your copyright notice in the Description page of Project Settings.


#include "RCharacter.h"

#include "RInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARCharacter::ARCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArmComp = CreateDefaultSubobject<USpringArmComponent>("springArmComp");
	springArmComp->SetupAttachment(RootComponent);

	cameraComp = CreateDefaultSubobject<UCameraComponent>("cameraComp");
	cameraComp->SetupAttachment(springArmComp);

	interactComp = CreateDefaultSubobject<URInteractionComponent>("interactComp");
	
	GetCharacterMovement()->bOrientRotationToMovement = true;

	springArmComp->bUsePawnControlRotation = true;

	
    bUseControllerRotationYaw = false;
	
}

// Called when the game starts or when spawned
void ARCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ARCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




void ARCharacter::MoveForward(float X)
{
	AddMovementInput(cameraComp->GetForwardVector(),X);
}

void ARCharacter::MoveRight(float X)
{
	AddMovementInput(cameraComp->GetRightVector(),X);
}

void ARCharacter::PrimaryAttack()
{
	PlayAnimMontage(primaryAttackAnimation);
	
	GetWorld()->GetTimerManager().SetTimer(primaryAttackHandle,this,&ARCharacter::SpawnProjectile,0.17f);
	//
	
}
void ARCharacter::SpawnProjectile()
{
	FVector location =  GetMesh()->GetSocketLocation("Muzzle_01");
	FActorSpawnParameters spawnParameters;
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	spawnParameters.Instigator = this;
	FHitResult hit;
	FVector start = cameraComp->GetComponentLocation();

	FVector end = start + cameraComp->GetComponentRotation().Vector()*10000;
	bool queryResult = GetWorld()->LineTraceSingleByChannel(hit,start,end,ECollisionChannel::ECC_Visibility);
	if(queryResult)
	{
		FRotator spawnway = (hit.ImpactPoint-location).Rotation();
		GetWorld()->SpawnActor<AActor>(projectile,location,spawnway,spawnParameters);
	}
	else
	{
		GetWorld()->SpawnActor<AActor>(projectile,location,cameraComp->GetComponentRotation(),spawnParameters);
	}
	

	GetWorld()->GetTimerManager().ClearTimer(primaryAttackHandle);
}

void ARCharacter::PrimaryInteract()
{
	interactComp->PrimaryInteract();
}

// Called to bind functionality to input
void ARCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward",this,&ARCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight",this,&ARCharacter::MoveRight);

	InputComponent->BindAxis("TurnHorizon",this,&APawn::AddControllerYawInput);

	InputComponent->BindAxis("TurnUp",this,&APawn::AddControllerPitchInput);

	InputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);

	InputComponent->BindAction("PrimaryAttack",IE_Pressed,this,&ARCharacter::PrimaryAttack);

	InputComponent->BindAction("PrimaryInteract",IE_Pressed,this,&ARCharacter::PrimaryInteract);
}

