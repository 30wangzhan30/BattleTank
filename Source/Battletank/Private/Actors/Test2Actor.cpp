// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Test2Actor.h"


// Sets default values
ATest2Actor::ATest2Actor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATest2Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATest2Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

