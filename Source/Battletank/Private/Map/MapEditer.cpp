// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/MapEditer.h"

#include "EnhancedInputComponent.h"
#include "InputAction.h"
 
#include "Actors/scenebox/GridActor.h"
 
#include "Kismet/GameplayStatics.h"
#include "Pawn/enemypawn.h"


// Sets default values
AMapEditer::AMapEditer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}
	
	//创建地图容器
	MapContainer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MapContainer"));
	MapContainer -> SetupAttachment(RootComponent);
	UStaticMesh* MapContainerMesh = LoadObject<UStaticMesh>(this, TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	MapContainer -> SetStaticMesh(MapContainerMesh);
	MapContainer->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

// Called when the game starts or when spawned
void AMapEditer::BeginPlay()
{
	Super::BeginPlay();
	 SpawnEnemiesRandomly();
	DrawMapContainer();	
	 
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		 
		UInputAction*RightMousePress= LoadObject<UInputAction>(
			this,
			TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Inputs/Actions/IA_Press.IA_Press'")
		);
		UInputAction*MiddleMousePress= LoadObject<UInputAction>(
				this,
				TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Inputs/Actions/IA_Hold.IA_Hold'")
			);
		if (RightMousePress)
		{
			if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PC->InputComponent))
			{
				// 绑定按住
				EnhancedInput->BindAction(
					RightMousePress,
					ETriggerEvent::Started,  // 对应 IE_Pressed
					this,
					&AMapEditer::OnMousePressed
				);

				// 绑定松开
				EnhancedInput->BindAction(
					RightMousePress,
					ETriggerEvent::Completed, // 对应 IE_Released
					this,
					&AMapEditer::OnMouseReleased
				);
			}
		}
		if (MiddleMousePress)
		{
			if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PC->InputComponent))
			{
				// 绑定按住
				EnhancedInput->BindAction(
					MiddleMousePress,
					ETriggerEvent::Started,  // 对应 IE_Pressed
					this,
					&AMapEditer::OnMiddleMouseHold
				);

				// 绑定松开
				EnhancedInput->BindAction(
					MiddleMousePress,
					ETriggerEvent::Completed, // 对应 IE_Released
					this,
					&AMapEditer::OnMiddleMouseReleased
				);
			}
		}
	}
	 

}
void AMapEditer::OnMousePressed()
{
	bIsMousePressed = true;
	FIntPoint TilePos = GetTileFromMousePosition();
	BoxSelectStart = GetTileFromMousePosition();
	if (TilePos.X >= 0 && TilePos.Y >= 0)
	{  
		DrawTile(TilePos.X, TilePos.Y, SelectedTileType);
		LastDrawnTile = TilePos;
	} 
	
}

void AMapEditer::OnMouseReleased()
{
	bIsMousePressed = false;
	LastDrawnTile = FIntPoint(-1, -1);
}

void AMapEditer::OnMiddleMouseHold()
{bIsBoxSelecting=true;
	FIntPoint TilePos = GetTileFromMousePosition();
	if (TilePos.X >= 0 && TilePos.Y >= 0)
	{
		DrawBoxSelectHint();
	}
}
 
void AMapEditer::OnMiddleMouseReleased( )
{bIsBoxSelecting=false;
	 
	FillBoxSelectArea( SelectedTileType);
	 
}

// Called every frame
void AMapEditer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//鼠标按下绘制
	if (bIsMousePressed)
	{ 
	 
		FIntPoint TilePos = GetTileFromMousePosition();
		 if (TilePos.X >= 0 && TilePos.Y >= 0 && TilePos != LastDrawnTile)
		{
			DrawTile(TilePos.X, TilePos.Y, SelectedTileType);
			LastDrawnTile = TilePos;
		}
	}
 	if (bIsBoxSelecting)
	{FIntPoint TilePos = GetTileFromMousePosition();
		//if (TilePos.X >= 0 && TilePos.Y >= 0)
		{
			 DrawBoxSelectHint();
		}
	}
}

 
 

