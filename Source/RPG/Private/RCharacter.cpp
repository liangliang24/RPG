// Fill out your copyright notice in the Description page of Project Settings.


#include "RCharacter.h"

#include "RAttributeComponent.h"
#include "RInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

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
	attributeComp = CreateDefaultSubobject<URAttributeComponent>("AttributeComponent");

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



void ARCharacter::OnHealthChange(AActor* InstigatorActor, URAttributeComponent* OwningComp, float NewHealth,
float Delta)
{
	if(NewHealth <= 0)
	{
		DisableInput(Cast<APlayerController>(GetController()));

		FTimerHandle destroy_TimerHandle;
		GetWorldTimerManager().SetTimer(destroy_TimerHandle,this,&ARCharacter::Die,5.0f);
	}
}

void ARCharacter::Die()
{
	Destroy();
}

void ARCharacter::MoveForward(float X)
{
	AddMovementInput(cameraComp->GetForwardVector(),X);
}

void ARCharacter::MoveRight(float X)
{
	AddMovementInput(cameraComp->GetRightVector(),X);
}

void ARCharacter::PrimaryAttack_Elasped()
{
	SpawnProjectile(projectile);
	GetWorldTimerManager().ClearTimer(primaryAttackHandle);
}

void ARCharacter::PrimaryAttack()
{
	PlayAnimMontage(primaryAttackAnimation);
	GetWorld()->GetTimerManager().SetTimer(primaryAttackHandle,this,&ARCharacter::PrimaryAttack_Elasped,0.17f);
	//
	
}
void ARCharacter::SpawnProjectile(TSubclassOf<AActor> classToSpawn)
{
	if(ensureAlways(classToSpawn))
	{
		UE_LOG(LogTemp,Log,TEXT("Spawn %s"),*GetNameSafe(classToSpawn));
		FVector location =  GetMesh()->GetSocketLocation("Muzzle_01");
		FActorSpawnParameters spawnParameters;
		spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		spawnParameters.Instigator = this;
		FHitResult hit;
		FVector start = cameraComp->GetComponentLocation();

		FVector end = start + cameraComp->GetComponentRotation().Vector()*10000;
	
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);
		bool queryResult = GetWorld()->LineTraceSingleByChannel(hit,start,end,ECollisionChannel::ECC_Visibility,params);
		UGameplayStatics::SpawnEmitterAttached(spawnProjectileVFX,GetMesh(),"Muzzle_01",FVector::ZeroVector,FRotator::ZeroRotator,EAttachLocation::SnapToTarget);
		if(queryResult)
		{
			FRotator spawnway = (hit.ImpactPoint-location).Rotation();
			GetWorld()->SpawnActor<AActor>(classToSpawn,location,spawnway,spawnParameters);
		}
		else
		{
			GetWorld()->SpawnActor<AActor>(classToSpawn,location,cameraComp->GetComponentRotation(),spawnParameters);
		}
	

		//GetWorld()->GetTimerManager().ClearTimer(primaryAttackHandle);
	}
}

void ARCharacter::PrimaryInteract()
{
	interactComp->PrimaryInteract();
}

void ARCharacter::Dash_Elasped()
{
	SpawnProjectile(dashProjectile);
	GetWorldTimerManager().ClearTimer(dashTimerHandle);
}

void ARCharacter::Dash()
{
	UE_LOG(LogTemp,Log,TEXT("Dash"));
	PlayAnimMontage(primaryAttackAnimation);
	GetWorld()->GetTimerManager().SetTimer(dashTimerHandle,this,&ARCharacter::Dash_Elasped,0.17f);
}

void ARCharacter::BlackHole_Elasped()
{
	SpawnProjectile(blackHoleProjectile);
	GetWorldTimerManager().ClearTimer(blackHoleTimerHandle);
}

void ARCharacter::BlackHole()
{
	PlayAnimMontage(primaryAttackAnimation);
	GetWorld()->GetTimerManager().SetTimer(blackHoleTimerHandle,this,&ARCharacter::BlackHole_Elasped,0.17f);
}

void ARCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	attributeComp->OnHealthChange.AddDynamic(this,&ARCharacter::OnHealthChange);
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

	InputComponent->BindAction("Dash",IE_Pressed,this,&ARCharacter::Dash);

	InputComponent->BindAction("BlackHole",IE_Pressed,this,&ARCharacter::BlackHole);
}

