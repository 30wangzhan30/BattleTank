// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/MapEditer.h"


// Sets default values
AMapEditer::AMapEditer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMapEditer::BeginPlay()
{
	Super::BeginPlay();
	DrawMapContainer();
	
}

// Called every frame
void AMapEditer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMapEditer::DrawMapContainer()
{
	UStaticMeshComponent* MapContainer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MapContainer"));
	UStaticMesh* MapContainerMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	MapContainer -> SetStaticMesh(MapContainerMesh);
	MapContainer -> SetWorldScale3D(FVector(MapSize.X * GridSize / 100.f, MapSize.Y * GridSize / 100.f, 1.0f));
	MapContainer -> SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
}