void AMapEditer::DrawMapContainer()
{
	//设置地图容器的大小并绘制地图网格
	MapContainer -> SetWorldScale3D(FVector(MapSize.X / 10 , MapSize.Y / 10 , 1.0f));
	MapContainer -> SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	UMaterialInstanceDynamic* MapContainerMaterial = UMaterialInstanceDynamic::Create(LoadObject<UMaterialInstance>(nullptr,TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/Mat_MapGrid_Inst.Mat_MapGrid_Inst'")), this);
	MapContainerMaterial -> SetVectorParameterValue(TEXT("LineColor"), LineColor);
	MapContainerMaterial -> SetScalarParameterValue(TEXT("GridSize"), GridSize);
	MapContainerMaterial -> SetScalarParameterValue(TEXT("LineWidth"), LineWidth);
	MapContainer -> SetMaterial(0, MapContainerMaterial);
}

// 获取鼠标点击的格子坐标
FIntPoint AMapEditer::GetTileFromMousePosition()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC || !MapContainer) return FIntPoint(-1, -1);

	// 屏幕坐标转世界射线
	 
	FVector2D ScreenPos;
	PC->GetMousePosition(ScreenPos.X, ScreenPos.Y);
	//UE_LOG(LogTemp, Log, TEXT("GetTileFromMousePosition: 鼠标屏幕坐标 X=%.2f, Y=%.2f"), ScreenPos.X, ScreenPos.Y);

	FVector WorldLoc, WorldDir;
	if (!PC->DeprojectScreenPositionToWorld(ScreenPos.X, ScreenPos.Y, WorldLoc, WorldDir))
	{
		return FIntPoint( WorldLoc.X, WorldLoc.Y);
	}
	 UE_LOG(LogTemp, Log, TEXT("GetTileFromMousePosition: 世界射线起点 X=%.2f, Y=%.2f, Z=%.2f | 方向 X=%.2f, Y=%.2f, Z=%.2f"),
	 WorldLoc.X, WorldLoc.Y, WorldLoc.Z, WorldDir.X, WorldDir.Y, WorldDir.Z);
	// 射线检测地图容器
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, WorldLoc, WorldLoc + WorldDir * 1000.f, ECC_Visibility, Params))
	{
		if (HitResult.GetComponent() == MapContainer)
		{ 
			// 将世界坐标转为格子坐标
			FVector LocalPos = MapContainer->GetComponentTransform().InverseTransformPosition(HitResult.ImpactPoint);
			int32 TileX = FMath::FloorToInt((LocalPos.X / (GridSize / 100.f)) + MapSize.X / 2);
			int32 TileY = FMath::FloorToInt((LocalPos.Y / (GridSize / 100.f)) + MapSize.Y / 2);
			
			// 边界检测
			//if (TileX >= 0 && TileX < MapSize.X && TileY >= 0 && TileY < MapSize.Y)
			{
				//return FIntPoint(TileX, TileY);
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("  射线未命中MapContainer！ "));
		}
	}

	return FIntPoint( WorldLoc.X, WorldLoc.Y);
}

// 绘制单个格子
void AMapEditer::DrawTile(int32 X, int32 Y, EGridType TileType)
{
	 FIntPoint TilePos(X, Y);
    
    // 1. 更新地图数据 
    if (TileType == EGridType::Empty)
    {
        // 空格子：删除数据 + 删除对应的Actor
       // CurrentMapData.Tiles.RemoveAll([X, Y](const FMapTile& Tile) { return Tile.X == X && Tile.Y == Y; });
        //DestroySingleTile(X, Y);
    }
    else
    {
        // 非空格子：先删除旧数据/Actor，再添加新数据/生成新Actor
        //CurrentMapData.Tiles.RemoveAll([X, Y](const FMapTile& Tile) { return Tile.X == X && Tile.Y == Y; });
        CurrentMapData.Tiles.Add(FMapTile(X, Y, TileType));
        SpawnSingleTile(X, Y, TileType);
    }
}

