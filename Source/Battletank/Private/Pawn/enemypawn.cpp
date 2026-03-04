// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/enemypawn.h"
 
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Map/MapEditer.h"


// Sets default values
Aenemypawn::Aenemypawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	 
	 RootCapsule  = Cast<UCapsuleComponent>(GetRootComponent());
	if (IsValid(RootComponent))
	{
		RootCapsule ->SetCapsuleRadius (15.0f);
		RootCapsule->SetCapsuleHalfHeight (15.0f);
	  box =CreateDefaultSubobject<UBoxComponent>("enemy");
	 	 
		RootCapsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//	RootCapsule->SetSimulatePhysics(true);
	}
	Tags.Add(TEXT("Enemy"));
}

// Called when the game starts or when spawned
void Aenemypawn::BeginPlay()
{
	Super::BeginPlay();
	//Sprites = LoadObject<UPaperFlipbook>(this, TEXT("/Script/Paper2D.PaperFlipbook'/Game/PlayerControler/TankSprite/FlipBook.FlipBook'"));
	 
	TArray<AActor*> PlayerTankActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerTank::StaticClass(), PlayerTankActors);
	PlayerTank = Cast<APlayerTank>(PlayerTankActors[0]);
	box->OnComponentBeginOverlap.AddDynamic(this, &Aenemypawn::OnEnemyOverlap);
}

// Called every frame
void Aenemypawn::Tick(float DeltaTime)
{  
	Super::Tick(DeltaTime);
 
	
	
	static float PathUpdateTimer = 0.0f;
	PathUpdateTimer += DeltaTime;
	if (CurrentPath.Num() == 0 || CurrentPathIndex >= CurrentPath.Num() || PathUpdateTimer >= 1.0f)
	{
		FIntPoint StartGrid = WorldPosToGrid(GetActorLocation());
		FIntPoint TargetGrid = WorldPosToGrid(PlayerTank->GetActorLocation());
		CurrentPath = FindPathAStar(StartGrid, TargetGrid);
		CurrentPathIndex = 0;
		PathUpdateTimer = 0.0f;

		UE_LOG(LogTemp, Log, TEXT("重新规划路径：起点(%d,%d) → 终点(%d,%d)，路径长度=%d"),
			StartGrid.X, StartGrid.Y, TargetGrid.X, TargetGrid.Y, CurrentPath.Num());
	}

	// 2. 沿路径移动
	if (CurrentPath.Num() > 0 && CurrentPathIndex < CurrentPath.Num())
	{
		MoveAlongPath(DeltaTime);
	}
}

 

 
 

