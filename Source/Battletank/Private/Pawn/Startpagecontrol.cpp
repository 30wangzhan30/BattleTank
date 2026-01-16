// Fill out your copyright notice in the Description page of Project Settings.
#include "Pawn/Startpagecontrol.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"


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
	
	
	if (!PC)
	{
		PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (!PC) return;
	}

	//  获取鼠标屏幕坐标
	FVector2D MouseScreenPos;
	if (!PC->GetMousePosition(MouseScreenPos.X, MouseScreenPos.Y))
	{
		return;
	}

	//  屏幕坐标转世界坐标 
	FVector WorldPos;
	FVector WorldDir;
	if (!PC->DeprojectScreenPositionToWorld(MouseScreenPos.X, MouseScreenPos.Y, WorldPos, WorldDir))
	{
		return;
	}
	WorldPos.Z = 0;

	// 3. 获取坦克当前位置 
	FVector ActorPos = this->GetActorLocation();
	 
	 
	//this->SetActorLocation(ActorPos); 
	 
	 

	//  计算方向+转向 
	FVector DirectionToMouse = (WorldPos - ActorPos).GetSafeNormal();
	FRotator TargetRot = UKismetMathLibrary::MakeRotFromX(DirectionToMouse);
	if (DirectionToMouse.IsNearlyZero())
	{
		DirectionToMouse = FVector(100, 0, 0); //  
	}
	DirectionToMouse.Normalize();
	// 调整速度 
	float TankRotateSpeed = 3.0f;    
	float TankMoveSpeed = 100.0f;    

	// 平滑转向
	FRotator CurrentRot = this->GetActorRotation();
	FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetRot, DeltaTime, TankRotateSpeed);
	 
	   this->SetActorRotation(NewRot);

	// 计算移动增量
	FVector MoveDelta = DirectionToMouse  * TankMoveSpeed * DeltaTime;
	FVector NewActorPos = ActorPos + MoveDelta;

  

	//  设置新位置 
	 this->SetActorLocation(NewActorPos);
 
	
}

// Called to bind functionality to input
void AStartpagecontrol::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

