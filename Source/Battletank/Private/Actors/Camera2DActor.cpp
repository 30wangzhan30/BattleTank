// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Camera2DActor.h"


 

ACamera2DActor::ACamera2DActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// 创建根组件
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));
	RootComponent = Root;

	// 创建弹簧臂（适配2D视角）
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f)); // 2D视角标准旋转
	CameraSpringArm->TargetArmLength = 200.0f; // 摄像机距离（根据你的场景调整）
	CameraSpringArm->bDoCollisionTest = false; // 2D视角关闭碰撞检测
	CameraSpringArm->SetRelativeLocation(FVector(0, 0, 200.0f)); // 抬高弹簧臂Z轴
	// 创建2D摄像机（纯正交模式）
	Main2DCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main2DCamera"));
	Main2DCamera->SetupAttachment(CameraSpringArm);
	Main2DCamera->SetProjectionMode(ECameraProjectionMode::Orthographic); // 纯正交（2D必选）
	Main2DCamera->SetOrthoWidth(2500.0f); // 2D视口宽度（适配你的贴图尺寸）
	Main2DCamera->SetRelativeLocation(FVector(0, 0, 0)); // 正交模式位置无需偏移
}

void ACamera2DActor::BeginPlay()
{
	Super::BeginPlay(); SetActorLocation(FVector(0, 0, 200.0f)); // Z轴200，覆盖坦克的2D渲染层
	// 自动找到玩家Pawn（可选，用于跟随）
	TargetPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void ACamera2DActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//  摄像机跟随玩家
	if (TargetPawn && FollowSpeed > 0)
	{
		FVector TargetLocation = TargetPawn->GetActorLocation();
		TargetLocation.Z = GetActorLocation().Z+200; // 固定Z轴
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), TargetLocation, DeltaTime, FollowSpeed));
	}
}