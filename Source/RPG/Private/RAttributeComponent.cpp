// Fill out your copyright notice in the Description page of Project Settings.


#include "RAttributeComponent.h"

#include "RActionComponent.h"
#include "RCharacter.h"
#include "RSaveGame.h"
#include "Net/UnrealNetwork.h"
#include "RPG/RPG.h"
#include "RPG/RPGGameModeBase.h"

// Sets default values for this component's properties
URAttributeComponent::URAttributeComponent()
{

	health = 100.0f;
	maxHealth = 100.0f;
	credit = 0.0f;
	rage = 0;
	haveRage = true;
	// ...

	SetIsReplicatedByDefault(true);
}

void URAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

URAttributeComponent* URAttributeComponent::GetAttributeComponent(AActor* targetActor)
{
	return targetActor?Cast<URAttributeComponent>(targetActor->GetComponentByClass(URAttributeComponent::StaticClass())):nullptr;
}

bool URAttributeComponent::GetActorAlive(AActor* targetActor)
{
	if(targetActor)
	{
		return GetAttributeComponent(targetActor)->IsAlive();
	}
	UE_LOG(LogTemp,Log,TEXT("%s no AttributeComponent"),*GetNameSafe(targetActor));
	return false;
}


void URAttributeComponent::MulticastHealthChanged_Implementation(AActor* instigatorActor, float newHealth, float delta)
{
	OnHealthChange.Broadcast(instigatorActor,this,newHealth,delta);
}

void URAttributeComponent::MulticastCreditChanged_Implementation(AActor* instigatorActor, int newCredit, int delta)
{
	//LogOnScreen(GetOwner(),FString::Printf(TEXT("Credit is %d"),credit),FColor::Red,0);
	OnCreditChanged.Broadcast(instigatorActor,this,newCredit,delta);
}

void URAttributeComponent::MulticastRageChanged_Implementation(AActor* instigatorActor, int newRage, int delta)
{
	OnRageChanged.Broadcast(instigatorActor,this,newRage,delta);
}

bool URAttributeComponent::IsAlive() const
{
	return health>0;
}

bool URAttributeComponent::IsStunned() const
{
	ARCharacter* Owner = Cast<ARCharacter>(GetOwner());

	if (Owner)
	{
		return Owner->actionComp->activeGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("Status.Stunned"));
	}
	return false;
}

bool URAttributeComponent::IsSprintting() const
{
	ARCharacter* Owner = Cast<ARCharacter>(GetOwner());

	if (Owner)
	{
		return Owner->actionComp->activeGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("Action.Sprinting"));
	}
	return false;
}

bool URAttributeComponent::ApplyHealthChange(AActor* instigatorActor, float delta)
{
	if (!GetOwner()->HasAuthority())
	{
		return false;
	}
	if (health <= 0)
	{
		return false;
	}
	if (delta < 0)
	{
		delta*=CVarDamageMultiplier.GetValueOnGameThread();
	}
	health+=delta;
	health = FMath::Clamp(health,0,maxHealth);
	MulticastHealthChanged(instigatorActor,health,delta);
	//OnHealthChange.Broadcast(instigatorActor,this,health,delta);
	UE_LOG(LogTemp,Log,TEXT("Owner:%s Health:%f"),*GetNameSafe(GetOwner()),health);
	if(health <= 0)
	{
		ARPGGameModeBase* GM = GetWorld()->GetAuthGameMode<ARPGGameModeBase>();
		if(GM)
		{
			GM->OnActorKill(GetOwner(),instigatorActor);
		}
	}
	return true;
}

bool URAttributeComponent::ApplyCreditChange(AActor* instigatorActor, int delta)
{
	if (credit + delta < 0)
	{
		return false;
	}
	credit+=delta;
	MulticastCreditChanged(instigatorActor,credit,delta);
	//OnCreditChanged.Broadcast(instigatorActor, this, credit, delta);

	return true;
}

bool URAttributeComponent::ApplyRageChange(AActor* instigatorActor, int delta)
{
	
	if (!haveRage)
	{
		return false;
	}

	if (rage + delta < 0)
	{
		return false;
	}
	rage+=delta;
	rage = FMath::Clamp(rage,0,100);
	MulticastRageChanged(instigatorActor,rage,delta);
	//OnRageChanged.Broadcast(instigatorActor,this,rage,delta);
	return true;
}

float URAttributeComponent::GetHealth()
{
	return health;
}

bool URAttributeComponent::Kill()
{
	return ApplyHealthChange(nullptr,-maxHealth);
}

void URAttributeComponent::SetCredit(int in)
{
	credit = in;
}


void URAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URAttributeComponent,health);
	//DOREPLIFETIME(URAttributeComponent,maxHealth);

	DOREPLIFETIME_CONDITION(URAttributeComponent,maxHealth,COND_OwnerOnly)

	DOREPLIFETIME(URAttributeComponent,credit);
	DOREPLIFETIME(URAttributeComponent,rage);
}
