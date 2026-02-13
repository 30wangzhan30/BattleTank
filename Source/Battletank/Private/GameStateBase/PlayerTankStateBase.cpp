// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateBase/PlayerTankStateBase.h"

void APlayerTankStateBase::BeginPlay()
{
	Super::BeginPlay();
	// 玩家1（索引0）的初始数据
	PlayerSessionDatas.Add(FGameSessionData());
	// 玩家2（索引1）的初始数据
	PlayerSessionDatas.Add(FGameSessionData());
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
 
void APlayerTankStateBase::AddKillCount(int32 PlayerIndex,int32 Count )
{
	PlayerSessionDatas[PlayerIndex].TankKillCount += Count;
	AddScore(Count * 100);
	OnKillCountChanged.Broadcast(PlayerSessionDatas[PlayerIndex].TankKillCount);
}

 
void APlayerTankStateBase::AddItemCount(int32 PlayerIndex,int32 Count )
{
	PlayerSessionDatas[PlayerIndex].ItemCount += Count;
	AddScore(Count * 50);
	OnItemCountChanged.Broadcast(PlayerSessionDatas[PlayerIndex].ItemCount);
}

// 记录通关时间（ 
 
void APlayerTankStateBase:: RecordLevelClearTime(int32 PlayerIndex,float Time)
{
	PlayerSessionDatas[PlayerIndex].LevelClearTime = Time;
	 
       
}

// 增加得分 
 
void APlayerTankStateBase::AddScore(int32 PlayerIndex, int32 ScoreToAdd  )
{
	PlayerSessionDatas[PlayerIndex].Score += ScoreToAdd;
	OnScoreChanged.Broadcast(PlayerSessionDatas[PlayerIndex].Score);
}
void APlayerTankStateBase::cantbeattack(int32 PlayerIndex)
{
	PlayerSessionDatas[PlayerIndex].canbeattack=false;
	OnScoreChanged.Broadcast(PlayerSessionDatas[PlayerIndex].canbeattack);
}

void APlayerTankStateBase::AddBlood( int32 PlayerIndex,int32 bloodToAdd )
{PlayerSessionDatas[PlayerIndex].blood+=bloodToAdd;
	
	OnbloodChanged.Broadcast(PlayerSessionDatas[PlayerIndex].blood);
	 
}

void APlayerTankStateBase::AddATK( int32 PlayerIndex,int32 atkToAdd)
{PlayerSessionDatas[PlayerIndex].atk+=atkToAdd;
	OnAtkChanged .Broadcast(PlayerSessionDatas[PlayerIndex].atk);
}

void APlayerTankStateBase::	AddATKSpeed( int32 PlayerIndex,int32 atkspeedToAdd)
{PlayerSessionDatas[PlayerIndex].atkspeed+=atkspeedToAdd;
	OnAtkSpeedChanged .Broadcast(PlayerSessionDatas[PlayerIndex].atkspeed);
}
void APlayerTankStateBase::cantbeattack()
{
	SessionData.canbeattack=false;
	OnScoreChanged.Broadcast(SessionData.canbeattack);
}

void APlayerTankStateBase::AddBlood(int32 bloodToAdd )
{SessionData.blood+=bloodToAdd;
	
	OnbloodChanged.Broadcast(SessionData.blood);
	UE_LOG(LogTemp, Error, TEXT("111"));
}

void APlayerTankStateBase::AddATK(int32 atkToAdd)
{SessionData.atk+=atkToAdd;
	OnAtkChanged .Broadcast(SessionData.atk);
}

void APlayerTankStateBase::	AddATKSpeed(int32 atkspeedToAdd)
{SessionData.atkspeed+=atkspeedToAdd;
	OnAtkSpeedChanged .Broadcast(SessionData.atkspeed);
}

// 重置单局数据（关卡切换时调用）
 
void APlayerTankStateBase::ResetSessionData(int32 PlayerIndex)
{
	PlayerSessionDatas[PlayerIndex] = FGameSessionData(); // 重置为默认值
	OnScoreChanged.Broadcast(0);
	OnKillCountChanged.Broadcast(0);
	OnItemCountChanged.Broadcast(0);
	OnbloodChanged.Broadcast(1);
	OnAtkChanged.Broadcast(10);
	OnAtkSpeedChanged.Broadcast(1);
	OncanbeattackChanged.Broadcast(true);
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
