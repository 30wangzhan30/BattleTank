// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/enemypawn.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Pawn/childtank.h"


// Sets default values
Aenemypawn::Aenemypawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	 
	 RootCapsule  = Cast<UCapsuleComponent>(GetRootComponent());
	if (IsValid(RootComponent))
	{
		RootCapsule ->SetCapsuleRadius (15.0f);
		RootCapsule->SetCapsuleHalfHeight (15.0f);
	  box =CreateDefaultSubobject<UBoxComponent>("enemy");
	 	 
		RootCapsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//	RootCapsule->SetSimulatePhysics(true);
	}
	Tags.Add(TEXT("Enemy"));
}

// Called when the game starts or when spawned
void Aenemypawn::BeginPlay()
{
	Super::BeginPlay();
	//Sprites = LoadObject<UPaperFlipbook>(this, TEXT("/Script/Paper2D.PaperFlipbook'/Game/PlayerControler/TankSprite/FlipBook.FlipBook'"));
	 
	  box->OnComponentBeginOverlap.AddDynamic(this, &Aenemypawn::OnEnemyOverlap);
}

// Called every frame
void Aenemypawn::Tick(float DeltaTime)
{  
	Super::Tick(DeltaTime);
	//SetSpawnNextBody();
 //BodyMove(DeltaTime);
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

void Aenemypawn::BodyMove(float Deltatime)
{static float _Speed = 0;
	_Speed =50 *Deltatime;
	//AddActorLocalOffset( FlipbookComponent-> GetForwardVector() * _Speed);
	if (NextBody)
	{
		// Tick每执行一次，就会传递一个位置点
		NextBody->AddPreLocationToArray(GetActorLocation()); // 如果存在下一节蛇身，就在每移动一次的时候传递一次位置
	}
}

 

void Aenemypawn:: OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{ 	 	UE_LOG(LogTemp, Log, TEXT("hitttt"));
	
	OverlappedComponent->SetGenerateOverlapEvents(false);
	OverlappedComponent->DestroyComponent();
	OverlappedComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
