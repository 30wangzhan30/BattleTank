// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HomeGameModeBase.generated.h"
#include "GameFramework/Pawn.h"
#include "PlayerTank.generated.h"
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

public:
	// Sets default values for this pawn's properties
	APlayerTank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//上下左右移动函数
	void OnMoveRightPressed();
	void OnMoveLeftPressed();
	void OnMoveUpPressed();
	void OnMoveDownPressed();
	
	void Onshoot();
	//
	void  PressedFunction();
	void ReleasedFunction();
	
	
	void UpdateTankGridStartLocation();//更新初始位置
	void  UpdateTankRotation();
	void UpdateTankGridLocation();//更新坦克位置函数
	//渲染序列帧动画的组件
	class UPaperFlipbookComponent* RenderFlipbookComponent;
	//资产
	class UPaperFlipbook* TankFlipbook;
	//碰撞箱
	class USphereComponent * Sphere;
	
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
	 
	ETankDirection CurrentDirection = ETankDirection::Left;//初始左
};
 