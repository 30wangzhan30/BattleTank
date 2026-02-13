// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
 
#include "CoreMinimal.h"
#include "PaperCharacter.h"

#include "PlayerTank.generated.h"

class APlayerTankStateBase;
class UFloatingPawnMovement;
class ATankController;
struct FInputActionValue;

// 单局临时数据（击杀数/道具/时间/得分）
USTRUCT(BlueprintType)
struct BATTLETANK_API FGameSessionData
{
	GENERATED_BODY()
	 
	UPROPERTY(BlueprintReadWrite)
	int32 TankKillCount = 0;      // 坦克击杀数
	UPROPERTY(BlueprintReadWrite)
	int32 ItemCount = 0;      // 道具数量
	UPROPERTY(BlueprintReadWrite)
	float LevelClearTime = 0.0f;  // 本局通关时间
	UPROPERTY(BlueprintReadWrite)
	int32 Score = 0;    
	UPROPERTY(BlueprintReadWrite)
	int32 blood = 1;     //血条数
	UPROPERTY(BlueprintReadWrite)
	int32 atk = 10;  //攻击（可破坏钢墙）
	UPROPERTY(BlueprintReadWrite)
	int32 atkspeed= 1;  //攻速
	UPROPERTY(BlueprintReadWrite)
	bool canbeattack= true;  //攻速
	
	UPROPERTY(BlueprintReadWrite)
	int32 enemynum  ;  //敌人数量
};
 
 
// 永久存档数据（通关关卡/最佳时间/最佳得分）
USTRUCT(BlueprintType)
struct BATTLETANK_API FGameSaveData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 UnlockedLevel = 1;                  // 已通关最高关卡
	UPROPERTY(BlueprintReadWrite)
	TMap<int32, float> LevelBestTimes;        // 各关卡最佳通关时间（键=关卡号）
	UPROPERTY(BlueprintReadWrite)
	TMap<int32, int32> LevelBestScores;       // 各关卡最佳得分（键=关卡号）
};
UENUM(BlueprintType)
enum class ETankDirection : uint8
{
	Left,    // 左（初始朝向）
	Right,   // 右
	Up,      // 上   
	Down     // 下 
};
UCLASS()
class BATTLETANK_API APlayerTank : public APaperCharacter
{	GENERATED_BODY()
	
private:
	int32 PlayerIndex; // 玩家索引
	UPROPERTY(VisibleAnywhere,Category="TankSettings")
	float RotationSpeed; // 旋转速度
	 
	UPROPERTY(VisibleAnywhere,Category="TankSettings")
	float MoveSpeed; // 移动速度
	
	//玩家2的移动处理
	FVector CurrentVelocity; // 当前速度
	float MaxVelocity;  // 最大速度
	float Acceleration; // 加速度
	float Deceleration; // 减速度
public:
	// Sets default values for this pawn's properties
	APlayerTank();
	// 设置玩家索引
	void SetPlayerIndex(int32 Index) {PlayerIndex = Index;}; 
	// 获取玩家索引
	int32 GetPlayerIndex() const { return PlayerIndex; }
	
	void InitializeTankController(ATankController* TankController);
	UFUNCTION()
	
	FGameSessionData GetTankSessionDataByID( );
	 
	
protected:
	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* TankMovementComponent;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
    //处理移动输入
	UFUNCTION()
	void MoveInputHandler(const int32 InPlayerIndex,const FInputActionValue& Value);
	UFUNCTION()
	void FireInputHandler(const int32 InPlayerIndex,const FInputActionValue& Value);
	//上下左右移动函数
	void OnMoveRightPressed();
	void OnMoveLeftPressed();
	void OnMoveUpPressed();
	void OnMoveDownPressed();
	
	void Onshoot();
	//  开火冷却时间 
	UPROPERTY(EditAnywhere, Category = "Tank|Fire")
	float FireCooldownTime = 0.6f; // 默认0.5秒冷却

	// 上次开火的时间戳（秒）
	float LastFireTime = 0.0f;

	//  是否可以开火（冷却是否结束）
	bool CanFire() const;
	
	void OnKillEnemy();
	
	
	void  PressedFunction();
	void ReleasedFunction();
	
	
	void UpdateTankGridStartLocation();//更新初始位置
	void UpdateTankRotation();
	void UpdateTankGridLocation();//更新坦克位置函数
	//渲染序列帧动画的组件
	UPROPERTY(VisibleAnywhere, Category = "Render")
	class UPaperFlipbookComponent* RenderTankComponent;
	//资产
	UPROPERTY(VisibleAnywhere, Category = "Render")
	class UPaperFlipbook* TankFlipbook;
	//碰撞箱
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Render")
	float TileSize = 1.0f;

	//子弹生成
	void SpawnBulletActor();
	USceneComponent* BulletSpawnPosition;
	
	//子弹对象池
	UPROPERTY()
	class AHomeGameModeBase* homebase;
	
	UPROPERTY(EditAnywhere, Category = "Grid Move")
	float GridStep = 32.0f; // 地图格子步长 

	UPROPERTY(EditAnywhere, Category = "Grid Move")
	FVector MapStartPos = FVector(320.0f, -790.f, 50.f); // 地图起始坐标（ABackGround生成坐标）

	int32 CurrentGridX = 0; // 左右移动索引 
	int32 CurrentGridY = 0; // 上下移动索引 
	APlayerTankStateBase *TankGameState;
	ETankDirection CurrentDirection = ETankDirection::Left;//初始左
	
	FGameSessionData TankSessionData;
	FGameSessionData GetTankSessionData() const { return TankSessionData; }
	
	
	FTimerHandle ResetTimerHandle;
	void ResetCooldownToZero();
	float BaseFireCooldownTime = 5;
	float CurrentFireCooldownTime = 0.0f;
	
	void  ApplyAddBloodEffect( );
	void  ApplyCantBeAttackedEffect( );
	void  ApplyClearAllEffect();
    void  ApplyProtectHomeEffect();
	void  ApplyAddAttackSpeedEffect( );
	void  ApplyAddAtkEffect( );
	void  ApplyTimerEffect( );
};
 
 