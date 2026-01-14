// Fill out your copyright notice in the Description page of Project Settings.
#include "HomeGameModeBase.h"
#include "Public/Actors/BackGround.h"

#include "Pawn/PlayerTank.h"
#include "Pawn/StartPagePawn.h"
#include "Actors/Camera2DActor.h"
#include "FrameWork/TankController.h"

AHomeGameModeBase ::AHomeGameModeBase()
{
 	//DefaultPawnClass = APlayerTank::StaticClass();
 	DefaultPawnClass = AStartPagePawn::StaticClass();
 	PlayerControllerClass = ATankController::StaticClass();
}
void AHomeGameModeBase::BeginPlay()
 {
	 //加载瓦片地图（测试）  //调了一下生成的位置，对不准相机？
 	GetWorld()->SpawnActor< ABackGround >( ABackGround ::StaticClass(), FVector(320.0f,  -790.f,  50.f), FRotator (0.0f, 0.0f, -90.0f));
	
	//获取玩家控制器
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
 		Tank1 = GetWorld()->SpawnActor<APlayerTank>(
			 APlayerTank::StaticClass(),
			 FVector(0, 0, 0),
			 FRotator(0, 0, 0)
		 );
 	}
	TankController->Possess(Tank1);
	Tank1 -> SetPlayerIndex(0);
	Tank1 -> InitializeTankController(TankController);

		// 手动Spawn坦克2
    	APlayerTank*	Tank2 = GetWorld()->SpawnActor<APlayerTank>(
    				APlayerTank::StaticClass(),
    				FVector(100, 100, 0),
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


  