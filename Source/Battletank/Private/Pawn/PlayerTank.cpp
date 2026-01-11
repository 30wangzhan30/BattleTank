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
	TankFlipbook=LoadObject<UPaperFlipbook>(  this , TEXT("/Script/Paper2D.PaperFlipbook'/Game/PlayerControler/TankSprite/FlipBook.FlipBook'"));
 
	if (RenderFlipbookComponent && TankFlipbook)
	{
		RenderFlipbookComponent->SetFlipbook(TankFlipbook);
		RenderFlipbookComponent->SetRelativeRotation(FRotator( -90.0f,  0.0f,  0.0f) );
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

void APlayerTank::MoveFunctionupdown(float AxisValue)
{
	if (AxisValue == 0) return;//没有按键, 不执行任何的逻辑
	//RenderFlipbookComponent->SetRelativeLocation(FVector(AxisValue,0,0));
	RenderFlipbookComponent->AddRelativeLocation(FVector(  0,  AxisValue, 0));

}

void APlayerTank::MoveFunctionforward(float AxisValue)
{
	if (AxisValue == 0) return;//没有按键, 不执行任何的逻辑
	RenderFlipbookComponent->AddRelativeLocation(FVector(  AxisValue,0  , 0));
	 
}
void APlayerTank::PressedFunction()
{
	
	
}
void APlayerTank::ReleasedFunction()
{
	
	
}