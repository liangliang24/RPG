// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AuroraAttackTrace.h"

#include "RAttributeComponent.h"
#include "Engine/SkeletalMeshSocket.h"


UAnimNotify_AuroraAttackTrace::UAnimNotify_AuroraAttackTrace()
{
	
}

void UAnimNotify_AuroraAttackTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	Mid = MeshComp->GetSocketByName("Sword_Mid");
	Tip = MeshComp->GetSocketByName("Sword_Tip");
	
	MidLastLocation = Mid->GetSocketLocation(MeshComp);
	TipLastLocation = Tip->GetSocketLocation(MeshComp);
	
}

void UAnimNotify_AuroraAttackTrace::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);


	FCollisionShape CollisionShape;
	CollisionShape.SetBox(FVector3f(5,10,20));
	FCollisionQueryParams Params;
	Params.AddIgnoredActors(HitActors);
	TArray<FHitResult> HitResult;
	FCollisionResponseParams ResponseParam;
	MeshComp->GetWorld()->SweepMultiByChannel(
		HitResult,
		TipLastLocation,
		Tip->GetSocketLocation(MeshComp),
		FQuat(MeshComp->GetComponentRotation()),
		ECC_Pawn,
		CollisionShape,
		Params);

	for (FHitResult& i:HitResult)
	{
		AActor* HitActor = i.GetActor();
		if (HitActor&&!HitActors.Contains(HitActor))
		{
			HitActors.Add(HitActor);
			URAttributeComponent* HitAttribute = URAttributeComponent::GetAttributeComponent(HitActor);
			if (HitAttribute)
			{
				HitAttribute->ApplyHealthChange(HitActor,-20);
			}
		}
	}

	HitResult.Empty();

	MeshComp->GetWorld()->SweepMultiByChannel(
		HitResult,
		TipLastLocation,
		Tip->GetSocketLocation(MeshComp),
		FQuat(MeshComp->GetComponentRotation()),
		ECC_Pawn,
		CollisionShape,
		Params);
	for (FHitResult& i:HitResult)
	{
		AActor* HitActor = i.GetActor();
		if (HitActor&&!HitActors.Contains(HitActor))
		{
			HitActors.Add(HitActor);
			URAttributeComponent* HitAttribute = URAttributeComponent::GetAttributeComponent(HitActor);
			if (HitAttribute)
			{
				HitAttribute->ApplyHealthChange(HitActor,-20);
			}
		}
	}

	MidLastLocation = Mid->GetSocketLocation(MeshComp);
	TipLastLocation = Tip->GetSocketLocation(MeshComp);
}

void UAnimNotify_AuroraAttackTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	HitActors.Empty();
}
