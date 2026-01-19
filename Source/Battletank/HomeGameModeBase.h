// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameStateBase/PlayerTankStateBase.h"
#include "HomeGameModeBase.generated.h"



 
UCLASS()
class BATTLETANK_API AHomeGameModeBase : public AGameModeBase
{private:
	UPROPERTY( )
	int32 MaxBulletCount = 7;  
	UPROPERTY()
	 TArray<class ATankBullet*> BulletObjectPool; // 子弹对象池

public:
	virtual void BeginPlay() override;
	GENERATED_BODY()
	
public:
	
	AHomeGameModeBase();
	
	 
	void Addinitilize();
	void AddBulletActor(ATankBullet* BulletActor);
	ATankBullet* GetBulletObject();
	
	
	
	
	
	//关卡开始调用
	 virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override
    {
        Super::InitGame(MapName, Options, ErrorMessage);
        // 获取GameState并重置数据
//        APlayerTankStateBase* TankGameState = Cast<APlayerTankStateBase>(GetGameState());
      //  if (TankGameState)
        {
        //    TankGameState->ResetSessionData();
            
        }
    }

    // ========== 外部调用接口（坦克/道具调用） ==========
    // 坦克击杀时调用
    UFUNCTION(BlueprintCallable, Category = "TankGameMode")
    void OnTankKilled()
    {
       // APlayerTankStateBase* TankGameState = Cast<APlayerTankStateBase>(GetGameState());
      //  if (TankGameState) TankGameState->AddKillCount(1);
    }

    // 拾取道具时调用
    UFUNCTION(BlueprintCallable, Category = "TankGameMode")
    void OnItemBookCollected()
    {
       // APlayerTankStateBase* TankGameState = Cast<APlayerTankStateBase>(GetGameState());
     //   if (TankGameState) TankGameState->AddItemBookCount(1);
    }

    // 关卡通关时调用（核心逻辑）
    UFUNCTION(BlueprintCallable, Category = "TankGameMode")
    void OnLevelCompleted(float ClearTime)
    {
        // 1. 记录通关时间和得分
      //  APlayerTankStateBase* TankGameState = Cast<APlayerTankStateBase>(GetGameState());
      //  if (!TankGameState) return;
      //  TankGameState->RecordLevelClearTime(ClearTime);
      //  FGameSessionData FinalData = TankGameState->GetSessionData();

        // 2. 同步到GameInstance做永久存档
      //  UTankGameInstance* GameInstance = Cast<UTankGameInstance>(GetGameInstance());
       // if (GameInstance)
        {
          //  GameInstance->UnlockNewLevel(CurrentLevel);
          //  GameInstance->UpdateLevelBestTime(CurrentLevel, FinalData.LevelClearTime);
          //  GameInstance->UpdateLevelBestScore(CurrentLevel, FinalData.Score);
        }

        //  加通关逻辑 ,跳转下一关
       
    }

private:
    // 当前关卡号 
    int32 CurrentLevel = 1;

    

	
	
};
