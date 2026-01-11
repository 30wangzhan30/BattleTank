// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Actors/BackGround.h"
#include "HomeGameModeBase.h"
#include "Pawn/PlayerTank.h"
#include "Actors/Camera2DActor.h"
 AHomeGameModeBase ::AHomeGameModeBase()
{
 	DefaultPawnClass = APlayerTank::StaticClass();
}
void AHomeGameModeBase::BeginPlay()
 {
	 //加载瓦片地图（测试）  //调了一下生成的位置，对不准相机？
 	GetWorld()->SpawnActor< ABackGround >( ABackGround ::StaticClass(), FVector(-1000.0f,  1000.f,  50.f), FRotator (-0.0f, 0.0f, -90.0f));
 	
 	  
 	
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
  