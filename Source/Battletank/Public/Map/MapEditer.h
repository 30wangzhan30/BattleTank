// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapEditer.generated.h"

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
	FLinearColor GridColor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void DrawMapContainer();
};
