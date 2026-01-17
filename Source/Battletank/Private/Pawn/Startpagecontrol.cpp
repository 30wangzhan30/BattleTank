// Fill out your copyright notice in the Description page of Project Settings.
#include "Pawn/Startpagecontrol.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/tankui.h"

// Sets default values
AStartpagecontrol::AStartpagecontrol()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// RenderFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("RenderFlipbookComponent"));
	// RootComponent = RenderFlipbookComponent; // 设置为根组件，确保显示
	// TankFlipbookMouse = CreateDefaultSubobject<UPaperFlipbook>(TEXT("TankFlipbook"));
	 TankAnimationWidget = nullptr;
	 TankAnimationWidgetClass =  LoadClass<Utankui>(this, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/StartPawn/Mytankui.Mytankui_C'")); ;
}

// Called when the game starts or when spawned
void AStartpagecontrol::BeginPlay()
{
	Super::BeginPlay();
	
	// TankFlipbookMouse=LoadObject<UPaperFlipbook>(  this , TEXT("/Script/Paper2D.PaperFlipbook'/Game/PlayerControler/TankSprite/FlipBook.FlipBook'"));
	//
	// if ( TankFlipbookMouse)
	// {
	// 	RenderFlipbookComponent->SetFlipbook(TankFlipbookMouse);
	// 	RenderFlipbookComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	// 	// 3. 调整坦克大小（鼠标样式要小）
	// 	RenderFlipbookComponent->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
	;
	TankAnimationWidget = CreateWidget<UUserWidget>(GetWorld(), TankAnimationWidgetClass);
	if (TankAnimationWidget)
	{  
		// 添加到视口（和你的开始游戏UI同层）
		TankAnimationWidget->AddToViewport();
	 
	}


		 
		 
	 

	}
 

// Called every frame
void AStartpagecontrol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	 
	 
	
		}
	 
	 

// Called to bind functionality to input
void AStartpagecontrol::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

