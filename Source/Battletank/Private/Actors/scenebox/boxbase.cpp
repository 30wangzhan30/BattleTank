// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/scenebox/boxbase.h"
#include "PaperSpriteComponent.h"
 

// Sets default values
Aboxbase::Aboxbase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	 
	PrimaryActorTick.bCanEverTick = false; //  不需要Tick， 

	// 1. 创建碰撞体
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox; // 设置为根组件
	CollisionBox->SetBoxExtent(FVector(TileSize*15, TileSize*15, TileSize*15)); // 碰撞体尺寸匹配格子
	CollisionBox->SetSimulatePhysics(true); // 开启物理模拟 
	// 2. 创建渲染组件
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	 SpriteComponent->SetSprite(Sprite);
	 
	SpriteComponent->SetRelativeRotation(FRotator(0.0f, 0.f, 90.0f));
	SpriteComponent->SetupAttachment(RootComponent);
	SpriteComponent->SetRelativeScale3D(FVector(TileSize , TileSize, TileSize)); // 适配格子尺寸
}

// Called when the game starts or when spawned
void Aboxbase::BeginPlay()
{
	Super::BeginPlay();
	 
	// 根据地形类型设置碰撞规则
	switch (TerrainType)
	{
	case ETerrainType::TT_Brick:
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		CollisionBox->SetCollisionResponseToAllChannels(ECR_Block);
		bIsDestructible = true;
		break;
	case ETerrainType::TT_Brick1:
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		CollisionBox->SetCollisionResponseToAllChannels(ECR_Block);
	case ETerrainType::TT_River:
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		CollisionBox->SetCollisionResponseToAllChannels(ECR_Block);
	 
		break;
	case ETerrainType::TT_Road:
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
		break;
	case ETerrainType::TT_Grass:
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	
	default:
		break;
	}
}

// 摧毁格子 
void Aboxbase::DestroyTile()
{
	if (bIsDestructible && TerrainType == ETerrainType::TT_Brick)
	{
		SpriteComponent->SetVisibility(false); // 隐藏贴图
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 关闭碰撞
		bIsDestructible = false;
	}
}

// 判断是否可通行
bool Aboxbase::IsPassable()
{
	switch (TerrainType)
	{
	case ETerrainType::TT_Brick: return false; // 砖块不可通行
	case ETerrainType::TT_Brick1: return false;// 钢砖不可通行
	case ETerrainType::TT_River: return false; // 河流不可通行
	case ETerrainType::TT_Road:  return true;  // 道路可通行
	case ETerrainType::TT_Empty: return true;  // 空地可通行
	case ETerrainType::TT_Grass: return true;  // 草地可通行
	default: return true;
	}

}

// Called every frame
void Aboxbase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

 
