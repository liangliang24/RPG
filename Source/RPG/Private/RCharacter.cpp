// Fill out your copyright notice in the Description page of Project Settings.


#include "RCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "RActionComponent.h"
#include "RAttributeComponent.h"
#include "RInputMoveConfig.h"
#include "RInteractionComponent.h"
#include "RPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "RPG/RPG.h"

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

void ARCharacter::P(const FInputActionInstance& InputActionInstance)
{
	LogOnScreen(this,"P");
	
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


void ARCharacter::MoveForward(const FInputActionValue& InputActionValue)
{
	AddMovementInput(cameraComp->GetForwardVector(),InputActionValue.Get<float>());
}

void ARCharacter::MoveBackWard(const FInputActionValue& InputActionValue)
{
	AddMovementInput(cameraComp->GetForwardVector(),-InputActionValue.Get<float>());
}

void ARCharacter::MoveLeft(const FInputActionValue& InputActionValue)
{
	AddMovementInput(cameraComp->GetRightVector(),-InputActionValue.Get<float>());
}

void ARCharacter::MoveRight(const FInputActionValue& InputActionValue)
{
	AddMovementInput(cameraComp->GetRightVector(),InputActionValue.Get<float>());
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
	

	actionComp->StartActionByName(this,"Gideon_Portal");
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

void ARCharacter::SprintStart(const FInputActionValue& InputActionValue)
{
	
	
	actionComp->StartActionByName(this,"Sprint");
}

void ARCharacter::SprintStop(const FInputActionValue& InputActionValue)
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

	
	
	//UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(GetController()->GetComponentByClass(UEnhancedInputComponent::StaticClass()));
	
	
}

void ARCharacter::Input_Jump(const FInputActionValue& InputActionValue)
{
	if (InputActionValue.Get<bool>())
	{
		Jump();
	}
}

void ARCharacter::Input_TurnHorizon(const FInputActionValue& InputActionValue)
{
	AddControllerYawInput(InputActionValue.Get<float>());
}

void ARCharacter::Input_TurnUp(const FInputActionValue& InputActionValue)
{
	AddControllerPitchInput(-InputActionValue.Get<float>());
}

// Called to bind functionality to input
void ARCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/*InputComponent->BindAxis("MoveForward",this,&ARCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight",this,&ARCharacter::MoveRight);*/

	/*InputComponent->BindAxis("TurnHorizon",this,&APawn::AddControllerYawInput);

	InputComponent->BindAxis("TurnUp",this,&APawn::AddControllerPitchInput);*/

	//InputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);

	InputComponent->BindAction("PrimaryAttack",IE_Pressed,this,&ARCharacter::PrimaryAttack);

	InputComponent->BindAction("PrimaryInteract",IE_Pressed,this,&ARCharacter::PrimaryInteract);

	InputComponent->BindAction("Dash",IE_Pressed,this,&ARCharacter::Dash);

	InputComponent->BindAction("BlackHole",IE_Pressed,this,&ARCharacter::BlackHole);

	/*InputComponent->BindAction("Sprint",IE_Pressed,this,&ARCharacter::SprintStart);
	InputComponent->BindAction("Sprint",IE_Released,this,&ARCharacter::SprintStop);*/

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	//Input->BindAction(IA_P,ETriggerEvent::Triggered,this,&ARCharacter::P);
	/*Input->BindAction(IA_P,ETriggerEvent::Canceled,this,&ARCharacter::P);
	Input->BindAction(IA_P,ETriggerEvent::Completed,this,&ARCharacter::P);
	Input->BindAction(IA_P,ETriggerEvent::None,this,&ARCharacter::P);
	Input->BindAction(IA_P,ETriggerEvent::Ongoing,this,&ARCharacter::P);*/
	Input->BindAction(IA_P,ETriggerEvent::Triggered,this,&ARCharacter::P);

	Input->BindAction(InputMoveAction->Forward,ETriggerEvent::Triggered,this,&ARCharacter::MoveForward);
	Input->BindAction(InputMoveAction->BackWard,ETriggerEvent::Triggered,this,&ARCharacter::MoveBackWard);
	Input->BindAction(InputMoveAction->Left,ETriggerEvent::Triggered,this,&ARCharacter::MoveLeft);
	Input->BindAction(InputMoveAction->Right,ETriggerEvent::Triggered,this,&ARCharacter::MoveRight);
	Input->BindAction(InputMoveAction->Jump,ETriggerEvent::Triggered,this,&ARCharacter::Input_Jump);
	Input->BindAction(InputMoveAction->TurnHorizon,ETriggerEvent::Triggered,this,&ARCharacter::Input_TurnHorizon);
	Input->BindAction(InputMoveAction->TurnUp,ETriggerEvent::Triggered,this,&ARCharacter::Input_TurnUp);
	Input->BindAction(InputMoveAction->StartRun,ETriggerEvent::Triggered,this,&ARCharacter::SprintStart);
	Input->BindAction(InputMoveAction->StopRun,ETriggerEvent::Triggered,this,&ARCharacter::SprintStop);
}

