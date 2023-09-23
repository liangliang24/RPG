// Fill out your copyright notice in the Description page of Project Settings.


#include "RGamePlayFunctionLibrary.h"

#include "RAttributeComponent.h"
#include "RCharacter.h"
#include "Camera/CameraComponent.h"

bool URGamePlayFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	URAttributeComponent* attributeComponent = URAttributeComponent::GetAttributeComponent(TargetActor);
	if (attributeComponent)
	{
		return attributeComponent->ApplyHealthChange(DamageCauser,DamageAmount);
	}
	return false;
}

bool URGamePlayFunctionLibrary::ApplyDirectionDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount,
	const FHitResult& HitResult)
{
	if (ApplyDamage(DamageCauser,TargetActor,DamageAmount))
	{
		
		UPrimitiveComponent* hitComp = HitResult.GetComponent();

		if (hitComp&&hitComp->IsSimulatingPhysics(HitResult.BoneName))
		{
			//UE_LOG(LogTemp,Log,TEXT("Apply hit success"));
			hitComp->AddImpulseAtLocation(-HitResult.ImpactNormal * 300000.0f,HitResult.ImpactPoint,HitResult.BoneName);
			return true;
		}
		
	}
	return false;
}


