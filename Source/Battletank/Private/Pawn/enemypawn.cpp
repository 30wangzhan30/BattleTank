// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/enemypawn.h"
 
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
 
 


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

 

 
 

void Aenemypawn:: OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{ 	 	UE_LOG(LogTemp, Log, TEXT("hitttt"));
	
	OverlappedComponent->SetGenerateOverlapEvents(false);
	OverlappedComponent->DestroyComponent();
	OverlappedComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
