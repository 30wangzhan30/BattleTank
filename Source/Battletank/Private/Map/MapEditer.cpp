// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/MapEditer.h"

#include "DataWrappers/ChaosVDParticleDataWrapper.h"


// Sets default values
AMapEditer::AMapEditer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}
	
	//创建地图容器
	MapContainer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MapContainer"));
	MapContainer -> SetupAttachment(RootComponent);
	UStaticMesh* MapContainerMesh = LoadObject<UStaticMesh>(this, TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	MapContainer -> SetStaticMesh(MapContainerMesh);
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
	//设置地图容器的大小并绘制地图网格
	MapContainer -> SetWorldScale3D(FVector(MapSize.X / 100.f, MapSize.Y / 100.f, 1.0f));
	MapContainer -> SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	UMaterialInstanceDynamic* MapContainerMaterial = UMaterialInstanceDynamic::Create(LoadObject<UMaterialInstance>(nullptr,TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/Mat_MapGrid_Inst.Mat_MapGrid_Inst'")), this);
	MapContainerMaterial -> SetVectorParameterValue(TEXT("LineColor"), LineColor);
	MapContainerMaterial -> SetScalarParameterValue(TEXT("GridSize"), GridSize);
	MapContainerMaterial -> SetScalarParameterValue(TEXT("LineWidth"), LineWidth);
	MapContainer -> SetMaterial(0, MapContainerMaterial);
}



