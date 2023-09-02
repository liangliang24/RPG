// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RAICharacter.generated.h"

class URWorldUserWidget;
class URAttributeComponent;
class UPawnSensingComponent;

/*
 * NPC，由AI控制
 */
UCLASS()
class RPG_API ARAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	// Sets default values for this character's properties
	ARAICharacter();

	

protected:
	URWorldUserWidget* healthBar;
	/*
	* AI感知组件
	*/
	UPROPERTY(VisibleAnywhere,Category="Components")
	UPawnSensingComponent* pawnSensingComp;
	FName materialParamName;
	UPROPERTY(EditAnywhere,Category="UI")
	TSubclassOf<UUserWidget> healthBarWidget;

	/*
	 * 当AI看见Pawn时候的反应
	 */
	UFUNCTION()
	void OnSeePawn(APawn* Pawn);


	
	UFUNCTION()
	void OnHealthChange(AActor* InstigatorActor, URAttributeComponent* OwningComp, float NewHealth, float Delta);
	
	UPROPERTY(EditDefaultsOnly)
	URAttributeComponent* attributeComp;

	
public:
	
	void Die();
	virtual void PostInitializeComponents() override;
};
