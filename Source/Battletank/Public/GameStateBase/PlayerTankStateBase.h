// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"     
#include "Pawn/PlayerTank.h"
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
	Score,
	blood
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
    FGameSessionData GetSessionData(int32 PlayerIndex) const { return PlayerSessionDatas[PlayerIndex]; }
	 
    // 增加击杀数
    UFUNCTION(BlueprintCallable, Category = "TankGameData")
    void AddKillCount(int32 PlayerIndex,int32 Count = 1);
   

    // 增加道具 
    UFUNCTION(BlueprintCallable, Category = "TankGameData")
    void AddItemCount(int32 PlayerIndex,int32 Count = 1);
    

    // 记录通关时间（同时根据时间奖励得分）
    UFUNCTION(BlueprintCallable, Category = "TankGameData")
    void RecordLevelClearTime(int32 PlayerIndex,float Time);
   

    // 增加得分 
    UFUNCTION(BlueprintCallable, Category = "TankGameData")
    void AddScore( int32 PlayerIndex,int32 ScoreToAdd = 10);
   
    UFUNCTION(BlueprintCallable, Category = "TankGameData")
	void AddBlood( int32 PlayerIndex,int32 bloodToAdd);
	
	UFUNCTION(BlueprintCallable, Category = "TankGameData")
	void AddATK( int32 PlayerIndex,int32 atkToAdd); 
	
	UFUNCTION(BlueprintCallable, Category = "TankGameData")
	void AddATKSpeed(int32 PlayerIndex, int32 atkspeedToAdd);
	
	UFUNCTION(BlueprintCallable, Category = "TankGameData")
	void  cantbeattack(int32 PlayerIndex);
    // 重置单局数据（关卡切换时调用）
    UFUNCTION(BlueprintCallable, Category = "TankGameData")
    void ResetSessionData(int32 PlayerIndex);
	
	
	//监听敌人销毁的回调函数
    //	UFUNCTION()
    	//void OnEnemyDestroyed(AActor* DestroyedActor);
	
	
	// 事件委托定义
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int32, NewScore);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKillCountChanged, int32, NewCount);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemCountChanged, int32, NewItemCount);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBloodChanged, int32, NewItemCount);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAtkChanged, int32, NewItemCount);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAtkSpeedChanged, int32, NewItemCount);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOncanbeattackChanged, int32, NewItemCount);     
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyChanged, int32, NewItemCount);     
    // ========== 数据变化事件（UI绑定刷新） ==========
    UPROPERTY(BlueprintAssignable, Category = "TankGameData")
    FOnScoreChanged OnScoreChanged;

    UPROPERTY(BlueprintAssignable, Category = "TankGameData")
    FOnKillCountChanged OnKillCountChanged;
	
    UPROPERTY(BlueprintAssignable, Category = "TankGameData")
    FOnItemCountChanged OnItemCountChanged;

	UPROPERTY(BlueprintAssignable, Category = "TankGameData")
	FOnBloodChanged OnbloodChanged;
   
	UPROPERTY(BlueprintAssignable, Category = "TankGameData")
	FOnAtkChanged OnAtkChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "TankGameData")
	FOnAtkSpeedChanged OnAtkSpeedChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "TankGameData")
	FOncanbeattackChanged OncanbeattackChanged ;
	
	UPROPERTY(BlueprintAssignable, Category = "TankGameData")
	FOncanbeattackChanged OnEnemyChanged ;
	 
	TArray<FGameSessionData> PlayerSessionDatas;
    //FGameSessionData SessionData;
};
 