// 生成单个格子Actor 
AGridActor* AMapEditer::SpawnSingleTile(int32 X, int32 Y, EGridType TileType)
{
	if (!GridActorClass)
	{
		GridActorClass = AGridActor::StaticClass();
	}
	 
	// 先删除当前位置已有的Actor 
	// DestroySingleTile(X, Y);

	// 计算格子世界坐标（ 
	//  FVector TileLoc = FVector(
	//     (X - MapSize.X / 2) * (GridSize / 100.f),
	//     (Y - MapSize.Y / 2) * (GridSize / 100.f),
	//     20.0f
	// );
	 

	// 1. 计算地图中心的世界坐标 
	FVector MapCenter = FVector(
		-(MapSize.X / 2)  ,
		-(MapSize.Y  / 2)  ,
		25.0f
	);

	 
	FVector OffsetFromCenter = FVector(X,Y,0.1) - MapCenter;
	float GridX_Float = OffsetFromCenter.X / 32.0f; // 先转成“4为单位”的浮点值
	float GridY_Float = OffsetFromCenter.Y / 32.0f;

	int32 GridX = FMath::RoundToInt(GridX_Float) *32; // 四舍五入后×4，得到4的倍数
	int32 GridY = FMath::RoundToInt(GridY_Float) *32;
	 

	// 4. 边界限制（防止生成到地图外）
	GridX = FMath::Clamp(GridX, 0, MapSize.X  - 1);
	GridY = FMath::Clamp(GridY, 0, MapSize.Y  - 1);
	FVector TileLoc = FVector(
		GridX+ MapCenter.X  ,GridY+ MapCenter.Y ,
		    25);
	 
// 	FVector TileLoc = FVector(
// 			X ,
// 			Y  ,
// 		   20.0f
// );
	 
    //生成单个Actor
     // AGridActor* TileActor = GetWorld()->SpawnActor<AGridActor>(
     //     GridActorClass,
     //     TileLoc,
     //     FRotator  (90,0,0)
     // );
	UClass* TileClass = LoadClass<AGridActor>(nullptr, TEXT("/Game/Blueprints/MyGridActor.MyGridActor_C"));

	if (!TileClass) return nullptr;
	AGridActor* TileActor = GetWorld()->SpawnActor<AGridActor>(
	TileClass,
	TileLoc,
	FRotator(90,0,0)
 
);
    if (TileActor)
    { 
        TileActor->SetActorScale3D(FVector3d(1.0f,0.4f,1.0f));
        TileActor->CurrentGridType = TileType;
    	TileActor->GridInit(TileType);
        TileActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
         TileActor->SetActorLabel(FString::Printf(TEXT("Tile_%d_%d"), X, Y));
       TileActorMap.Add(FIntPoint(X, Y), TileActor); //记录映射关系
     
    	 
     
        UE_LOG(LogTemp, Log, TEXT("  生成单个格子：X=%d, Y=%d"), GridX, GridY);
    }
    

    return TileActor;
}
 

