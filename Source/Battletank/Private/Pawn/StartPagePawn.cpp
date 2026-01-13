// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/StartPagePawn.h"
#include "Components/WidgetComponent.h"
#include "UI/MainUI.h"
// Sets default values
AStartPagePawn::AStartPagePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	 
	// 将Widget组件挂载到根组件（如果根组件为空，设为根组件）
	if (!RootComponent)
	{
		RootComponent = TankWidgetComponent;
	}
	else
	{
	//	TankWidgetComponent->SetupAttachment(RootComponent);
	}

 
//	TankWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen); // 屏幕空间（UI跟随屏幕，不是世界空间）
//	TankWidgetComponent->SetDrawSize(FVector2D(800, 600));    // Widget显示大小（宽800，高600）
	//TankWidgetComponent->SetVisibility(false);                // 初始隐藏，按需显示
 
}

// Called when the game starts or when spawned
void AStartPagePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStartPagePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
 