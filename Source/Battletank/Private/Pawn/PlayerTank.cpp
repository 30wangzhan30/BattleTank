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
	 
	    
	 
	
	// 绑定操作映射到函数 (玩家坦克写在子类里)
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &APlayerTank::OnMoveRightPressed);
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &APlayerTank::OnMoveLeftPressed);
	PlayerInputComponent->BindAction("MoveUp", IE_Pressed, this, &APlayerTank::OnMoveUpPressed);
	PlayerInputComponent->BindAction("MoveDown", IE_Pressed, this, &APlayerTank::OnMoveDownPressed);
	 
}
//想要实现计算瓦片地图每个格子的位置然后SetRelativeLocation到将要移动到的位置
void APlayerTank::OnMoveRightPressed( )
{
	// 向右移动1格
	CurrentGridX += 1;
	//更新朝向
	CurrentDirection = ETankDirection::Right; 
	UpdateTankRotation();
	// 更新实际位置
	UpdateTankGridLocation();  

}

void APlayerTank::OnMoveLeftPressed()
{ 
	
	CurrentGridX -= 1;
	//更新朝向
	CurrentDirection = ETankDirection::Left; 
	UpdateTankRotation();
	// 更新实际位置
	UpdateTankGridLocation();
}

void APlayerTank::OnMoveUpPressed( )
{
	CurrentGridY -= 1;
	//更新朝向
	CurrentDirection = ETankDirection::Up; 
	UpdateTankRotation();
	// 更新实际位置
	UpdateTankGridLocation();
}
void APlayerTank::OnMoveDownPressed( )
{
	CurrentGridY += 1;
	//更新朝向
	CurrentDirection = ETankDirection::Down; 
	UpdateTankRotation();
	// 更新实际位置
	UpdateTankGridLocation();
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


// 核心：根据朝向更新旋转角度
void  APlayerTank::UpdateTankRotation()
{
	FRotator NewRotation = FRotator::ZeroRotator;
    
	// UE中Yaw（偏航角）：0°=朝右，90°=朝上（前），180°=朝左，270°=朝下（后）
	switch (CurrentDirection)
	{
	case ETankDirection::Left:
		NewRotation.Yaw = 180.0f; // 初始朝向：左
		break;
	case ETankDirection::Right:
		NewRotation.Yaw = 0.0f;    // 朝右
		break;
	case ETankDirection::Up:
		NewRotation.Yaw =  270.0f;   // 朝上（前）
		break;
	case ETankDirection::Down:
		NewRotation.Yaw =90.0f;  // 朝下（后）
		break;
	}

	// 设置坦克旋转（平滑旋转可选，直接设置更适配格子移动）
	SetActorRotation(NewRotation);
}



//子弹逻辑