// 删除单个格子Actor（从场景+映射表中移除）
void AMapEditer::DestroySingleTile(int32 X, int32 Y)
{
	FIntPoint TilePos(X, Y);
	if (TileActorMap.Contains(TilePos))
	{
		AGridActor* OldTile = TileActorMap[TilePos];
		if (OldTile)
		{
			OldTile->Destroy(); // 销毁Actor
			UE_LOG(LogTemp, Log, TEXT("  删除单个格子：X=%d, Y=%d"), X, Y);
		}
		TileActorMap.Remove(TilePos); // 从映射表移除
	}
}
// 清空已生成的地形Actor
void AMapEditer::ClearTileActors()
{
    
  
}// 绘制框选网格提示（在Tick中调用）
void AMapEditer::DrawBoxSelectHint()
{
   // if (!bIsBoxSelecting) return;

    // 更新当前鼠标的终点坐标
    BoxSelectEnd = GetTileFromMousePosition();
	UE_LOG(LogTemp, Log, TEXT("框选中") );
    
	FVector MapCenter = FVector(
		-(MapSize.X / 2)  ,
		-(MapSize.Y  / 2)  ,
		0.1f
	);

    // 计算选框的最小/最大网格坐标（处理反向框选）
    int32 MinGridX = FMath::Min(BoxSelectStart.X, BoxSelectEnd.X);
    int32 MaxGridX = FMath::Max(BoxSelectStart.X, BoxSelectEnd.X);
    int32 MinGridY = FMath::Min(BoxSelectStart.Y, BoxSelectEnd.Y);
    int32 MaxGridY = FMath::Max(BoxSelectStart.Y, BoxSelectEnd.Y);

    // 遍历选框内所有网格，绘制提示
    for (int32 GridX = MinGridX; GridX <= MaxGridX; GridX += 32)
    {
        for (int32 GridY = MinGridY; GridY <= MaxGridY; GridY += 32)
        {
            // 网格坐标转世界坐标（中心位置）
            FVector GridWorldPos = FVector(
                MapCenter.X + GridX * GridSize  + GridSize /2,
                MapCenter.Y + GridY * GridSize  + GridSize /2,
                30.1f // 略高于格子，避免遮挡
            );

            // 绘制网格提示框（半透明绿）
            FVector BoxExtent(GridSize /2, GridSize /2, 10.f);
        	DrawDebugBox(
	 GetWorld(),
	 GridWorldPos,
	 BoxExtent,
	 BoxSelectColor,
	 false,
	 0.f,
	 0,
	 2.f
 );

            // 绘制网格线（白色）
            FVector LineStart = FVector(
                MapCenter.X + GridX * GridSize ,
                MapCenter.Y + GridY * GridSize ,
                30.2f
            );
            FVector LineEndX = LineStart + FVector(GridSize , 0, 0);
            FVector LineEndY = LineStart + FVector(0, GridSize , 0);
            DrawDebugLine(GetWorld(), LineStart, LineEndX, FColor::White, false, 0.f);
            DrawDebugLine(GetWorld(), LineStart, LineEndY, FColor::White, false, 0.f);
        }
    }

    // 绘制选框外框（实线绿）
    FVector BoxStartWorld = FVector(
        MapCenter.X + MinGridX * GridSize ,
        MapCenter.Y + MinGridY * GridSize ,
        30.3f
    );
    FVector BoxEndWorld = FVector(
        MapCenter.X + (MaxGridX + 32) * GridSize ,
        MapCenter.Y + (MaxGridY +32) * GridSize ,
        30.3f
    );
	DrawDebugBox(
	GetWorld(),
	(BoxStartWorld + BoxEndWorld) / 2,  // Center
	(BoxEndWorld - BoxStartWorld) / 2,  // Extent
	FQuat(FRotator::ZeroRotator),       // Rotation 
	FColor::Green,
	false,
	0.f,
	0,
	3.f
);
}
// ===================== 批量填充逻辑 =====================
void AMapEditer::FillBoxSelectArea(EGridType GridType )
{
    // 校验选框有效
    if (BoxSelectStart.X == -1 || BoxSelectEnd.X == -1) return;

    float GridSizeMeter = GridSize ;
    FVector MapCenter = FVector(-(MapSize.X/2)*GridSizeMeter, -(MapSize.Y/2)*GridSizeMeter, 0);

    // 选框范围（处理反向框选）
    int32 MinGridX = FMath::Min(BoxSelectStart.X, BoxSelectEnd.X);
    int32 MaxGridX = FMath::Max(BoxSelectStart.X, BoxSelectEnd.X);
    int32 MinGridY = FMath::Min(BoxSelectStart.Y, BoxSelectEnd.Y);
    int32 MaxGridY = FMath::Max(BoxSelectStart.Y, BoxSelectEnd.Y);

    int32 GeneratedCount = 0; // 统计生成数量
    TArray<FIntPoint> NeighborOffsets = {FIntPoint(0,32), FIntPoint(0,-32), FIntPoint(32,0), FIntPoint(-32,0)}; // 32邻格

    // 遍历选框内所有32倍网格
    for (int32 GridX = MinGridX; GridX <= MaxGridX; GridX += 28)
    {
        for (int32 GridY = MinGridY; GridY <= MaxGridY; GridY += 28)
        {
            FIntPoint TargetGrid(GridX, GridY);
            bool bCanSpawn = true;

             
              if (TileActorMap.Contains(TargetGrid))
             {
                AGridActor* ExistingTile = TileActorMap[TargetGrid];
                 if (IsValid(ExistingTile) )
             {
                      bCanSpawn = false;
                }
             }

            //  附近格子有砖块 
            if (bCanSpawn)
            {
                for (const FIntPoint& Offset : NeighborOffsets)
                {
                    FIntPoint NeighborGrid(GridX + Offset.X, GridY + Offset.Y);
                    if (NeighborGrid.X < 0 || NeighborGrid.X >= MapSize.X ||
                        NeighborGrid.Y < 0 || NeighborGrid.Y >= MapSize.Y)
                        continue;

                    if (TileActorMap.Contains(NeighborGrid))
                    {
                        AGridActor* NeighborTile = TileActorMap[NeighborGrid];
                        if (IsValid(NeighborTile) && NeighborTile->CurrentGridType == GridType)
                        {
                            bCanSpawn = false;
                            break;
                        }
                    }
                }
            }

            // 校验通过，生成格子
            if (bCanSpawn)
            {
	            FVector TileLoc = FVector(
					(GridX - MapSize.X/2) * GridSizeMeter,
					(GridY - MapSize.Y/2) * GridSizeMeter,
					25.0f
				);

               
            	UClass* TileClass = LoadClass<AGridActor>(nullptr, TEXT("/Game/Blueprints/MyGridActor.MyGridActor_C"));

            	 
            	AGridActor* TileActor = GetWorld()->SpawnActor<AGridActor>(
				TileClass,
				TileLoc,
				FRotator(90,0,0)
 
			);

                if (TileActor)
                {   TileActor->SetActorScale3D(FVector3d(1.0f,0.4f,1.0f));
                    TileActor->CurrentGridType = GridType;
                    TileActor->GridInit(GridType);
                    TileActor->SetActorLabel(FString::Printf(TEXT("GridTile_%d_%d"), GridX, GridY));
                    TileActorMap.Add(TargetGrid, TileActor);
                	CurrentMapData.Tiles.Add(FMapTile((GridX - MapSize.X/2) * GridSizeMeter, (GridY - MapSize.Y/2) * GridSizeMeter,GridType));
                    GeneratedCount++;
                }
            }
        }
    }

    UE_LOG(LogTemp, Log, TEXT("框选填充完成：共生成%d个砖块（跳过已有/附近有砖块的格子）"), GeneratedCount);
}

