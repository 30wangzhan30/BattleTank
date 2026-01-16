// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapEditer.generated.h"

enum EGridType: uint8
{
	Empty = 0 UMETA(DisplayName = "空地"),
	Brick = 1 UMETA(DisplayName = "砖墙"),
	Steel = 2 UMETA(DisplayName = "钢墙"),
	Water = 3 UMETA(DisplayName = "河流"),
	Forest = 4 UMETA(DisplayName = "森林"),
	Ice = 5 UMETA(DisplayName = "冰面"),
	Home = 6 UMETA(DisplayName = "家"),
	PlayerStart = 7 UMETA(DisplayName = "玩家起始点"),
	Boundary = 8 UMETA(DisplayName = "边界"),
};

UCLASS()
class BATTLETANK_API AMapEditer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMapEditer();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MapEditer|MapContainer")
	FVector2D MapSize;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MapEditer|MapContainer")
	float GridSize;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MapEditer|MapContainer")
	float LineWidth;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MapEditer|MapContainer")
	FLinearColor LineColor;
	//创建地图容器
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="MapEditer|MapContainer")
	UStaticMeshComponent* MapContainer;
	
	//
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void DrawMapContainer();
};
