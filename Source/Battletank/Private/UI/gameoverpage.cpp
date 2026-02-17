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
{UE_LOG(LogTemp, Log, TEXT(" KillCount ") );
	OnGameDataChanged(EGameDataChangeType::KillCount, NewKillCount);
}

// 接收道具数 → 调用通用更新函数
void Ugameoverpage::OnItemCountReceived(int32 NewItemCount)
{
	OnGameDataChanged(EGameDataChangeType::ItemCount, NewItemCount);
}

// 接收得分 → 调用通用更新函数
void Ugameoverpage::OnScoreReceived(int32 NewScore)
{UE_LOG(LogTemp, Log, TEXT(" NewScore ") );
	OnGameDataChanged(EGameDataChangeType::Score, NewScore);
}
 
void Ugameoverpage::OnGameDataChanged(EGameDataChangeType ChangeType, int32 NewValue)
{
	// 在这里根据ChangeType处理数据变化
	//  更新UI文本 
	switch (ChangeType)
	{
	case EGameDataChangeType::KillCount:
		{ 
			int32 Currentnum = GameState->GetSessionData(0).TankKillCount; 
			FText KillcountText = FText::AsNumber(Currentnum);
			int32 Currentnum1= GameState->GetSessionData(0).KillCount1; 
			FText KillcountText1= FText::AsNumber(Currentnum1);
			int32 Currentnum2= GameState->GetSessionData(0).KillCount2; 
			FText KillcountText2= FText::AsNumber(Currentnum2);
			int32 Currentnum3= GameState->GetSessionData(0).KillCount3; 
			FText KillcountText3= FText::AsNumber(Currentnum3);
			num1->SetText(KillcountText1);
			num2->SetText(KillcountText2);
			num3->SetText(KillcountText3);
			Text_TotalScore ->SetText(KillcountText );
			
			
			int32 CurrentKillplayer2= GameState->GetSessionData(1).TankKillCount; 
			FText KillTextplayer2 = FText::AsNumber(CurrentKillplayer2);
			int32 CurrentSKill1player2= GameState->GetSessionData(1).KillCount1; 
			FText KillText1player2= FText::AsNumber(CurrentSKill1player2);
			int32 CurrentKill2player2= GameState->GetSessionData(1).KillCount2; 
			FText KillText2player2= FText::AsNumber(CurrentKill2player2);
			int32 CurrentKill3player2= GameState->GetSessionData(1).KillCount3; 
			FText KillText3player2= FText::AsNumber(CurrentKill3player2);
			num1_1->SetText(KillText1player2);
			num1_2->SetText(KillText2player2);
			num1_3->SetText(KillText3player2);
			Text_TotalScore_1 ->SetText(KillTextplayer2 );
			 
		}
		break;
	case EGameDataChangeType::ItemCount:
		break;
	case EGameDataChangeType::Score:
		{
		int32 CurrentScore = GameState->GetSessionData(0).Score; 
		FText ScoreText = FText::AsNumber(CurrentScore);
		int32 CurrentScore1= GameState->GetSessionData(0).Score1; 
		FText ScoreText1= FText::AsNumber(CurrentScore1);
		int32 CurrentScore2= GameState->GetSessionData(0).Score2; 
		FText ScoreText2= FText::AsNumber(CurrentScore2);
		int32 CurrentScore3= GameState->GetSessionData(0).Score3; 
		FText ScoreText3= FText::AsNumber(CurrentScore3);
		// 设置文本
		Text_ScoreItem1->SetText(ScoreText1);
		Text_ScoreItem2->SetText(ScoreText2);
		Text_ScoreItem3 ->SetText(ScoreText3);
		TextBlock_1026 ->SetText(ScoreText);
			
			int32 CurrentScoreplayer2= GameState->GetSessionData(1).Score; 
			FText ScoreTextplayer2 = FText::AsNumber(CurrentScoreplayer2);
			int32 CurrentScore1player2= GameState->GetSessionData(1).Score1; 
			FText ScoreText1player2= FText::AsNumber(CurrentScore1player2);
			int32 CurrentScore2player2= GameState->GetSessionData(1).Score2; 
			FText ScoreText2player2= FText::AsNumber(CurrentScore2player2);
			int32 CurrentScore3player2= GameState->GetSessionData(1).Score3; 
			FText ScoreText3player2= FText::AsNumber(CurrentScore3player2);
			Text_ScoreItem1_1->SetText(ScoreText1player2);
			Text_ScoreItem1_2->SetText(ScoreText2player2);
			Text_ScoreItem1_3->SetText(ScoreText3player2);
		    TextBlock_11 ->SetText(ScoreTextplayer2);
		}
		break;
 default:break;
	}
}


void Ugameoverpage::BindSettlementData(const FString& HiScore, const FString& Stage, const FString& PlayerScore,
                                       const TArray<FString>& ScoreItems, const TArray<FString>& ItemCounts, const FString& TotalScore)
{
}
  
 