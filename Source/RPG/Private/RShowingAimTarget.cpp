// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\RShowingAimTarget.h"

#include "RCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Engine/InputDelegateBinding.h"
#include "Kismet/GameplayStatics.h"


FVector UShowingAimTarget::TraceAimLine(ARCharacter* Instigator)
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
	
	return TraceEnd;
	
}

void UShowingAimTarget::Start(ARCharacter* Instigator)
{
	InstigatorCameraComponent = Cast<UCameraComponent>(Instigator->GetComponentByClass(UCameraComponent::StaticClass()));
	DecalActor = UGameplayStatics::SpawnDecalAtLocation(this,
		PortalDecalMaterial,
		FVector(100,100,100),
		FVector::Zero());

	FTimerDelegate SetDecalLocation_Delegate;
	SetDecalLocation_Delegate.BindUFunction(this,"SetDecalLocation",Instigator);
	GetWorld()->GetTimerManager().SetTimer(SkillTarget_TimerHandle,SetDecalLocation_Delegate,0.03f,true);
}

UDecalComponent* UShowingAimTarget::Stop()
{
	GetWorld()->GetTimerManager().ClearTimer(SkillTarget_TimerHandle);
	return DecalActor;
}

void UShowingAimTarget::SetDecalLocation(ARCharacter* Instigator)
{
	DecalActor->SetWorldLocation(TraceAimLine(Instigator)); 
}
