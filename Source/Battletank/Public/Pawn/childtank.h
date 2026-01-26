// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/PlayerTank.h"
#include "childtank.generated.h"

UCLASS()
class BATTLETANK_API Achildtank : public APlayerTank
{
	GENERATED_BODY()
 
public:
    Achildtank();
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UPaperFlipbookComponent* FlipbookComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UPaperFlipbook* Sprite;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class Achildtank* NextBody;
	virtual void SetNextBody(Achildtank* Next);
	 UPROPERTY()
        TArray<FVector> PreLocationArray;//上一节蛇身的位置数组
     //提供一个上一节蛇传递位置的函数
     void AddPreLocationToArray(FVector PreSnakeLocation);
   //蛇身移动
    void BodyMove();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
