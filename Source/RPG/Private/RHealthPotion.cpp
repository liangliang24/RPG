// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\RHealthPotion.h"

#include "RAttributeComponent.h"



// Sets default values
ARHealthPotion::ARHealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = staticMesh;
	isDie = false;

	SetReplicates(true);
}

// Called when the game starts or when spawned
void ARHealthPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARHealthPotion::Interact_Implementation(APawn* instigatorPawn)
{
	IRGameplayInterface::Interact_Implementation(instigatorPawn);

	URAttributeComponent* instigatorAttribute = Cast<URAttributeComponent>(instigatorPawn->GetComponentByClass(URAttributeComponent::StaticClass()));

	if(instigatorAttribute&&(!isDie))
	{
		UE_LOG(LogTemp,Log,TEXT("otherAttribute:%s"),*GetNameSafe(instigatorAttribute));
		if (instigatorAttribute->ApplyCreditChange(instigatorPawn, -20))
		{
			instigatorAttribute->ApplyHealthChange(this,20.0f);

			FTimerHandle timerHandle_Die;
			GetWorldTimerManager().SetTimer(timerHandle_Die,this,&ARHealthPotion::Die,3.0f);
			isDie = true;
		}
		
	}
}


void ARHealthPotion::Die()
{
	Destroy();

	
}

// Called every frame
void ARHealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

