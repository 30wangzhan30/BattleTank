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
UENUM(BlueprintType)
enum class EGameDataChangeType : uint8
{
	KillCount,
	ItemCount,
	Score
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
	
	//  声明OnGameDataChanged函数
	UFUNCTION()
	void OnGameDataChanged(EGameDataChangeType ChangeType, int32 NewValue);

	 
	int getgamescore() const{return Gamestore;};
	
	 
    
	 
    float GameSpeed; 
    
    EGameState CurrentGameState;
	
	
    void ChangeBirdState(EGameState NewState);
	
	 
	
	
	
	
	
	
    // ========== 数据操作接口（供GameModeBase调用） ==========
    // 获取单局数据
    UFUNCTION(BlueprintCallable, Category = "TankGameData")
    FGameSessionData GetSessionData() const { return SessionData; }

    // 增加击杀数
    UFUNCTION(BlueprintCallable, Category = "TankGameData")
    void AddKillCount(int32 Count = 1);
   

    // 增加道具 
    UFUNCTION(BlueprintCallable, Category = "TankGameData")
    void AddItemCount(int32 Count = 1);
    

    // 记录通关时间（同时根据时间奖励得分）
    UFUNCTION(BlueprintCallable, Category = "TankGameData")
    void RecordLevelClearTime(float Time);
   

    // 增加得分 
    UFUNCTION(BlueprintCallable, Category = "TankGameData")
    void AddScore(int32 ScoreToAdd = 10);
   

    // 重置单局数据（关卡切换时调用）
    UFUNCTION(BlueprintCallable, Category = "TankGameData")
    void ResetSessionData();
   
	
	
	
	
	
	// 事件委托定义
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int32, NewScore);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKillCountChanged, int32, NewCount);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemCountChanged, int32, NewItemCount);

	 

    // ========== 数据变化事件（UI绑定刷新） ==========
    UPROPERTY(BlueprintAssignable, Category = "TankGameData")
    FOnScoreChanged OnScoreChanged;

    UPROPERTY(BlueprintAssignable, Category = "TankGameData")
    FOnKillCountChanged OnKillCountChanged;
	
    UPROPERTY(BlueprintAssignable, Category = "TankGameData")
    FOnItemCountChanged OnItemCountChanged;

 
 
    
    FGameSessionData SessionData;
};
 