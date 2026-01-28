// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/childtank.h "


#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

// Sets default values
Achildtank::Achildtank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComponent"));
}

// Called when the game starts or when spawned
void Achildtank::BeginPlay()
{
	Super::BeginPlay();
	
	 Sprites = LoadObject<UPaperFlipbook>(this, TEXT("/Script/Paper2D.PaperFlipbook'/Game/PlayerControler/TankSprite/FlipBook.FlipBook'"));
	if ( Sprites)
	{
	 	FlipbookComponent->SetFlipbook( Sprites);
	}
}

// Called every frame
void Achildtank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); //BodyMove();
}
//接收到head生成的身体，每个新生成的身体会先走else设置nextbody的值为传入的spawn生成的下一截身体，然后走上面的if往下便利
void Achildtank::SetNextBody(Achildtank* Next)
{if (NextBody)
{//不是末尾就一直便利
	NextBody->SetNextBody(Next);
}
else
{ //便利到末尾把next赋给nextbody
	NextBody = Next;
	NextBody->SetActorLocation(GetActorLocation() +  FVector::ForwardVector * 45.f);
}
}

// Called to bind functionality to input
void Achildtank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
 
  
void Achildtank:: BodyMove()
{
	if (PreLocationArray.Num() >= 15)
	{
		// 判断到上一节已经移动了15次了，得到了至少15个位置的距离
		SetActorLocation(PreLocationArray[0]); // 根据上一节提供的位置，设置当前一节蛇身的位置
		if (NextBody)
		{
			NextBody->AddPreLocationToArray(PreLocationArray[0]);
		}
		PreLocationArray.RemoveAt(0); // 已经将上一节提供的这个位置点使用完成了，移除出数组
	}
}
   void Achildtank::AddPreLocationToArray(FVector PreSnakeLocation)
{
	PreLocationArray.Add(PreSnakeLocation);
}
