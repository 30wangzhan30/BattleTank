// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Pawn/PlayerTank.h"
#include "GameInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()
public:
	// 游戏启动时加载存档
	virtual void Init() override
	{
		Super::Init();
		// 存档路径：项目/Saved/TankGameSave.json
		SaveFilePath = FPaths::ProjectSavedDir() + TEXT("TankGameSave.json");
		//LoadGameData(); // 启动时自动加载
	}

	// ========== 永久数据操作接口 ==========
	// 解锁新关卡
	UFUNCTION(BlueprintCallable, Category = "TankGameSave")
	void UnlockNewLevel(int32 Level)
	{
		if (Level > SaveData.UnlockedLevel)
		{
			SaveData.UnlockedLevel = Level;
			SaveGameData(); // 自动保存
		}
	}

	// 更新关卡最佳时间
	UFUNCTION(BlueprintCallable, Category = "TankGameSave")
	void UpdateLevelBestTime(int32 Level, float Time)
	{
		if (!SaveData.LevelBestTimes.Contains(Level) || Time < SaveData.LevelBestTimes[Level])
		{
			SaveData.LevelBestTimes.Add(Level, Time);
			SaveGameData();
		}
	}

	// 更新关卡最佳得分
	UFUNCTION(BlueprintCallable, Category = "TankGameSave")
	void UpdateLevelBestScore(int32 Level, int32 Score)
	{
		if (!SaveData.LevelBestScores.Contains(Level) || Score > SaveData.LevelBestScores[Level])
		{
			SaveData.LevelBestScores.Add(Level, Score);
			SaveGameData();
		}
	}

	// 获取永久存档数据 
	UFUNCTION(BlueprintCallable, Category = "TankGameSave")
	FGameSaveData GetSaveData() const { return SaveData; }

	// 手动保存/加载 
	UFUNCTION(BlueprintCallable, Category = "TankGameSave")
	void SaveGameData();
	//UFUNCTION(BlueprintCallable, Category = "TankGameSave")
	//void LoadGameData();

private:
	// 永久存档数据
	UPROPERTY()
	FGameSaveData SaveData;
	// 存档文件路径
	FString SaveFilePath;
	 
};
