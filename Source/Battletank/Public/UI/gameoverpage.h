// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "GameStateBase/PlayerTankStateBase.h"
#include "gameoverpage.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class BATTLETANK_API Ugameoverpage : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	// 绑定单局结算数据的接口
	UFUNCTION(BlueprintCallable, Category = "ScoreSettlement")
	void BindSettlementData(const FString& HiScore, const FString& Stage, const FString& PlayerScore,
							const TArray<FString>& ScoreItems, const TArray<FString>& ItemCounts,
							const FString& TotalScore);
	
	APlayerTankStateBase* GameState;
	// ========== UI层的事件响应函数（只接收数据，不处理核心逻辑） ==========
	UFUNCTION() // 必须加UFUNCTION()，否则AddDynamic绑定失败
	void OnKillCountReceived(int32 NewKillCount); // 接收击杀数

	UFUNCTION()
	void OnItemCountReceived(int32 NewItemCount); // 接收道具数

	UFUNCTION()
	void OnScoreReceived(int32 NewScore); // 接收得分

	// 通用UI更新函数
	UFUNCTION()
	void OnGameDataChanged(EGameDataChangeType ChangeType, int32 NewValue);
private:
	 
  //玩家1score
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_PlayerScore;
  //如果有玩家2，total=1+2,没有就是单个
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_TotalScore;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StageNum;
	// 分项得分文本
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_ScoreItem1;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_ScoreItem2;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_ScoreItem3;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_ScoreItem4;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_ScoreItem1_1;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_ScoreItem1_2;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_ScoreItem1_3;
	UPROPERTY(meta = (BindWidget))
	UTextBlock*  TextBlock_11;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* num1;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* num2;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* num3;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_1026;
	UPROPERTY(meta = (BindWidget))
	UTextBlock*num1_1;
	UPROPERTY(meta = (BindWidget))
	UTextBlock*num1_2;
	UPROPERTY(meta = (BindWidget))
	UTextBlock*num1_3;
	UPROPERTY(meta = (BindWidget))
	UTextBlock*Text_TotalScore_1;
};
