// Fill out your copyright notice in the Description page of Project Settings.


#include "RCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ObjectStringName.h"
#include "RActionComponent.h"
#include "RAttributeComponent.h"
#include "RInputAbilityConfig.h"
#include "RInputMoveConfig.h"
#include "RInteractionComponent.h"
#include "RPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
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

	ActionComp = CreateDefaultSubobject<URActionComponent>("ActionComponent");
	GetCharacterMovement()->bOrientRotationToMovement = true;

	springArmComp->bUsePawnControlRotation = true;

	
    bUseControllerRotationYaw = false;

	
	PressF = false;
	PressE = false;
	PressQ = false;
	PressR = false;
	PressLeftbutton = false;

	springArmComp->SetRelativeLocation(FVector(0,0,60));
	springArmComp->TargetArmLength = 190;
	springArmComp->SocketOffset = FVector(-100,90,20);
	SetReplicates(true);
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
	//SetALSMovingAction_Implementation(EMovementAction::ALS_MovementState_Walk);
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



void ARCharacter::PrimaryAttack(const FInputActionValue& InputActionValue)
{
	ActionComp->StartActionByName(this,"PrimaryAttack");
	/*PlayAnimMontage(primaryAttackAnimation);
	GetWorld()->GetTimerManager().SetTimer(primaryAttackHandle,this,&ARCharacter::PrimaryAttack_Elasped,0.17f);*/
	//
}


void ARCharacter::PrimaryInteract()
{
	interactComp->PrimaryInteract();
}


void ARCharacter::AbilityF_Start()
{
	ActionComp->StartActionByName(this,Gideon_Portal);
}

void ARCharacter::AbilityF_Stop()
{
	ActionComp->StopActionByName(this,Gideon_Portal);
}

void ARCharacter::AbilityE_Start(const FInputActionValue& InputActionValue)
{
	
	ActionComp->StartActionByName(this,Gideon_BlackHole);
	
	
	/*PlayAnimMontage(primaryAttackAnimation);
	GetWorld()->GetTimerManager().SetTimer(blackHoleTimerHandle,this,&ARCharacter::BlackHole_Elasped,0.17f);*/
}

void ARCharacter::AbilityE_Stop(const FInputActionValue& InputActionValue)
{
	ActionComp->StopActionByName(this,Gideon_BlackHole);
}

void ARCharacter::SprintStart(const FInputActionValue& InputActionValue)
{
	ActionComp->StartActionByName(this,Sprint);
}

void ARCharacter::SprintStop(const FInputActionValue& InputActionValue)
{
	
	ActionComp->StopActionByName(this,Sprint);
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

void ARCharacter::OnActionStart(URActionComponent* OwningComp, URAction* Action)
{
	switch (Action->ActionKey)
	{
	case 'F':
		PressF = true;
		break;
	case 'E':
		PressE = true;
		break;
	case 'Q':
		PressQ = true;
		break;
	case 'R':
		PressR = true;
		break;
	default:
		PressLeftbutton = true;
			
	}
}

void ARCharacter::OnActionStop(URActionComponent* OwningComp, URAction* Action)
{
	switch (Action->ActionKey)
	{
	case 'F':
		FResult = Action->AbilityResult;
		PressF = false;
		break;
	case 'E':
		EResult = Action->AbilityResult;
		PressE = false;
		break;
	case 'Q':
		QResult = Action->AbilityResult;
		PressQ = false;
		break;
	case 'R':
		RResult = Action->AbilityResult;
		PressR = false;
		break;
	default:
		PressLeftbutton = false;
	}
}

void ARCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	attributeComp->OnHealthChange.AddDynamic(this,&ARCharacter::OnHealthChange);

	attributeComp->OnCreditChanged.AddDynamic(this,&ARCharacter::OnCreditChanged);
	
	ActionComp->OnActionStarted.AddDynamic(this,&ARCharacter::OnActionStart);

	ActionComp->OnActionStoped.AddDynamic(this,&ARCharacter::OnActionStop);
	
	//UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(GetController()->GetComponentByClass(UEnhancedInputComponent::StaticClass()));
	
	
}

void ARCharacter::Input_Jump(const FInputActionValue& InputActionValue)
{
	//UE_LOG(LogTemp,Log,TEXT("Input_Jump"));
	//ActionComp->StartActionByName(this,"Jump");
	if (!attributeComp->IsSprintting())
	{
		Jump();
	}
	//SetALSMovementAction_Implementation(EMovementAction::ALS_MovementAction_Jump);
	
}

