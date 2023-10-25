// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/RAction_Aim.h"

#include "RCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "RPG/RPG.h"

URAction_Aim::URAction_Aim()
{
	ActionName = "Aim";

	DecalSize = FVector(100.0f,100.0f,100.0f);
}

void URAction_Aim::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ARCharacter* owner = Cast<ARCharacter>(Instigator);
	
	SpawnDecalActor(owner);
	
}

void URAction_Aim::StopAction_Implementation(AActor* instigator)
{
	Super::StopAction_Implementation(instigator);

	//ResultLocation = FVector::Zero();
	SetClientLogicStop();

	if (ResultLocation != FVector::Zero())
	{
		ResultLocation+=ResultLocationBias;
	}
	LogOnScreen(this,(TEXT("SpawnLocation:%s"),ResultLocation.ToString()));
}

void URAction_Aim::SpawnDecalActor_Implementation(ARCharacter* Instigator)
{
	InstigatorCameraComponent = Cast<UCameraComponent>(Instigator->GetComponentByClass(UCameraComponent::StaticClass()));
	DecalActor = UGameplayStatics::SpawnDecalAtLocation(this,
		PortalDecalMaterial,
		FVector(100,100,100),
		TraceAimLine(Instigator));
	
	//LogOnScreen(this,(TEXT("DecalActor Size:%s"), DecalActor->DecalSize.ToString()));
	DecalActor->DecalSize = DecalSize;
	FTimerDelegate SetDecalLocation_Delegate;
	
	SetDecalLocation_Delegate.BindUFunction(this,"SetDecalLocation",Instigator);
	GetWorld()->GetTimerManager().SetTimer(SkillTarget_TimerHandle,SetDecalLocation_Delegate,0.03f,true);
}

void URAction_Aim::SetDecalLocation_Implementation(ARCharacter* Instigator)
{
	FVector ret = TraceAimLine(Instigator);
	DecalActor->SetWorldLocation(ret);

	SetResultLocation(ret);
}

FVector URAction_Aim::TraceAimLine(ARCharacter* Instigator)
{
	FVector TraceStart = InstigatorCameraComponent
		?InstigatorCameraComponent->GetComponentLocation()
		:Instigator->GetPawnViewLocation();
	FRotator TraceRotation = InstigatorCameraComponent->GetComponentRotation();
	FVector TraceEnd = TraceStart + TraceRotation.Vector()*2000.0f;

	FHitResult hit;
	bool traceResult = GetWorld()->LineTraceSingleByChannel(hit,
	TraceStart,
	TraceEnd,
	ECC_Visibility);
	if (traceResult)
	{
		return hit.ImpactPoint;
	}
	
	return FVector::Zero();
}

void URAction_Aim::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URAction_Aim,ResultLocation)
}

void URAction_Aim::SetResultLocation_Implementation(FVector FinalLocation)
{
	ResultLocation = FinalLocation;
	//LogOnScreen(this,(TEXT("Final Location : %s"),ResultLocation.ToString()));
}

void URAction_Aim::SetClientLogicStop_Implementation()
{
	

	//SetResultLocation(DecalActor->GetComponentLocation());
	//LogOnScreen(this,(TEXT("DecalLocation : %s"),DecalActor->GetComponentLocation().ToString()));
	
	
	GetWorld()->GetTimerManager().ClearTimer(SkillTarget_TimerHandle);
	if (ensure(DecalActor))
	{
		DecalActor->DestroyComponent();
	}
	
}
