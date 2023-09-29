// Fill out your copyright notice in the Description page of Project Settings.


#include "RMonsterData.h"

FPrimaryAssetId URMonsterData::GetPrimaryAssetId() const
{
	return FPrimaryAssetId("Monsters",GetFName());
}
