// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateBase/PlayerTankStateBase.h"

void APlayerTankStateBase::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerTankStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

APlayerTankStateBase::APlayerTankStateBase ()
{
	
}
	
void APlayerTankStateBase:: addscore()
{
	
}
void APlayerTankStateBase:: resetscore()
{
	
	
}

void APlayerTankStateBase::ChangeBirdState(EGameState NewState)
{
	CurrentGameState=NewState;
	switch (CurrentGameState)
	{
	case EGameState::GameUI:break;
	case EGameState::Game:
		break;
	case EGameState::GameOver:break;
	}
}