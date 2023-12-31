// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RInteractionComponent.generated.h"

class URWorldUserWidget;
static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("rpg.InteractionDebugDraw"),
                                                           false,
                                                           TEXT("Enable Debug Lines for Interaction Component"),
                                                           ECVF_Cheat);
/*
 * 交互组件，拥有这个组件的物体可以和可交互物体进行交互
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API URInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URInteractionComponent();

	
	/*
	 * 普通交互操作
	 */
	void PrimaryInteract(); 
protected:

	UFUNCTION(Server,Reliable)
	void ServerInteract(AActor* focusActor);
	
	// Called when the game starts
	virtual void BeginPlay() override;
	
	void FindBestToInteract();

	UPROPERTY()
	AActor* FocusActor;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<URWorldUserWidget> defaultWidgetClass;

	UPROPERTY()
	URWorldUserWidget* defaultWidgetInstance;
	APawn* ownerPawn;

public:
	
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
