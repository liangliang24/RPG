// Fill out your copyright notice in the Description page of Project Settings.


#include "RPlayerState.h"

#include "RSaveGame.h"
#include "RPG/RPG.h"

int ARPlayerState::GetCredit() const
{
	return credit;
}

void ARPlayerState::SetCredit(int Credit)
{
	
	this->credit = Credit;
	LogOnScreen(this,FString::Printf(TEXT("Change Credit In Player State,New is %d"),credit));
}

void ARPlayerState::LoadSaveGame_Implementation(URSaveGame* saveObject)
{
	if (saveObject)
	{
		credit = saveObject->credit;
	}
		
}

void ARPlayerState::WriteSaveGame_Implementation(URSaveGame* saveObject)
{
	if (saveObject)
		saveObject->credit = credit;
}
