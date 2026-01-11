// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerTank.generated.h"

UCLASS()
class BATTLETANK_API APlayerTank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerTank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveFunctionupdown(float AxisValue);
	void MoveFunctionforward(float AxisValue);
	void  PressedFunction();
	void ReleasedFunction();
 
	//渲染序列帧动画的组件
	class UPaperFlipbookComponent* RenderFlipbookComponent;
	//资产
	class UPaperFlipbook* TankFlipbook;
	class USphereComponent * Sphere;
};
 