// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "boxbase.generated.h"
class UPaperFlipbookComponent;

UENUM(BlueprintType)
enum class ETerrainType : uint8
{
    TT_Brick UMETA(DisplayName = "砖块"),
    TT_Brick1 UMETA(DisplayName = "钢砖"),
    TT_River UMETA(DisplayName = "河流"),
    TT_Road  UMETA(DisplayName = "道路"),
    TT_Empty UMETA(DisplayName = "空地"),
    TT_Grass UMETA(DisplayName = "草地"), 
};

UCLASS()
class BATTLETANK_API Aboxbase : public AActor
{
	GENERATED_BODY()

 
 
    
public:
    // 构造函数
    Aboxbase();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // ========== 核心组件 ==========
    // 碰撞体 
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Terrain")
    UBoxComponent* CollisionBox;

    // 像素渲染组件
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Terrain")
    UPaperSpriteComponent* SpriteComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Terrain")
    UPaperSprite * Sprite ;
    
    // 地形类型
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain")
    ETerrainType TerrainType;

    // 格子尺寸 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain")
    float TileSize = 1.0f;

    // 是否可破坏（仅砖块有效）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain")
    bool bIsDestructible = false;

   
    // 格子被摧毁（比如砖块被坦克炮打坏）
    UFUNCTION(BlueprintCallable, Category = "Terrain")
    virtual void DestroyTile();

    // 获取格子通行规则 
    UFUNCTION(BlueprintPure, Category = "Terrain")
    bool IsPassable();
};
 
