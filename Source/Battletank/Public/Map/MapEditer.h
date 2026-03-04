// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/scenebox/GridActor.h"
#include "GameFramework/Actor.h"
#include "MapEditer.generated.h"

// 地形类型枚举（ 
UENUM(BlueprintType)
enum class ETileType : uint8
{
	Empty = 0 UMETA(DisplayName = "空地"),
	Brick = 1 UMETA(DisplayName = "砖墙"),
	Steel = 2 UMETA(DisplayName = "钢墙"),
	River = 3 UMETA(DisplayName = "河流"),
	Forest = 4 UMETA(DisplayName = "森林"),
	Ice = 5 UMETA(DisplayName = "冰面"),
	Home = 6 UMETA(DisplayName = "家"),
	PlayerStart = 7 UMETA(DisplayName = "玩家起始点"),
	Boundary = 8 UMETA(DisplayName = "边界"),
};
// 单个格子数据
USTRUCT(BlueprintType)
struct FMapTile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 X = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Y = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETileType TileType = ETileType::Empty;

	FMapTile() = default;
	FMapTile(int32 InX, int32 InY, ETileType InType) : X(InX), Y(InY), TileType(InType) {}
};

// 整张地图数据
USTRUCT(BlueprintType)
struct FMapData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint MapSize; // 地图尺寸（宽/高，格子数）

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMapTile> Tiles;

	FMapData() = default;
	FMapData(FIntPoint InMapSize) : MapSize(InMapSize) {}

	// JSON序列化/反序列化
	FString ToJsonString() const;
	static FMapData FromJsonString(const FString& JsonString);
};
UCLASS()
class BATTLETANK_API AMapEditer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMapEditer();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MapEditer|MapContainer")
	FVector2D MapSize;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MapEditer|MapContainer")
	float GridSize=32;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MapEditer|MapContainer")
	float LineWidth;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MapEditer|MapContainer")
	FLinearColor LineColor;
	//创建地图容器
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="MapEditer|MapContainer")
	UStaticMeshComponent* MapContainer;
	
	// 当前编辑的地图数据
	UPROPERTY(BlueprintReadOnly, Category = "MapEditor|Data")
	FMapData CurrentMapData;
	
	// 鼠标拖拽状态
	bool bIsMousePressed = false;
	FIntPoint LastDrawnTile = FIntPoint(-1, -1);
	// 选中的地形类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapEditor|Config")
	ETileType SelectedTileType = ETileType::Brick;
	 UPROPERTY(EditAnywhere) 
	TSubclassOf<AGridActor> GridActorClass;
	
	FIntPoint  GetTileFromMousePosition();
	// 格子坐标 → 对应的Actor
	TMap<FIntPoint, AGridActor*> TileActorMap;
	// 框选相关参数
	UPROPERTY(EditAnywhere, Category = "BoxSelect")
	bool bIsBoxSelecting = false; // 是否正在框选
	FIntPoint BoxSelectStart;     // 框选起点（网格坐标）
	FIntPoint BoxSelectEnd;       // 框选终点（网格坐标）
	FColor BoxSelectColor = FColor(0, 255, 0, 100); // 框选提示颜色（半透明绿）
	// 框选函数
	 
	 void DrawBoxSelectHint();     // 绘制框选网格提示
	 void FillBoxSelectArea();     // 填充框选区域

	//  DrawTile函数
	void DrawTile(int32 X, int32 Y, ETileType TileType);
	//  单独生成/删除单个格子 
	
	AGridActor* SpawnSingleTile(int32 X, int32 Y, ETileType TileType);
	
	void DestroySingleTile(int32 X, int32 Y);
	
	void  SpawnTileActors(const FMapData& MapData);
	void  ClearTileActors();
	void  OnMousePressed();
	void  OnMouseReleased();
	void OnMiddleMouseHold();
	void  OnMiddleMouseReleased();
	void SaveMap();
	void LoadMap();
	// 地图保存路径
	FString GetMapSavePath() const { return FPaths::ProjectSavedDir() / TEXT("TankMap.json"); }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void DrawMapContainer();
};
