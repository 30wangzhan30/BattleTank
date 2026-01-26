// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/childtank.h "

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

// Sets default values
Achildtank::Achildtank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	 
}

// Called when the game starts or when spawned
void Achildtank::BeginPlay()
{
	Super::BeginPlay();
	
	 Sprite = LoadObject<UPaperFlipbook>(this, TEXT("/Script/Paper2D.PaperFlipbook'/Game/PlayerControler/TankSprite/FlipBook.FlipBook'"));
	if ( Sprite)
	{
	 	FlipbookComponent->SetFlipbook( Sprite);
	}
}

// Called every frame
void Achildtank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	NextBody->SetActorLocation(GetActorLocation() + GetActorUpVector() * -45.f);
}
}

// Called to bind functionality to input
void Achildtank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

 
 