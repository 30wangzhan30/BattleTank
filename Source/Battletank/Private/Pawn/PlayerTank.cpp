// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PlayerTank.h"


// Sets default values
APlayerTank::APlayerTank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TankFlipbook=LoadObject<UPaperFlipbook>(  this , TEXT("/Script/Paper2D.PaperFlipbook'/Game/bird/birds.birds'"));
	RenderFlipbookComponent->SetFlipbook(BindFlipbook);
	//RenderFlipbookComponent->OnComponentHit.AddDynamic(this, &AMypawn::OnComponentHitEvent );
	RenderFlipbookComponent->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMypawn::OnComponentBeginOverlapEvent);
}

// Called when the game starts or when spawned
void APlayerTank::BeginPlay()
{
	Super::BeginPlay();
	
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
}

