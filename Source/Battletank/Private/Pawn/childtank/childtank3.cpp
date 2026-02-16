// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/childtank/childtank3.h"

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"


// Sets default values
Achildtank3::Achildtank3()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
 
	 
	EnemyTag=3;
}

// Called when the game starts or when spawned
void Achildtank3::BeginPlay()
{
	Super::BeginPlay();
 
}

// Called every frame
void Achildtank3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void Achildtank3::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

