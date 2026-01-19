// Fill out your copyright notice in the Description page of Project Settings.
#include "Pawn/Startpagecontrol.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/gameoverpage.h"
#include "UI/tankui.h"

 
// Sets default values
AStartpagecontrol::AStartpagecontrol()
{
 
	PrimaryActorTick.bCanEverTick = true;
	
	 
	 TankAnimationWidget = nullptr;
	  TankAnimationWidgetClass =  LoadClass<Utankui>(this, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/StartPawn/uitank.uitank_C'")); ;
	//TankAnimationWidgetClass= LoadClass<Ugameoverpage>(this, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/StartPawn/gameover.gameover_C'")); 
}

// Called when the game starts or when spawned
void AStartpagecontrol::BeginPlay()
{
	Super::BeginPlay();
	
	 
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

