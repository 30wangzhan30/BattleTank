// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/childtank/childtank2.h"

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"


// Sets default values
Achildtank2:: Achildtank2()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	 
	 
	EnemyTag=2;
}

// Called when the game starts or when spawned
void Achildtank2::BeginPlay()
{
	Super::BeginPlay();
 
}

// Called every frame
void Achildtank2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void Achildtank2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

