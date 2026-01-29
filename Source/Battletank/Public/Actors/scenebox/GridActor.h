// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridActor.generated.h"

class UBoxComponent;
class UPaperSprite;
class UPaperSpriteComponent;

UENUM()
enum class EGridType: uint8
{
	Empty = 0 UMETA(DisplayName = "空地"),
	Brick = 1 UMETA(DisplayName = "砖墙"),
	Steel = 2 UMETA(DisplayName = "钢墙"),
	River = 3 UMETA(DisplayName = "河流"),
	Forest = 4 UMETA(DisplayName = "森林"),
	Ice = 5 UMETA(DisplayName = "冰面"),
	Home = 6 UMETA(DisplayName = "家"),
	PlayerStart = 7 UMETA(DisplayName = "玩家起始点"),
	Boundary = 8 UMETA(DisplayName = "边界"),
};


UCLASS()
class BATTLETANK_API AGridActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGridActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
	UPaperSpriteComponent* GridRenderer;
	 
	
	
	UPROPERTY(EditAnywhere,Category="GridActor|Sprites")
	UPaperSprite* EmptyGrid;
	UPROPERTY(EditAnywhere,Category="GridActor|Sprites")
	TArray<UPaperSprite*> BrickGrid;
	UPROPERTY(EditAnywhere,Category="GridActor|Sprites")
	TArray<UPaperSprite*> SteelGrid;
	UPROPERTY(EditAnywhere,Category="GridActor|Sprites")
	UPaperSprite* RiverGrid;
	UPROPERTY(EditAnywhere,Category="GridActor|Sprites")
	UPaperSprite* ForestGrid;
	UPROPERTY(EditAnywhere,Category="GridActor|Sprites")
	UPaperSprite* IceGrid;
	UPROPERTY(EditAnywhere,Category="GridActor|Sprites")
	UPaperSprite* HomeGrid;
	UPROPERTY(EditAnywhere,Category="GridActor|Sprites")
	UPaperSprite* PlayerStartGrid;
	UPROPERTY(EditAnywhere,Category="GridActor|Sprites")
	UPaperSprite* BoundaryGrid;
	
	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* GridCollision;
	 
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* GridTrigger;
	
	
	UPROPERTY(EditAnywhere,Category="GridActor|GridType")
	EGridType CurrentGridType;
	void GridInit(EGridType GridType);

	
	void AddGridCollision();
	void AddBrickGridCollision( UPaperSpriteComponent* ,int Index);
	void RemoveGridCollision();
	void RemoveBrickGridCollision();
	UFUNCTION()
	void OnGridTriggered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void AddTrigger();
	void RemoveGridTrigger();
	
	//Brick Grid
	UPROPERTY()
	TArray<UPaperSpriteComponent*> BrickGridRenders;
	UPROPERTY()
	TArray<UBoxComponent*> BrickGridComponent;
	 
	void AddBrickGrids();
	void ClearBrickGrids();
	
	UPROPERTY()
	TArray<UPaperSpriteComponent*> SteelGridRenders;
	void AddSteelGrids();
	void ClearSteelGrids();
	
};
