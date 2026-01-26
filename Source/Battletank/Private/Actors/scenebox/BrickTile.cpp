// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/scenebox/BrickTile.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
 
 ABrickTile::ABrickTile()
{
	// 初始化父类属性
	TerrainType = ETerrainType::TT_Brick;
	bIsDestructible = true; // 普通砖块可摧毁
}

void  ABrickTile::BeginPlay()
{
	Super::BeginPlay();
 	//Sprite=LoadObject<UPaperSprite >(this, TEXT("/Script/Paper2D.PaperSprite'/Game/SceneSprite/Map_Sprite_1.Map_Sprite_1'"));
	// 普通砖块碰撞：阻挡坦克/炮弹/所有物体
 
}
 

void  ABrickTile::OnHitByBullet(int32 Damage)
{
	if (!bIsDestructible) return;

	BrickHealth -= Damage;
	if (BrickHealth <= 0)
	{
		// 调用父类摧毁逻辑
		DestroyTile();
		// 普通砖块摧毁后直接隐藏
		SpriteComponent->SetVisibility(false);
	}
}
