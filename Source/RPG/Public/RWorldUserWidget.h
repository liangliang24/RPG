// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RWorldUserWidget.generated.h"

class USizeBox;
/**
 * 
 */
UCLASS()
class RPG_API URWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditDefaultsOnly,Category="UI")
	FVector positionOffset;
	UPROPERTY(meta = (BindWidget))
	USizeBox* parentSizeBox;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	UPROPERTY(BlueprintReadOnly,Category = "UI", meta = (ExposeOnSpawn = true))
	AActor* attachedActor;
};
