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
 
void APlayerTankStateBase::AddKillCount(int32 PlayerIndex, int32 scoretoadd,int32 enemytag)
{ 
	PlayerSessionDatas[PlayerIndex].TankKillCount += 1;
	switch (enemytag)
	{
	case 1:	 
		PlayerSessionDatas[PlayerIndex].KillCount1 += 1;
		OnKillCountChanged.Broadcast(PlayerSessionDatas[PlayerIndex].KillCount1);
		AddScore(PlayerIndex,200, enemytag);
		scoretoadd=200;
		break;
	case 2:  
		PlayerSessionDatas[PlayerIndex].KillCount2 += 1;
		OnKillCountChanged.Broadcast(PlayerSessionDatas[PlayerIndex].KillCount2);
		AddScore(PlayerIndex,400, enemytag);
		scoretoadd=400;
		break;
	case 3: 
		PlayerSessionDatas[PlayerIndex].KillCount3 += 1;
		OnKillCountChanged.Broadcast(PlayerSessionDatas[PlayerIndex].KillCount3);
		AddScore(PlayerIndex,800, enemytag);
		scoretoadd=800;
		break;
		default:break;;
	}
	AddScore(PlayerIndex,scoretoadd, enemytag);
	OnKillCountChanged.Broadcast(PlayerSessionDatas[PlayerIndex].TankKillCount);
}

 
void APlayerTankStateBase::AddItemCount(int32 PlayerIndex,int32 Count )
{
	PlayerSessionDatas[PlayerIndex].ItemCount += Count;
	//AddScore( );
	OnItemCountChanged.Broadcast(PlayerSessionDatas[PlayerIndex].ItemCount);
}

// 记录通关时间（ 
 
void APlayerTankStateBase:: RecordLevelClearTime(int32 PlayerIndex,float Time)
{
	PlayerSessionDatas[PlayerIndex].LevelClearTime = Time;
	 
       
}

// 增加得分 
 
void APlayerTankStateBase::AddScore(int32 PlayerIndex, int32 ScoreToAdd ,int32 enemytag )
{PlayerSessionDatas[PlayerIndex].Score += ScoreToAdd;
	switch (enemytag)
{
case 1:	 	UE_LOG(LogTemp, Log, TEXT("1  ") );
	PlayerSessionDatas[PlayerIndex].Score1 += ScoreToAdd;
	OnScoreChanged.Broadcast(PlayerSessionDatas[PlayerIndex].Score1);

	break;
case 2:	UE_LOG(LogTemp, Log, TEXT("2 ") );
	PlayerSessionDatas[PlayerIndex].Score2 += ScoreToAdd;
	OnScoreChanged.Broadcast(PlayerSessionDatas[PlayerIndex].Score2);
	break;
case 3:	
	UE_LOG(LogTemp, Log, TEXT("3 ") );
	PlayerSessionDatas[PlayerIndex].Score3 += ScoreToAdd;
	OnScoreChanged.Broadcast(PlayerSessionDatas[PlayerIndex].Score3);
	break;
default:break;;
}
	 
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