FString AMapEditer::GetSaveFilePath(const FString& LevelName)
{
	// 拼接路径：项目Saved目录 + MapData文件夹 + 关卡名.json
	FString SaveDir = FPaths::ProjectSavedDir() + TEXT("MapData/");
	// 创建文件夹（不存在则创建）
	IFileManager::Get().MakeDirectory(*SaveDir, true);
	// 返回完整路径
	return SaveDir + LevelName + TEXT(".json");
}
 
// 接口实现：保存地图数据到JSON对象
void AMapEditer::OnSave (FJsonObject& OutJson)
{
	// 1. 保存基础信息
	OutJson.SetStringField("LevelName", CurrentLevelName);
	OutJson.SetNumberField("MapSizeX", MapSize.X);
	OutJson.SetNumberField("MapSizeY", MapSize.Y);
	OutJson.SetNumberField("GridSize", GridSize);

	// 2. 保存格子数据（数组）
	TArray<TSharedPtr<FJsonValue>> TilesJsonArray;
	for (const FMapTile& Tile : CurrentMapData.Tiles)
	{
		TSharedPtr<FJsonObject> TileJson = MakeShareable(new FJsonObject());
		// 保存格子坐标和类型
		TileJson->SetNumberField("X", Tile.X);
		TileJson->SetNumberField("Y", Tile.Y);
		TileJson->SetNumberField("TileType", (int32)Tile.TileType); // 枚举转int
		// 添加到数组
		TilesJsonArray.Add(MakeShareable(new FJsonValueObject(TileJson)));
	}
	OutJson.SetArrayField("Tiles", TilesJsonArray);

	UE_LOG(LogTemp, Log, TEXT("地图数据序列化完成：共%d个格子"), CurrentMapData.Tiles.Num());
}
void AMapEditer::OnLoad (const FJsonObject& InJson)
{//if (!LoadMapFromFile( CurrentLevelName ))return;
	// 1. 加载基础信息
	CurrentLevelName = InJson.GetStringField("LevelName");
	MapSize.X = InJson.GetIntegerField("MapSizeX");
	MapSize.Y = InJson.GetIntegerField("MapSizeY");
	GridSize = InJson.GetNumberField("GridSize");

	// 2. 清空当前地图
	ClearCurrentMap();

	// 3. 加载格子数据
	TArray<TSharedPtr<FJsonValue>> TilesJsonArray = InJson.GetArrayField("Tiles");
	for (const TSharedPtr<FJsonValue>& JsonValue : TilesJsonArray)
	{
	 
		TSharedPtr<FJsonObject> TileJson = JsonValue->AsObject();
		int32 X = TileJson->GetIntegerField("X");
		int32 Y = TileJson->GetIntegerField("Y");
		EGridType TileType = (EGridType)TileJson->GetIntegerField("TileType"); // int转枚举

		// 添加到地图数据
		CurrentMapData.Tiles.Add(FMapTile(X, Y, TileType));
		// 生成格子Actor（复用你之前的SpawnSingleTile）
		SpawnSingleTile(X, Y, TileType);
		UE_LOG(LogTemp, Log, TEXT(" 格子类型  (枚举值：%d)"), static_cast<int32>(TileType));
	}

	UE_LOG(LogTemp, Log, TEXT("地图数据反序列化完成：加载%d个格子 "), TilesJsonArray.Num());
	 
}
bool AMapEditer::SaveMapToFile()
{
	// 1. 创建JSON对象
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	// 2. 调用接口保存数据
	OnSave(*JsonObject);
	// 3. 序列化JSON到字符串
	FString JsonStr;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonStr);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	// 4. 写入文件
	FString SavePath = GetSaveFilePath(CurrentLevelName);
	bool bSaved = FFileHelper::SaveStringToFile(JsonStr, *SavePath);

	if (bSaved)
	{
		UE_LOG(LogTemp, Log, TEXT("地图保存成功！路径：%s"), *SavePath);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("地图保存失败！路径：%s"), *SavePath);
	}

	return bSaved;
}

