// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RAction.h"
#include "UObject/NoExportTypes.h"
#include "RAction_Gideon_Portal.generated.h"

class ARCharacter;
class UShowingAimTarget;
/**
 * 
 */
UCLASS()
class RPG_API URAction_Gideon_Portal : public URAction
{
	GENERATED_BODY()

public:
	bool isAiming;
	URAction_Gideon_Portal();
	UFUNCTION(Client,Reliable)
	void CreateAim();
	UFUNCTION(NetMulticast,Reliable)
	void NetMulticast_AnimationPlay(ARCharacter* Owner);
	virtual void StartAction_Implementation(AActor* instigator) override;
	virtual void StopAction_Implementation(AActor* instigator) override;


protected:
	UPROPERTY(Replicated)
	FVector Portal2SpawnLocation;
	UFUNCTION(Server,Reliable)
	void SetPortal2SpawnLocation(FVector NewLocation);
	UPROPERTY(Replicated)
	UShowingAimTarget* Aim;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UShowingAimTarget> AimTarget;
	UPROPERTY(EditDefaultsOnly,Category="Animation")
	UAnimMontage* PortalStartAnimMontage;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> Portal;

	/*UFUNCTION(Server,Reliable)
	void SpawnPortal(const FVector& Vector, const FRotator& Rotator, UDecalComponent* DecalActor);*/
	//UFUNCTION(Server,Reliable)
	UFUNCTION()
	void StartAction_Elasped(ACharacter* instigator);
	UFUNCTION(Client,Reliable)
	void AimStart(ARCharacter* Instigator);
	UFUNCTION(Client,Reliable)
	void AimStop();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
private:
};