void ARCharacter::Input_TurnHorizon(const FInputActionValue& InputActionValue)
{
	AddControllerYawInput(InputActionValue.Get<float>());
}

void ARCharacter::Input_TurnUp(const FInputActionValue& InputActionValue)
{
	AddControllerPitchInput(-InputActionValue.Get<float>());
}

void ARCharacter::SetCharacterSpeedShortly(float Speed, float time)
{
	
	float CurSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = Speed;

	FTimerHandle ShortlySpeedSet_TimerHandle;
	FTimerDelegate ShortlySpeedSet_TimerDelegate;
	ShortlySpeedSet_TimerDelegate.BindUFunction(this,"CharacterSpeedSet",CurSpeed);
	GetWorld()->GetTimerManager().SetTimer(ShortlySpeedSet_TimerHandle,ShortlySpeedSet_TimerDelegate,time,false);
}

void ARCharacter::CharacterSpeedSet(float Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void ARCharacter::Q_AbilityStart(const FInputActionValue& InputActionValue)
{
	ActionComp->StartActionByName(this,Gideon_QAbility);
}

void ARCharacter::Q_AbilityStop(const FInputActionValue& InputActionValue)
{
	ActionComp->StopActionByName(this,Gideon_QAbility);
}

void ARCharacter::R_AbilityStart(const FInputActionValue& InputActionValue)
{
	ActionComp->StartActionByName(this,Gideon_RAbility);
}

void ARCharacter::R_AbilityStop(const FInputActionValue& InputActionValue)
{
	ActionComp->StopActionByName(this,Gideon_RAbility);
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

	//InputComponent->BindAction("PrimaryAttack",IE_Pressed,this,&ARCharacter::PrimaryAttack);

	InputComponent->BindAction("PrimaryInteract",IE_Pressed,this,&ARCharacter::PrimaryInteract);

	/*InputComponent->BindAction("Dash",IE_Pressed,this,&ARCharacter::Dash_Start);

	InputComponent->BindAction("Dash",IE_Released,this,&ARCharacter::Dash_Stop);*/
	

	//InputComponent->BindAction("BlackHole",IE_Pressed,this,&ARCharacter::BlackHole);

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
	Input->BindAction(InputAbilityAction->PrimaryAttack,ETriggerEvent::Triggered,this,&ARCharacter::PrimaryAttack);
	//Input->BindAction(InputAbilityAction->F_Ability,ETriggerEvent::Triggered,this,&ARCharacter::Dash);
	//Input->BindAction(InputAbilityAction->Q_Ability,ETriggerEvent::Triggered,this,&ARCharacter::BlackHole);
	Input->BindAction(InputAbilityAction->F_Ability,ETriggerEvent::Triggered,this,&ARCharacter::AbilityF_Start);
	Input->BindAction(InputAbilityAction->FStop_Ability,ETriggerEvent::Triggered,this,&ARCharacter::AbilityF_Stop);
	Input->BindAction(InputAbilityAction->E_Ability,ETriggerEvent::Triggered,this,&ARCharacter::AbilityE_Start);
	Input->BindAction(InputAbilityAction->EStop_Ability,ETriggerEvent::Triggered,this,&ARCharacter::AbilityE_Stop);
	Input->BindAction(InputAbilityAction->Q_Ability,ETriggerEvent::Triggered,this,&ARCharacter::Q_AbilityStart);
	Input->BindAction(InputAbilityAction->QStop_Ability,ETriggerEvent::Triggered,this,&ARCharacter::Q_AbilityStop);
	Input->BindAction(InputAbilityAction->R_Ability,ETriggerEvent::Triggered,this,&ARCharacter::R_AbilityStart);
	Input->BindAction(InputAbilityAction->RStop_Ability,ETriggerEvent::Triggered,this,&ARCharacter::R_AbilityStop);
}

void ARCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(ARCharacter,AbilityState);
	DOREPLIFETIME(ARCharacter,PressE);
	DOREPLIFETIME(ARCharacter,PressF);
	DOREPLIFETIME(ARCharacter,PressQ);
	DOREPLIFETIME(ARCharacter,PressR);
	DOREPLIFETIME(ARCharacter,PressLeftbutton);
	DOREPLIFETIME(ARCharacter,EResult);
	DOREPLIFETIME(ARCharacter,FResult);
	DOREPLIFETIME(ARCharacter,RResult);
	DOREPLIFETIME(ARCharacter,QResult);
}
