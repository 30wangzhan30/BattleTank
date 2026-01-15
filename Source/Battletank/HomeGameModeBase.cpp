// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "HomeGameModeBase.h"
#include "Public/Actors/BackGround.h"
#include "Pawn/PlayerTank.h"
#include "Actors/Camera2DActor.h"
#include "Actors/TankBullet.h"
#include "Pawn/PlayerHud.h"
#include "Pawn/Startpagecontrol.h"
AHomeGameModeBase ::AHomeGameModeBase()
{
 	// DefaultPawnClass = APlayerTank::StaticClass();
	DefaultPawnClass = AStartpagecontrol::StaticClass();
 	 GameStateClass = APlayerHud::StaticClass();
 	 HUDClass = APlayerHud::StaticClass();
}
void AHomeGameModeBase::BeginPlay()
 {
	 //加载瓦片地图（测试）  //调了一下生成的位置，对不准相机？
 	GetWorld()->SpawnActor< ABackGround >( ABackGround ::StaticClass(), FVector(320.0f,  -790.f,  50.f), FRotator (0.0f, 90.0f, -90.0f));
 //	GetWorld()->SpawnActor< Aenemypawn >( Aenemypawn ::StaticClass(), PlayerTank, FRotator (0.0f, 90.0f, -90.0f));
 	//实例化填装对象池
 	Addinitilize();
 	
 	APlayerController* PC = GetWorld()->GetFirstPlayerController();
 	if (!PC) return;
 	// 优先获取UE自动生成的坦克
 	APlayerTank* Tank = Cast<APlayerTank>(PC->GetPawn());
 	if (!Tank)
 	{
 		// 手动Spawn坦克
 		Tank = GetWorld()->SpawnActor<APlayerTank>(
			 APlayerTank::StaticClass(),
			 FVector(0, 0, 0),
			 FRotator(0, 0, 0)
		 );
 		PC->Possess(Tank);
 	}

 	// Spawn独立摄像机
 	ACamera2DActor* CameraActor = GetWorld()->SpawnActor<ACamera2DActor>(
		 ACamera2DActor::StaticClass(),
		 Tank->GetActorLocation() + FVector(0, 0, 200.0f),
		 FRotator(0, 0, 0)
	 );
    
 	 
 	PC->SetViewTargetWithBlend(CameraActor, 0.0f);
 	 
  

 	}
// 初始化5个子弹，放进池子里
void AHomeGameModeBase::Addinitilize()
 {
	 for (int i=0;i<MaxBulletCount;i++)
	 {
	 	UClass* BulletClass = LoadClass<ATankBullet>(this, TEXT("/Script/Engine.Blueprint'/Game/BulletClass/MyTankBullet.MyTankBullet_C'"));
	 	ATankBullet* BulletActor = GetWorld()->SpawnActor<ATankBullet>(BulletClass, FVector(0,0,0), FRotator::ZeroRotator);//要隐藏
	 	AddBulletActor( BulletActor);
	 }
	 
 	
 	
 }



	//放进池子里
void AHomeGameModeBase::AddBulletActor(ATankBullet* BulletActor)
 {  
   
 	 if (BulletObjectPool.Num() < MaxBulletCount)
 	 { BulletObjectPool.Add(BulletActor); 
	 	 
 	 	
 	 } 
     else
     {
     	BulletActor->Destroy();
     }
 	
 	
 }
//从池里拿
ATankBullet* AHomeGameModeBase::GetBulletObject()
 {
 	if (BulletObjectPool.Num() > 0 )
 	{
 		ATankBullet* GetObj = BulletObjectPool[0];
 		BulletObjectPool.RemoveAt(0); // 这个对象已经被重新利用了，不应该存在回收池中
 		return GetObj;
 	}
 	return nullptr;
 }