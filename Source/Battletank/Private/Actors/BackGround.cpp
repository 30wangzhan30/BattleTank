// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BackGround.h"
#include "PaperTileMapComponent.h"  

// Sets default values
ABackGround::ABackGround()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LoadedTileMap = CreateDefaultSubobject<UPaperTileMap>("LoadedTileMap");
	TileMapComponent = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("TileMapComponent"));
	RootComponent = TileMapComponent;
}

// Called when the game starts or when spawned
void ABackGround::BeginPlay()
{
	Super::BeginPlay();
	LoadedTileMap =LoadObject<UPaperTileMap>(  this , TEXT("/Script/Paper2D.PaperTileMap'/Game/瓦片地图/BackGround.BackGround'"));
	TileMapComponent->SetTileMap(LoadedTileMap);

}

// Called every frame
void ABackGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

