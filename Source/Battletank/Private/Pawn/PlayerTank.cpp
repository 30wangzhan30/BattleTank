// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PlayerTank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/SphereComponent.h"
// Sets default values
APlayerTank::APlayerTank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent= CreateDefaultSubobject<USceneComponent >(TEXT("root"));
	RenderFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("RenderFlipbookComponent"));
	RenderFlipbookComponent->SetupAttachment(RootComponent);
	RenderFlipbookComponent->SetCollisionProfileName(TEXT("BlockAll"));
	 
	
	
	
	
}

// Called when the game starts or when spawned
void APlayerTank::BeginPlay()
{ 
	Super::BeginPlay();
	UpdateTankGridLocation();
	
	TankFlipbook=LoadObject<UPaperFlipbook>(  this , TEXT("/Script/Paper2D.PaperFlipbook'/Game/PlayerControler/TankSprite/FlipBook.FlipBook'"));
 
	if (RenderFlipbookComponent && TankFlipbook)
	{
		RenderFlipbookComponent->SetFlipbook(TankFlipbook);
		RenderFlipbookComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("TANk绑定失败！"));
	}
	 
}

// Called every frame
void APlayerTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	 
	    
	 
	//轴映射回调的函数必须有一个float类型的参数, 无返回值
	PlayerInputComponent->BindAxis(TEXT("Moveupanddown"), this, &APlayerTank::MoveFunctionupdown);
	PlayerInputComponent->BindAxis(TEXT("Moveforward"), this, &APlayerTank::MoveFunctionforward);
}
//想要实现计算瓦片地图每个格子的位置然后SetRelativeLocation到将要移动到的位置
void APlayerTank::MoveFunctionupdown(float AxisValue)
{
	//if (AxisValue == 0) return;//没有按键, 不执行任何的逻辑
 
	
	//RenderFlipbookComponent->AddRelativeLocation(FVector(  0,  AxisValue, 0));
	
	// 1. 死区过滤：按键松开时重置状态（核心！）
	// const float DeadZone = 0.1f;
	// if (FMath::Abs(AxisValue) < DeadZone)
	// {
	// 	LastHorizontalDir = 0.0f; // 重置上下方向状态
	// 	return;
	// }
	  float CurrentDir = FMath::Sign(AxisValue);
	  // 仅方向变化时触发移动
	  if (CurrentDir != LastHorizontalDir)
	  {
	 	CurrentGridX += (CurrentDir > 0 ? 1 : -1);  
	 	UpdateTankGridLocation(); // 刷新坦克位置
	  	LastHorizontalDir = CurrentDir;
	  }
	//RenderFlipbookComponent->SetRelativeLocation(FVector(LastHorizontalDir,0,0));
	
	
	//AddActorLocalOffset(GetActorForwardVector()*32*AxisValue);
}

void APlayerTank::MoveFunctionforward(float AxisValue)
{ 
 
	//RenderFlipbookComponent->AddRelativeLocation(FVector(  AxisValue,0  , 0));
	// 1. 死区过滤：按键松开时重置状态（核心！）
	// const float DeadZone = 0.1f;
	// if (FMath::Abs(AxisValue) < DeadZone)
	// {
	// 	LastHorizontalDir = 0.0f; // 重置上下方向状态
	// 	return;
	// }
	float CurrentDir = FMath::Sign(AxisValue);
	// 仅方向变化时触发移动
	if (CurrentDir != LastVerticalDir)
	{
		CurrentGridY += (CurrentDir > 0 ? 1 : -1);  
		UpdateTankGridLocation(); // 刷新坦克位置
		LastVerticalDir = CurrentDir;
	}//RenderFlipbookComponent->SetRelativeLocation(FVector(0,LastVerticalDir,0));
}
void APlayerTank::PressedFunction()
{
	
	
}
void APlayerTank::ReleasedFunction()
{
	
	
}

void APlayerTank::UpdateTankGridLocation()
{
	FVector TargetPos = MapStartPos;//初始位置

	 
	// 左右移动  
	TargetPos.Y += CurrentGridX * GridStep;
	// 上下移动  
	TargetPos.X -= CurrentGridY * GridStep;

	// 瞬移到目标格子
  SetActorLocation(TargetPos);
}