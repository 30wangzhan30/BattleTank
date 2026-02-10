// Fill out your copyright notice in the Description page of Project Settings.

#include "HomeGameModeBase.h"
#include "Public/Actors/BackGround.h"
#include "Pawn/PlayerTank.h"
//#include "Pawn/StartPagePawn.h"
#include "Actors/Camera2DActor.h"
#include "Actors/TankBullet.h"
#include "GameStateBase/PlayerTankStateBase.h"
#include "Pawn/PlayerHud.h"
#include "UI/Startpagecontrol.h"
#include "FrameWork/TankController.h"
#include "Kismet/GameplayStatics.h"

AHomeGameModeBase ::AHomeGameModeBase()
{
	//DefaultPawnClass = APlayerTank::StaticClass();
	//DefaultPawnClass = UStartpagecontrol::StaticClass();
	PlayerControllerClass = ATankController::StaticClass();
	GameStateClass = APlayerTankStateBase::StaticClass();
	static ConstructorHelpers::FClassFinder<APlayerHud> HUD_BP(TEXT("/Script/Engine.Blueprint'/Game/StartPawn/playerhud/MyPlayerHud.MyPlayerHud_C'"));

	HUDClass= HUD_BP.Class;
 	// HUDClass = APlayerHud::StaticClass();
}
void AHomeGameModeBase::BeginPlay()
 {
	 //加载瓦片地图（测试）  //调了一下生成的位置，对不准相机？
 	GetWorld()->SpawnActor< ABackGround >( ABackGround ::StaticClass(), FVector(320.0f,  -790.f,  50.f), FRotator (0.0f, 90.0f, -90.0f));
 
 	//实例化填装对象池
 	//Addinitilize();
 	
 	APlayerController* PC = GetWorld()->GetFirstPlayerController();
 	if (!PC)
 	{
 		UE_LOG(LogTemp,Error,TEXT("PlayerController is nullptr"));
 		return;
 	}
	 

	//获取玩家TankController
	ATankController* TankController = Cast<ATankController>(PC);
 	if (!TankController)
 	{
 		UE_LOG(LogTemp,Error,TEXT("TankController is nullptr"));
 		return;
 	}
 	// 优先获取UE自动生成的坦克
 	 APlayerTank* Tank1 = Cast<APlayerTank>(PC->GetPawn());
 	if (!Tank1)
 	{
 		// 手动Spawn坦克
 		FActorSpawnParameters SpawnInfo;
 		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
 		 Tank1 = GetWorld()->SpawnActor<APlayerTank>(
			 APlayerTank::StaticClass(),
			 FVector(100, 200, 300 ),
			 FRotator(0, 0, 0),
			 SpawnInfo
		 );
 	
	 TankController->Possess(Tank1);
	Tank1 -> SetPlayerIndex(0);
	Tank1 -> InitializeTankController(TankController);
}
		// 手动Spawn坦克2
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    	APlayerTank*	Tank2 = GetWorld()->SpawnActor<APlayerTank>(
    				APlayerTank::StaticClass(),
    				FVector(100, 200, 20 ),
    				FRotator(0, 0, 0)
    				
    			);

    	Tank2 -> SetPlayerIndex(1);
 
    	Tank2 -> InitializeTankController(TankController);
    	
    	if (!Tank2)
    	{
    		UE_LOG(LogTemp,Error,TEXT("Tank2 is nullptr"));
    	}
	
 
	// Spawn独立摄像机
	ACamera2DActor* CameraActor = GetWorld()->SpawnActor<ACamera2DActor>(
		ACamera2DActor::StaticClass(),
		Tank1->GetActorLocation() + FVector(0, 0, 200.0f),
		FRotator(0, 0, 0)
	);
	
	TankController->SetViewTargetWithBlend(CameraActor, 0.0f);
    	
	
 }

// 初始化5个子弹，放进池子里
void AHomeGameModeBase::Addinitilize()
{
	for (int i=0;i<0;i++)
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


  