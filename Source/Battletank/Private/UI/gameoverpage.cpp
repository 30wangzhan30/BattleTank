// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/gameoverpage.h"
#include "Components/TextBlock.h"
#include "GameStateBase/PlayerTankStateBase.h"
#include "Pawn/PlayerTank.h"

void Ugameoverpage::NativeConstruct()
{
	Super::NativeConstruct();
	 
	// 获取游戏状态
	  GameState = GetWorld() ? Cast<APlayerTankStateBase>(GetWorld()->GetGameState()) : nullptr;
	if (GameState)
	{
		GameState->OnKillCountChanged.AddDynamic(this, &Ugameoverpage::OnKillCountReceived);
		GameState->OnItemCountChanged.AddDynamic(this, &Ugameoverpage::OnItemCountReceived);
		GameState->OnScoreChanged.AddDynamic(this, &Ugameoverpage::OnScoreReceived);
	}
}

// 接收击杀数 → 调用通用更新函数
void Ugameoverpage::OnKillCountReceived(int32 NewKillCount)
{
	OnGameDataChanged(EGameDataChangeType::KillCount, NewKillCount);
}

// 接收道具数 → 调用通用更新函数
void Ugameoverpage::OnItemCountReceived(int32 NewItemCount)
{
	OnGameDataChanged(EGameDataChangeType::ItemCount, NewItemCount);
}

// 接收得分 → 调用通用更新函数
void Ugameoverpage::OnScoreReceived(int32 NewScore)
{
	OnGameDataChanged(EGameDataChangeType::Score, NewScore);
}
 
void Ugameoverpage::OnGameDataChanged(EGameDataChangeType ChangeType, int32 NewValue)
{
	// 在这里根据ChangeType处理数据变化
	//  更新UI文本 
	switch (ChangeType)
	{
	case EGameDataChangeType::KillCount:
		 
		break;
	case EGameDataChangeType::ItemCount:
		 
		break;
	case EGameDataChangeType::Score:
		int32 CurrentScore = GameState->GetSessionData(1).Score; 
		//  把整数转为 FText 类型（SetText 要求的参数类型）
		FText ScoreText = FText::AsNumber(CurrentScore);
		// 设置文本
		Text_ScoreItem1->SetText(ScoreText);
		 
		break;
 
	}
}


void Ugameoverpage::BindSettlementData(const FString& HiScore, const FString& Stage, const FString& PlayerScore,
                                       const TArray<FString>& ScoreItems, const TArray<FString>& ItemCounts, const FString& TotalScore)
{
}
  
 