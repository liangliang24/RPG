// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "RItemChest.generated.h"

/*
 * 宝箱，可交互Actor
 */
UCLASS()
class RPG_API ARItemChest : public AActor,public IRGameplayInterface
{
	/*
	 * 交互接口的实现
	 */
	GENERATED_BODY()
	void Interact_Implementation(APawn* instigatorPawn) override;

	bool opened;
public:	
	// Sets default values for this actor's properties
	ARItemChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	 * 根组件
	 */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* baseMesh;

	/*
	 * 网格体
	 */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* lidMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
