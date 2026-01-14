// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/enemypawn.h"


// Sets default values
Aenemypawn::Aenemypawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	 
	Tags.Add(TEXT("Enemy"));
}

// Called when the game starts or when spawned
void Aenemypawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Aenemypawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void Aenemypawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

