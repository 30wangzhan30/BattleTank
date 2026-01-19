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

void APlayerTankStateBase::OnGameDataChanged(EGameDataChangeType ChangeType, int32 NewValue)
{
}


// 增加击杀数
 
void APlayerTankStateBase::AddKillCount(int32 Count )
{
	SessionData.TankKillCount += Count;
	AddScore(Count * 100);
	OnKillCountChanged.Broadcast(SessionData.TankKillCount);
}

 
void APlayerTankStateBase::AddItemCount(int32 Count )
{
	SessionData.ItemCount += Count;
	AddScore(Count * 50);
	OnItemCountChanged.Broadcast(SessionData.ItemCount);
}

// 记录通关时间（ 
 
void APlayerTankStateBase:: RecordLevelClearTime(float Time)
{
	SessionData.LevelClearTime = Time;
	 
       
}

// 增加得分 
 
void APlayerTankStateBase::AddScore(int32 ScoreToAdd  )
{
	SessionData.Score += ScoreToAdd;
	OnScoreChanged.Broadcast(SessionData.Score);
}

// 重置单局数据（关卡切换时调用）
 
void APlayerTankStateBase::ResetSessionData()
{
	SessionData = FGameSessionData(); // 重置为默认值
	OnScoreChanged.Broadcast(0);
	OnKillCountChanged.Broadcast(0);
	OnItemCountChanged.Broadcast(0);
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