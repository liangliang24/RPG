// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AuroraAttackTrace.h"

#include "RAttributeComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/KismetSystemLibrary.h"


UAnimNotify_AuroraAttackTrace::UAnimNotify_AuroraAttackTrace()
{
	
}

void UAnimNotify_AuroraAttackTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	Base = MeshComp->GetSocketByName("Sword_Base");
	Mid = MeshComp->GetSocketByName("Sword_Mid");
	Tip = MeshComp->GetSocketByName("Sword_Tip");

	BaseLastLocation = Base->GetSocketLocation(MeshComp);
	MidLastLocation = Mid->GetSocketLocation(MeshComp);
	TipLastLocation = Tip->GetSocketLocation(MeshComp);
	
}

void UAnimNotify_AuroraAttackTrace::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);


	FCollisionShape MidCollisionShape;
	MidCollisionShape.SetBox(FVector3f(10,50,5));
	FCollisionQueryParams Params;
	Params.AddIgnoredActors(HitActors);
	Params.AddIgnoredActor(MeshComp->GetOwner());
	TArray<FHitResult> HitResult;
	MeshComp->GetWorld()->SweepMultiByChannel(
		HitResult,
		TipLastLocation,
		Tip->GetSocketLocation(MeshComp),
		FQuat(MeshComp->GetComponentRotation()),
		ECC_Pawn,
		MidCollisionShape,
		Params);
	/*TArray<FHitResult> temp;
	UKismetSystemLibrary::BoxTraceMulti(MeshComp->GetWorld(),
		MidLastLocation,
		Mid->GetSocketLocation(MeshComp),
		FVector(10,50,5),
		MeshComp->GetComponentRotation(),
		TraceTypeQuery1,
		false,
		HitActors,
		EDrawDebugTrace::ForDuration,
		temp,
		true);UKismetSystemLibrary::BoxTraceMulti(MeshComp->GetWorld(),
		TipLastLocation,
		Tip->GetSocketLocation(MeshComp),
		FVector(10,20,5),
		MeshComp->GetComponentRotation(),
		TraceTypeQuery1,
		false,
		HitActors,
		EDrawDebugTrace::ForDuration,
		temp,
		true);UKismetSystemLibrary::BoxTraceMulti(MeshComp->GetWorld(),
		BaseLastLocation,
		Base->GetSocketLocation(MeshComp),
		FVector(10,20,5),
		MeshComp->GetComponentRotation(),
		TraceTypeQuery1,
		false,
		HitActors,
		EDrawDebugTrace::ForDuration,
		temp,
		true);*/
	for (FHitResult& i:HitResult)
	{
		
		AActor* HitActor = i.GetActor();
		if (HitActor&&!HitActors.Contains(HitActor))
		{
			HitActors.Add(HitActor);
			//DrawDebugBox(MeshComp->GetWorld(),HitActor->GetActorLocation(),FVector(5,20,5),FColor::Red,false,2,0,8);
			URAttributeComponent* HitAttribute = URAttributeComponent::GetAttributeComponent(HitActor);
			if (HitAttribute)
			{
				HitAttribute->ApplyHealthChange(HitActor,-20);
			}
		}
	}

	HitResult.Empty();

	FCollisionShape TipCollisionShape;
	TipCollisionShape.SetBox(FVector3f(10,20,5));
	MeshComp->GetWorld()->SweepMultiByChannel(
		HitResult,
		TipLastLocation,
		Tip->GetSocketLocation(MeshComp),
		FQuat(MeshComp->GetComponentRotation()),
		ECC_Pawn,
		TipCollisionShape,
		Params);
	for (FHitResult& i:HitResult)
	{
		//DrawDebugBox(MeshComp->GetWorld(),Tip->GetSocketLocation(MeshComp),FVector(5,20,5),FColor::Red,false,2,0,16);
		AActor* HitActor = i.GetActor();
		if (HitActor&&!HitActors.Contains(HitActor))
		{
			//DrawDebugBox(MeshComp->GetWorld(),HitActor->GetActorLocation(),FVector(5,20,5),FColor::Red,false,2,0,8);
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
		BaseLastLocation,
		Base->GetSocketLocation(MeshComp),
		FQuat(MeshComp->GetComponentRotation()),
		ECC_Pawn,
		TipCollisionShape,
		Params);

	for (FHitResult& i:HitResult)
	{
		//DrawDebugBox(MeshComp->GetWorld(),Base->GetSocketLocation(MeshComp),FVector(5,20,5),FColor::Red,false,2,0,16);
		AActor* HitActor = i.GetActor();
		if (HitActor&&!HitActors.Contains(HitActor))
		{
			//DrawDebugBox(MeshComp->GetWorld(),HitActor->GetActorLocation(),FVector(5,20,5),FColor::Red,false,2,0,8);
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