// 从JSON文件加载地图（对外调用）
bool AMapEditer::LoadMapFromFile(const FString& LevelName)
{
	FString LoadPath = GetSaveFilePath(LevelName);
	UE_LOG(LogTemp, Warning, TEXT("[LoadMapFromFile] 尝试加载JSON文件：%s"), *LoadPath);

	//  检查文件是否存在  
	if (!FPaths::FileExists(LoadPath))
	{
		UE_LOG(LogTemp, Error, TEXT("[LoadMapFromFile] 加载失败：文件不存在！路径：%s"), *LoadPath);
		return false;
	}

	//  读取JSON文件内容  
	FString JsonStr;
	if (!FFileHelper::LoadFileToString(JsonStr, *LoadPath))
	{
		UE_LOG(LogTemp, Error, TEXT("[LoadMapFromFile] 加载失败：读取文件失败！路径：%s"), *LoadPath);
		return false;
	}
	UE_LOG(LogTemp, Log, TEXT("[LoadMapFromFile] 成功读取文件，内容长度：%d字符"), JsonStr.Len());

	//  反序列化JSON字符串到对象  
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonStr);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("[LoadMapFromFile] 加载失败：JSON格式错误！路径：%s"), *LoadPath);
		return false;
	}

	//  调用OnLoad解析数据 
	OnLoad(*JsonObject);

	//  
	UE_LOG(LogTemp, Log, TEXT("[LoadMapFromFile] 地图加载成功！关卡名：%s，JSON路径：%s"), *LevelName, *LoadPath);
	return true;
}

