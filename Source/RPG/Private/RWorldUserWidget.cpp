// Fill out your copyright notice in the Description page of Project Settings.


#include "RWorldUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"

void URWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	if (!IsValid(attachedActor))
	{
		RemoveFromParent();
		return ;
	}
	FVector2D screenPosition;
	//将玩家在3D世界的位置转换成屏幕中的位置输出至ScreenPosition，并返回转换结果
	if(UGameplayStatics::ProjectWorldToScreen(
		GetOwningPlayer(),
		attachedActor->GetActorLocation()+positionOffset,
		screenPosition))
	{
		//获取比例
		float scale = UWidgetLayoutLibrary::GetViewportScale(this);

		//将UI显示的位置调整至正确的比例
		if (scale > 0)
		{
			screenPosition/=scale;
		}
		

		if (parentSizeBox)
		{
			parentSizeBox->SetRenderTranslation(screenPosition);
		}
	}
}
