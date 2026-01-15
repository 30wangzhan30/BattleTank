// Fill out your copyright notice in the Description page of Project Settings.

#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Pawn/Startpagecontrol.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AStartpagecontrol::AStartpagecontrol()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RenderFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("RenderFlipbookComponent"));
	RootComponent = RenderFlipbookComponent; // 设置为根组件，确保显示
	TankFlipbookMouse = CreateDefaultSubobject<UPaperFlipbook>(TEXT("TankFlipbook"));
	
}

// Called when the game starts or when spawned
void AStartpagecontrol::BeginPlay()
{
	Super::BeginPlay();
	
	TankFlipbookMouse=LoadObject<UPaperFlipbook>(  this , TEXT("/Script/Paper2D.PaperFlipbook'/Game/PlayerControler/TankSprite/FlipBook.FlipBook'"));
 
	if ( TankFlipbookMouse)
	{
		RenderFlipbookComponent->SetFlipbook(TankFlipbookMouse);
		RenderFlipbookComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
		// 3. 调整坦克大小（鼠标样式要小）
		RenderFlipbookComponent->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
		 ;
		
		
		PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	}
}

// Called every frame
void AStartpagecontrol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	FVector2D MouseScreenPos;
	PC->GetMousePosition(MouseScreenPos.X, MouseScreenPos.Y);

	// 2. 屏幕坐标转世界坐标（让Actor跟随）
	FVector WorldPos;
	FVector WorldDir;
	PC->DeprojectScreenPositionToWorld(MouseScreenPos.X, MouseScreenPos.Y, WorldPos, WorldDir);

	// 3. 让挂载该组件的Actor跟随鼠标移动
	FVector ActorPos = this->GetActorLocation();
	ActorPos.X = WorldPos.X;
	ActorPos.Y = WorldPos.Y; 
	//this->SetActorLocation(ActorPos);
	
	 
	FVector MouseWorldPos;
	//  计算坦克到鼠标的方向向量 + 目标角度
	FVector DirectionToMouse = (MouseWorldPos - ActorPos).GetSafeNormal(); // 归一化方向向量
	FRotator TargetRot = UKismetMathLibrary::MakeRotFromX(DirectionToMouse); // 从方向向量生成旋转角
	
	float TankRotateSpeed=50;
	float TankMoveSpeed=50;
	 
	
	FRotator CurrentRot=this->GetActorRotation();
	FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetRot, DeltaTime, TankRotateSpeed);
	this->SetActorRotation(NewRot);
	FVector MoveDelta = NewRot.Vector() * TankMoveSpeed * DeltaTime; // 按朝向和速度移动
	this->SetActorLocation(MoveDelta);
	
	
}

// Called to bind functionality to input
void AStartpagecontrol::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

