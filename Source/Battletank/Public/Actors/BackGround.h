 
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperTileMap.h"
#include "PaperTileMapComponent.h"

#include "BackGround.generated.h"
UCLASS()
class BATTLETANK_API ABackGround : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABackGround();

protected:
	// Called when the game starts or when spawned
	

public:
	// Called every frame
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, Category = "TileMap")
	UPaperTileMapComponent* TileMapComponent;
	UPROPERTY()
	UPaperTileMap* LoadedTileMap;
};
