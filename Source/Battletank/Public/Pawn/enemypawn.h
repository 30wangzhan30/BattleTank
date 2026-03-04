// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/PlayerTank.h"
#include "PaperCharacter.h"
#include "Components/BoxComponent.h"
#include "enemypawn.generated.h"
// 网格节点 
USTRUCT()
struct FGridNode
{
	GENERATED_BODY()

	// 网格坐标
	FIntPoint Pos;
	// 父节点（用于回溯路径）
	FGridNode* Parent = nullptr;
	// A*代价
	int32 G = 0; // 起点到当前的代价
	int32 H = 0; // 当前到终点的预估代价
	int32 F() const { return G + H; }

	// 是否是障碍物
	bool bIsObstacle = false;
	// 是否已被访问
	bool bIsClosed = false;

	// 重载比较（用于排序）
	bool operator<(const FGridNode& Other) const { return F() < Other.F(); }
};

 
	 
 
UCLASS()
class BATTLETANK_API Aenemypawn : public APaperCharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	Aenemypawn();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperFlipbookComponent* FlipbookComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperFlipbook * Flipbook ;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* RootCapsule;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent*box;
	int EnemyTag;
 
	UFUNCTION()
	void OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	
	// 敌方坦克移动速度
	UPROPERTY(EditAnywhere, Category = "AI")
	float MoveSpeed = 20.0f;

	// 我方坦克目标（需要在游戏中赋值）
	UPROPERTY(EditAnywhere, Category = "AI")
	APlayerTank* PlayerTank = nullptr;

	// 地图相关参数（和你的地图编辑器对齐）
	UPROPERTY(EditAnywhere, Category = "AI")
	int32 MapSizeX = 100;
	UPROPERTY(EditAnywhere, Category = "AI")
	int32 MapSizeY =100;
	UPROPERTY(EditAnywhere, Category = "AI")
	float GridSizeMeter = 0.32f; // 32cm/格

	// 寻路相关
	TArray<FIntPoint> CurrentPath; // 当前规划的路径
	int32 CurrentPathIndex = 0;    // 当前走到路径的第几个点

	 

	// A*寻路主函数
	TArray<FIntPoint> FindPathAStar(FIntPoint StartGrid, FIntPoint TargetGrid);
	// 世界坐标转网格坐标
	FIntPoint WorldPosToGrid(FVector WorldPos);
	// 网格坐标转世界坐标
	FVector GridToWorldPos(FIntPoint GridPos);
	// 检查格子是否是障碍物（砖块/钢砖）
	bool IsGridObstacle(FIntPoint GridPos);
	// 移动到路径下一个点
	void MoveAlongPath(float DeltaTime);
};
 
