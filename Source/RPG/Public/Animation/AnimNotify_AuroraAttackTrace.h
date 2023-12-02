// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotify_AuroraAttackTrace.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UAnimNotify_AuroraAttackTrace : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UAnimNotify_AuroraAttackTrace();
protected:
	TArray<AActor*> HitActors;

	//USkeletalMeshComponent* OwnerMeshComp;
	USkeletalMeshSocket const* Mid;
	USkeletalMeshSocket const* Tip;
	FVector MidLastLocation;
	FVector TipLastLocation;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
