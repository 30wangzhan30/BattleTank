// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Actors/BackGround.h"
#include "HomeGameModeBase.h"
 AHomeGameModeBase ::AHomeGameModeBase()
{
 	 
}
void AHomeGameModeBase::BeginPlay()
{//加载瓦片地图（测试）
 	GetWorld()->SpawnActor< ABackGround >( ABackGround ::StaticClass(), FVector(0.0f,  0.f,  50.f), FRotator (-0.0f, 0.0f, -90.0f));}