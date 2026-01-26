// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/enemypawn.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Pawn/childtank.h"


// Sets default values
Aenemypawn::Aenemypawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT(" FlipbookComponent"));
	Tags.Add(TEXT("Enemy"));
}

// Called when the game starts or when spawned
void Aenemypawn::BeginPlay()
{
	Super::BeginPlay();
	Sprite = LoadObject<UPaperFlipbook>(this, TEXT("/Script/Paper2D.PaperFlipbook'/Game/PlayerControler/TankSprite/FlipBook.FlipBook'"));
	if ( Sprite)
	{
		FlipbookComponent->SetFlipbook( Sprite);
	}
}

// Called every frame
void Aenemypawn::Tick(float DeltaTime)
{  
	Super::Tick(DeltaTime);
	SetSpawnNextBody();
}

void Aenemypawn::SetSpawnNextBody( )
{
	Achildtank*currentbody=GetWorld()->SpawnActor<Achildtank>(Achildtank::StaticClass());
	{if (NextBody)
	{//第二次查找就跳转到这里， 这个next是第二节身体，每次新生成一截身体就传给setnextbody便利
		NextBody->SetNextBody( currentbody);
	}
	else
	{
		NextBody = currentbody;//一开始只有头没有下一截nextbody，把生成的current给next
		NextBody->SetActorLocation(GetActorLocation() + FVector::ForwardVector * 45.f);
	}
	}
}
// Called to bind functionality to input
void Aenemypawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

