// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerTank.generated.h"


class UFloatingPawnMovement;
class ATankController;
struct FInputActionValue;

UENUM(BlueprintType)
enum class ETankDirection : uint8
{
	Left,    // 左（初始朝向）
	Right,   // 右
	Up,      // 上   
	Down     // 下 
};
UCLASS()
class BATTLETANK_API APlayerTank : public APawn
{
	GENERATED_BODY()
	
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
	//上下左右移动函数
	void OnMoveRightPressed();
	void OnMoveLeftPressed();
	void OnMoveUpPressed();
	void OnMoveDownPressed();
	//
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
	UPROPERTY(VisibleAnywhere, Category = "Render")
	class USphereComponent * Sphere;
	
	
	
	UPROPERTY(EditAnywhere, Category = "Grid Move")
	float GridStep = 32.0f; // 地图格子步长 

	UPROPERTY(EditAnywhere, Category = "Grid Move")
	FVector MapStartPos = FVector(320.0f, -790.f, 50.f); // 地图起始坐标（ABackGround生成坐标）

	int32 CurrentGridX = 0; // 左右移动索引 
	int32 CurrentGridY = 0; // 上下移动索引 
	 
	ETankDirection CurrentDirection = ETankDirection::Left;//初始左
};
 