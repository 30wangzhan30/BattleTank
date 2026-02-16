// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/childtank/childtank.h"

 

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

// Sets default values
Achildtank1::Achildtank1()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	 
	 
	EnemyTag=1;
}

// Called when the game starts or when spawned
void Achildtank1::BeginPlay()
{
	Super::BeginPlay();
	 
	 
	 
}

// Called every frame
void Achildtank1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); //BodyMove();
}
 

// Called to bind functionality to input
void Achildtank1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
 
  
 