void Aenemypawn:: OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{ 	 	UE_LOG(LogTemp, Log, TEXT("hitttt"));
	
	OverlappedComponent->SetGenerateOverlapEvents(false);
	OverlappedComponent->DestroyComponent();
	OverlappedComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
 TArray<FIntPoint> Aenemypawn::FindPathAStar(FIntPoint StartGrid, FIntPoint TargetGrid)
{
    TArray<FIntPoint> FinalPath;

    // 边界校验：起点/终点超出地图，直接返回空路径
    if (StartGrid.X < 0 || StartGrid.X >= MapSizeX || StartGrid.Y < 0 || StartGrid.Y >= MapSizeY ||
        TargetGrid.X < 0 || TargetGrid.X >= MapSizeX || TargetGrid.Y < 0 || TargetGrid.Y >= MapSizeY)
    {
        UE_LOG(LogTemp, Warning, TEXT("A*寻路失败：起点/终点超出地图"));
        return FinalPath;
    }

    // 终点是障碍物，直接返回空路径
    if (IsGridObstacle(TargetGrid))
    {
        UE_LOG(LogTemp, Warning, TEXT("A*寻路失败：终点是障碍物"));
        return FinalPath;
    }

    // 1. 初始化节点网格
    TArray<TArray<FGridNode>> GridNodes;
    GridNodes.Init(TArray<FGridNode>(), MapSizeX);
    for (int32 X = 0; X < MapSizeX; X++)//32
    {
        GridNodes[X].Init(FGridNode(), MapSizeY);
        for (int32 Y = 0; Y < MapSizeY; Y++)
        {
            GridNodes[X][Y].Pos = FIntPoint(X, Y);
            GridNodes[X][Y].bIsObstacle = IsGridObstacle(FIntPoint(X, Y));
        }
    }

    // 2. 开放列表（待评估的节点）、关闭列表（已评估的节点）
    TArray<FGridNode*> OpenList;
    FGridNode* StartNode = &GridNodes[StartGrid.X][StartGrid.Y];
    FGridNode* TargetNode = &GridNodes[TargetGrid.X][TargetGrid.Y];
    OpenList.Add(StartNode);

    // 3. 核心寻路循环
    while (OpenList.Num() > 0)
    {
        // 找到开放列表中F值最小的节点
        FGridNode* CurrentNode = OpenList[0];
        for (FGridNode* Node : OpenList)
        {
            if (Node->F() < CurrentNode->F() || (Node->F() == CurrentNode->F() && Node->H < CurrentNode->H))
            {
                CurrentNode = Node;
            }
        }

        // 将当前节点移到关闭列表
        OpenList.Remove(CurrentNode);
        CurrentNode->bIsClosed = true;

        // 找到终点，回溯路径
        if (CurrentNode == TargetNode)
        {
            FGridNode* BackNode = TargetNode;
            while (BackNode != nullptr)
            {
                FinalPath.Insert(BackNode->Pos, 0); // 从终点回溯到起点，插入到头部
                BackNode = BackNode->Parent;
            }
            break;
        }

        // 遍历4邻格（上下左右，可扩展为8邻格）
        TArray<FIntPoint> Neighbors = {
            FIntPoint(0, 1), FIntPoint(0, -1),
            FIntPoint(1, 0), FIntPoint(-1, 0)
        };

        for (FIntPoint NeighborOffset : Neighbors)
        {
            FIntPoint NeighborPos = CurrentNode->Pos + NeighborOffset;
            // 边界校验
            if (NeighborPos.X < 0 || NeighborPos.X >= MapSizeX ||
                NeighborPos.Y < 0 || NeighborPos.Y >= MapSizeY)
            {
                continue;
            }

            FGridNode* NeighborNode = &GridNodes[NeighborPos.X][NeighborPos.Y];
            // 跳过障碍物/已关闭的节点
            if (NeighborNode->bIsObstacle || NeighborNode->bIsClosed)
            {
                continue;
            }

            // 计算G值（当前节点G+1，因为邻格代价为1）
            int32 NewG = CurrentNode->G + 1;
            // 如果新G值更小，或节点不在开放列表中，更新节点
            if (NewG < NeighborNode->G || !OpenList.Contains(NeighborNode))
            {
                NeighborNode->G = NewG;
                // H值：曼哈顿距离（|X1-X2| + |Y1-Y2|）
                NeighborNode->H = FMath::Abs(NeighborPos.X - TargetGrid.X) + FMath::Abs(NeighborPos.Y - TargetGrid.Y);
                NeighborNode->Parent = CurrentNode;

                if (!OpenList.Contains(NeighborNode))
                {
                    OpenList.Add(NeighborNode);
                }
            }
        }
    }

    return FinalPath;
}// 世界坐标转网格坐标
FIntPoint Aenemypawn::WorldPosToGrid(FVector WorldPos)
{
	// 计算地图中心（和你的地图编辑器对齐）
	FVector MapCenter = FVector(-(MapSizeX * GridSizeMeter) / 2, -(MapSizeY * GridSizeMeter) / 2, 0);
	// 相对地图中心的偏移
	FVector RelativePos = WorldPos - MapCenter;
	// 转网格索引
	int32 GridX = FMath::RoundToInt(RelativePos.X / GridSizeMeter);
	int32 GridY = FMath::RoundToInt(RelativePos.Y / GridSizeMeter);
	// 边界限制
	GridX = FMath::Clamp(GridX, 0, MapSizeX - 1);
	GridY = FMath::Clamp(GridY, 0, MapSizeY - 1);
	return FIntPoint(GridX, GridY);
}

// 网格坐标转世界坐标
FVector Aenemypawn::GridToWorldPos(FIntPoint GridPos)
{
	FVector MapCenter = FVector(-(MapSizeX * GridSizeMeter) / 2, -(MapSizeY * GridSizeMeter) / 2, 0);
	FVector WorldPos = MapCenter + FVector(
		GridPos.X * GridSizeMeter + GridSizeMeter / 2, // 格子中心
		GridPos.Y * GridSizeMeter + GridSizeMeter / 2,
		GetActorLocation().Z // 保持Z轴高度
	);
	return WorldPos;
}
// 检查格子是否是障碍物（从地图编辑器获取砖块/钢砖信息）
bool Aenemypawn ::IsGridObstacle(FIntPoint GridPos)
{
	// 找到地图编辑器Actor（需要确保场景中只有一个MapEditer）
	TArray<AActor*> MapEditerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMapEditer::StaticClass(), MapEditerActors);
	if (MapEditerActors.Num() == 0) return false;

	AMapEditer* MapEditer = Cast<AMapEditer>(MapEditerActors[0]);
	if (!MapEditer) return false;

	// 检查TileActorMap中该格子是否是砖块/钢砖
	if (MapEditer->TileActorMap.Contains(GridPos))
	{
		AGridActor* GridActor = MapEditer->TileActorMap[GridPos];
		if (IsValid(GridActor))
		{
			return (GridActor->CurrentGridType == EGridType::Brick || 
					GridActor->CurrentGridType == EGridType::Steel);
		}
	}
	return false;
}

// 沿路径移动
void Aenemypawn::MoveAlongPath(float DeltaTime)
{
	FIntPoint TargetGrid = CurrentPath[CurrentPathIndex];
	FVector TargetWorldPos = GridToWorldPos(TargetGrid);
	TargetWorldPos.Z = GetActorLocation().Z; // 保持Z轴

	// 计算方向
	FVector Direction = (TargetWorldPos - GetActorLocation()).GetSafeNormal();
	// 移动
	SetActorLocation(GetActorLocation() + Direction * MoveSpeed * DeltaTime);

	// 到达当前路径点，切换到下一个
	float DistanceToTarget = FVector::Distance(GetActorLocation(), TargetWorldPos);
	if (DistanceToTarget < GridSizeMeter / 2) // 距离小于半个格子，视为到达
	{
		CurrentPathIndex++;
		// 旋转朝向我方坦克（可选）
		FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerTank->GetActorLocation());
		LookAtRot.Pitch = 0; LookAtRot.Roll = 0; // 只旋转Yaw
		SetActorRotation(FMath::RInterpTo(GetActorRotation(), LookAtRot, DeltaTime, 5.0f));
	}
}