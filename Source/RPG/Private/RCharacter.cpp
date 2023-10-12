// Fill out your copyright notice in the Description page of Project Settings.


#include "RCharacter.h"

#include "RActionComponent.h"
#include "RAttributeComponent.h"
#include "RInteractionComponent.h"
#include "RPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Gideon/RGideon_Portal.h"
#include "RPG/RPG.h"

// Sets default values
ARCharacter::ARCharacter()
	:HandSocketName("Muzzle_01")
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArmComp = CreateDefaultSubobject<USpringArmComponent>("springArmComp");
	springArmComp->SetupAttachment(RootComponent);

	cameraComp = CreateDefaultSubobject<UCameraComponent>("cameraComp");
	cameraComp->SetupAttachment(springArmComp);

	interactComp = CreateDefaultSubobject<URInteractionComponent>("interactComp");
	attributeComp = CreateDefaultSubobject<URAttributeComponent>("AttributeComponent");

	actionComp = CreateDefaultSubobject<URActionComponent>("ActionComponent");
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

void ARCharacter::LoadFromState()
{
	ARPlayerState* playerState = Cast<ARPlayerState>(GetPlayerState());
	if (playerState)
	{
		attributeComp->SetCredit(playerState->GetCredit());
	}
}

void ARCharacter::SpawnUI()
{
	if (!IsLocallyControlled())
	{
		return ;
	}

	if (!playerUIInstance)
	{
		playerUIInstance = CreateWidget<UUserWidget>(GetWorld(),playerUIClass);
	}
	
	

	playerUIInstance->AddToViewport();
	
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
	actionComp->StartActionByName(this,"PrimaryAttack");
	/*PlayAnimMontage(primaryAttackAnimation);
	GetWorld()->GetTimerManager().SetTimer(primaryAttackHandle,this,&ARCharacter::PrimaryAttack_Elasped,0.17f);*/
	//
	
}


void ARCharacter::PrimaryInteract()
{
	interactComp->PrimaryInteract();
}



void ARCharacter::Dash()
{
	//actionComp->StartActionByName(this,"Dash");
	PlayAnimMontage(primaryAttackAnimation);
	FTimerHandle Temp_TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(Temp_TimerHandle,this,&ARCharacter::TempElasped,0.17f);
	
	/*UE_LOG(LogTemp,Log,TEXT("Dash"));
	PlayAnimMontage(primaryAttackAnimation);
	GetWorld()->GetTimerManager().SetTimer(dashTimerHandle,this,&ARCharacter::Dash_Elasped,0.17f);*/
}

void ARCharacter::TempElasped()
{
	FVector tempLocation = GetMesh()->GetSocketLocation(HandSocketName);
	FRotator tempRotation = GetActorRotation();
	ARGideon_Portal* portal1 = GetWorld()->SpawnActor<ARGideon_Portal>(Portal,tempLocation,tempRotation);
	ARGideon_Portal* portal2 = GetWorld()->SpawnActor<ARGideon_Portal>(Portal,tempLocation + tempRotation.Vector()*1500,tempRotation);

	portal1->BindingPortal = portal2;
	portal2->BindingPortal = portal1;
}

void ARCharacter::BlackHole()
{
	if (attributeComp->ApplyRageChange(this,blackHoleCostRage))
	{
		actionComp->StartActionByName(this,"BlackHole");
	}
	
	/*PlayAnimMontage(primaryAttackAnimation);
	GetWorld()->GetTimerManager().SetTimer(blackHoleTimerHandle,this,&ARCharacter::BlackHole_Elasped,0.17f);*/
}

void ARCharacter::SprintStart()
{
	actionComp->StartActionByName(this,"Sprint");
}

void ARCharacter::SprintStop()
{
	actionComp->StopActionByName(this,"Sprint");
}

void ARCharacter::HealSelf(float delta)
{
	attributeComp->ApplyHealthChange(this,delta);
}

void ARCharacter::OnCreditChanged(AActor* InstigatorActor, URAttributeComponent* OwningComp, int NewCredit, int Delta)
{
	ARPlayerState* playerState = Cast<ARPlayerState>(GetPlayerState());
	if (playerState)
	{
		LogOnScreen(this,"Find PlayerState");
		playerState->SetCredit(NewCredit);
	}
	else
	{
		LogOnScreen(this,"Failed To Find PlayerState");
	}
}

void ARCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	attributeComp->OnHealthChange.AddDynamic(this,&ARCharacter::OnHealthChange);

	attributeComp->OnCreditChanged.AddDynamic(this,&ARCharacter::OnCreditChanged);
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

	InputComponent->BindAction("Sprint",IE_Pressed,this,&ARCharacter::SprintStart);
	InputComponent->BindAction("Sprint",IE_Released,this,&ARCharacter::SprintStop);
}

