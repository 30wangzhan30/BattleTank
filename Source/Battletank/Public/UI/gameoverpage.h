// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
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
	UTextBlock* num1;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* num2;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* num3;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* num4;

 
};