void AMapEditer::ClearCurrentMap()
{    int32 DestroyedCount = 0; 
	for (auto& Pair : TileActorMap)
	{AGridActor* TileActor = Pair.Value;
	
		if (IsValid(TileActor))
		{
			
			TileActor->Destroy();
			DestroyedCount++;
		}
	}

	
	//TileActorMap.Empty();


	int32 ClearedTileCount = CurrentMapData.Tiles.Num();
	CurrentMapData.Tiles.Empty();
	UE_LOG(LogTemp, Log, TEXT("[ClearCurrentMap] 地图清空完成：销毁%d个格子Actor，清空%d个格子数据"),
	  DestroyedCount, ClearedTileCount);
}
void AMapEditer::SpawnEnemiesRandomly()
{
	// 获取所有空白格子
	TArray<FVector> EmptyGrids = GetAllEmptyGridPositions();
	if (EmptyGrids.Num() == 0) 
	{
		UE_LOG(LogTemp, Log, TEXT(" 没有空格子"));
		return;
	}

	// 限制生成数量不超过空白格子数
	int32 ActualSpawnCount = FMath::Min(SpawnCount, 5);

	// 随机生成敌人
	for (int32 i = 0; i < ActualSpawnCount; i++)
	{
		// 随机选一个空白格子
		int32 RandomIndex = FMath::RandRange(0, EmptyGrids.Num() - 1);
		FVector SpawnLocation = EmptyGrids[RandomIndex];
		TSubclassOf<Aenemypawn> EnemyPawnClass;
		// 生成敌人
		GetWorld()->SpawnActor<Aenemypawn>(EnemyPawnClass, SpawnLocation, FRotator::ZeroRotator);
		// 从数组移除该格子（避免重复生成）
		EmptyGrids.RemoveAt(RandomIndex);
	}
}
bool AMapEditer::IsGridEmpty(const FVector& GridLocation)
{
	 
	FVector BoxExtent = FVector(32, 32, 20); 
	 
	FRotator BoxRotation = FRotator::ZeroRotator;

   
	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::BoxTraceMulti(
  GetWorld(),                  // 必须的游戏世界
  GridLocation,                // 检测中心位置
  GridLocation,                // 结束位置（和起始一致，静态检测）
  BoxExtent,                   // 你要保留的核心：网格尺寸
  FRotator::ZeroRotator,       // 固定无旋转
  ETraceTypeQuery::TraceTypeQuery1,
  false,                     
  TArray<AActor*>(),           
  EDrawDebugTrace::None,
  HitResults,
  true
);   
	UE_LOG(LogTemp, Log, TEXT(" 是否为空格子%d"),HitResults.Num() );
	return HitResults.Num() == 0;
	
}
TArray<FVector> AMapEditer::GetAllEmptyGridPositions()
{
	TArray<FVector> EmptyGrids;
	// 遍历所有格子
	for (int32 X = 0; X < MapSize.X; X+=32)
	{
		for (int32 Y = 0; Y< MapSize.Y; Y+=32)
		{
			// 计算格子中心坐标
			FVector GridLocation = FVector(X * GridSize + GridSize/2, Y * GridSize + GridSize/2,0.2F);
			// 如果空白则加入数组
			if (IsGridEmpty(GridLocation))
			{
				EmptyGrids.Add(GridLocation);
			}
		}
	}
	return EmptyGrids;
}