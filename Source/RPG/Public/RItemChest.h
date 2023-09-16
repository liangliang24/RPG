// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "RItemChest.generated.h"

class URAction;
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

	
public:	
	// Sets default values for this actor's properties
	ARItemChest();

protected:
	UPROPERTY(ReplicatedUsing = "OnRep_LidOpened",BlueprintReadOnly)
    bool bIsOpened;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void OnRep_LidOpened();
	
	/*
	 * 根组件
	 */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* baseMesh;

	/*
	 * 网格体
	 */
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* lidMesh;


	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* goldMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UParticleSystemComponent* goldFlash;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ExecuteWhenOpened(APawn* instigatorPawn);

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TArray<TSubclassOf<URAction>> buffs;
};
