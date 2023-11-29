// Fill out your copyright notice in the Description page of Project Settings.


#include "RAction.h"
#include "RActionComponent.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "RPG/RPG.h"




void URAction::InitializeActionComp(URActionComponent* newActionComp)
{
	actionComp = newActionComp;
}


void URAction::PreAction_Implementation(AActor* instigatorActor)
{
	
}

void URAction::StartAction_Implementation(AActor* Instigator)
{
	//UE_LOG(LogTemp,Log,TEXT("Running:%s"),*GetNameSafe(instigator));
	//LogOnScreen(this,FString::Printf(TEXT("Running:%s"),*GetNameSafe(instigator)),FColor::Green);
	URActionComponent* Comp = GetOwningComponent();

	Comp->activeGameplayTags.AppendTags(grantTags);

	repData.bIsRunning = true;
	repData.instigator = Instigator;
	Comp->OnActionStarted.Broadcast(Comp,this);
	//LogOnScreen(this,FString::Printf(TEXT("time between:%s"),*UKismetStringLibrary::Conv_DoubleToString(GetWorld()->GetTimeSeconds()-LastTimeStart)));
}

void URAction::StopAction_Implementation(AActor* instigator)
{
	//UE_LOG(LogTemp,Log,TEXT("Stop:%s"),*GetNameSafe(instigator));
	//LogOnScreen(this,FString::Printf(TEXT("Stop:%s"),*GetNameSafe(instigator)),FColor::White);
	//ensureAlways(bIsRunning);
	
	URActionComponent* Comp = GetOwningComponent();
	
	Comp->activeGameplayTags.RemoveTags(grantTags);

	repData.bIsRunning = false;
	AbilitySuccess();
	//LogOnScreen(this,FString::Printf(TEXT("Result:%s"),AbilityResult?TEXT("true"):TEXT("false")));
	Comp->OnActionStoped.Broadcast(Comp,this);
	if (AbilityResult)
	{
		LastTimeStart = GetWorld()->GetTimeSeconds();
	}
	
}

URAction::URAction()
{
	bAutoStart = false;
	hasPreAction = false;
	ActionKey = ' ';
	LastTimeStart = 0.0f;
}

void URAction::SetAbilityResult_Implementation(bool in)
{
	AbilityResult = in;
}

void URAction::AbilitySuccess_Implementation()
{
}

URActionComponent* URAction::GetOwningComponent() const
{
	return actionComp;
}



bool URAction::IsRunning()
{
	return repData.bIsRunning;
}

void URAction::SetIsRunning_Implementation(bool in)
{
	repData.bIsRunning = in;
}

bool URAction::CanStart_Implementation(AActor* instigator)
{
	URActionComponent* comp = GetOwningComponent();

	float CurTime = UGameplayStatics::GetGameState(this)->GetServerWorldTimeSeconds();
	if ((LastTimeStart != 0&&CurTime-LastTimeStart < CD)
		||comp->activeGameplayTags.HasAny(blockedTags))
	{
		/*LogOnScreen(this,FString::Printf(TEXT("CurTime:%s,LastTimeStart:%s,Rest:%s"),
			*UKismetStringLibrary::Conv_DoubleToString(CurTime),
			*UKismetStringLibrary::Conv_DoubleToString(LastTimeStart),
			*UKismetStringLibrary::Conv_DoubleToString(CD-(CurTime-LastTimeStart))));*/
		return false;
	}
	//LogOnScreen(this,"Can Start");
	return true;
}

void URAction::ShowForAllClient_Implementation(AActor* instigator)
{
	//LogOnScreen(this,"show");
}

UWorld* URAction::GetWorld() const
{
	AActor* actor = Cast<AActor>(GetOuter());
	if (actor)
	{
		return actor->GetWorld();
	}
	return nullptr;
}

bool URAction::IsSupportedForNetworking() const
{
	return true;
}

bool URAction::CallRemoteFunction(UFunction* Function, void* Parms, FOutParmRec* OutParms, FFrame* Stack)
{
	//UObject::CallRemoteFunction(Function, Parms, OutParms, Stack);
	AActor* owner = GetTypedOuter<AActor>();
	UNetDriver* NetDriver = owner->GetNetDriver();
	if (NetDriver)
	{
		NetDriver->ProcessRemoteFunction(owner,Function,Parms,OutParms,Stack,this);
		return true;
	}
	return false;
}

int32 URAction::GetFunctionCallspace(UFunction* Function, FFrame* Stack)
{
	check(GetOuter()!=nullptr)
	return GetOuter()->GetFunctionCallspace(Function,Stack);
}


void URAction::OnRep_RepData_Implementation()
{
	
	/*LogOnScreen(repData.instigator,FString::Printf(TEXT("Onrep_RepDataImplementation,IsRunning:%s,instigator:%s"),
		repData.bIsRunning?TEXT("true"):TEXT("false"),
		*GetNameSafe(repData.instigator)));*/
	/*if (repData.bIsRunning)
	{
		StartAction(repData.instigator);
	}
	else
	{
		StopAction(repData.instigator);
	}*/
}

void URAction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URAction,repData)
	DOREPLIFETIME(URAction,actionComp)
	DOREPLIFETIME(URAction,LastTimeStart)
	DOREPLIFETIME(URAction,AbilityResult)
}


