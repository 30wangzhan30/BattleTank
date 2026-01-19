// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Pawn/PlayerTank.h"
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PlayerTankStateBase.generated.h"

enum EGameState
{
	GameUI,Game,GameOver
	
};

UCLASS()
class BATTLETANK_API APlayerTankStateBase : public AGameStateBase
{
	GENERATED_BODY()
	public:
	int32 Gamestore;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	APlayerTankStateBase ();
	
	void addscore();
	void resetscore();
	int getgamescore() const{return Gamestore;};
	
	 
    
	 
    float GameSpeed; 
    
    EGameState CurrentGameState;
	
	
    void ChangeBirdState(EGameState NewState);
	
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int32, NewScore);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKillCountChanged, int32, NewCount);
 

 
	
	
	
	
	
	
    // ========== 数据操作接口（供GameModeBase调用） ==========
    // 获取单局数据
    UFUNCTION(BlueprintCallable, Category = "TankGameData")
    FGameSessionData GetSessionData() const { return SessionData; }

    // 增加击杀数
    UFUNCTION(BlueprintCallable, Category = "TankGameData")
    void AddKillCount(int32 Count = 1)
    {
        SessionData.TankKillCount += Count;
        AddScore(Count * 100);
        OnKillCountChanged.Broadcast(SessionData.TankKillCount);
    }

    // 增加道具（同时加分：1本=50分）
    UFUNCTION(BlueprintCallable, Category = "TankGameData")
    void AddItemCount(int32 Count = 1)
    {
        SessionData.ItemCount += Count;
        AddScore(Count * 50);
        OnItemCountChanged.Broadcast(SessionData.ItemCount);
    }

    // 记录通关时间（同时根据时间奖励得分）
    UFUNCTION(BlueprintCallable, Category = "TankGameData")
    void RecordLevelClearTime(float Time)
    {
        SessionData.LevelClearTime = Time;
        // 时间越短，得分越高
        if (Time <= 60.0f) AddScore(500);   // 60秒内通关：+500
        else if (Time <= 120.0f) AddScore(200); // 2分钟内通关：+200
        else AddScore(100);                  // 超过2分钟：+100
    }

    // 增加得分（核心方法）
    UFUNCTION(BlueprintCallable, Category = "TankGameData")
    void AddScore(int32 ScoreToAdd = 10)
    {
        SessionData.Score += ScoreToAdd;
        OnScoreChanged.Broadcast(SessionData.Score);
    }

    // 重置单局数据（关卡切换时调用）
    UFUNCTION(BlueprintCallable, Category = "TankGameData")
    void ResetSessionData()
    {
        SessionData = FGameSessionData(); // 重置为默认值
        OnScoreChanged.Broadcast(0);
        OnKillCountChanged.Broadcast(0);
        OnItemCountChanged.Broadcast(0);
    }

    // ========== 数据变化事件（UI绑定刷新） ==========
    UPROPERTY(BlueprintAssignable, Category = "TankGameData")
    FOnScoreChanged OnScoreChanged;

    UPROPERTY(BlueprintAssignable, Category = "TankGameData")
    FOnKillCountChanged OnKillCountChanged;

    // 道具数量变化事件
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemCountChanged, int32, NewCount);
    UPROPERTY(BlueprintAssignable, Category = "TankGameData")
    FOnItemCountChanged OnItemCountChanged;

 

private:
    
    FGameSessionData SessionData;
};
 