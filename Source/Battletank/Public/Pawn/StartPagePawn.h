// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Pawn.h"
#include "StartPagePawn.generated.h"

UCLASS()
class BATTLETANK_API AStartPagePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AStartPagePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	 
	virtual void Tick(float DeltaTime) override;
	
	// 声明Widget组件（用于承载UI的核心组件）
	UPROPERTY(VisibleAnywhere, Category = "UI Widget")
	UWidgetComponent* TankWidgetComponent;

	// 要加载的Widget蓝图类（在蓝图中指定，比如你的GameEnterPanel）
	UPROPERTY(EditAnywhere, Category = "UI Widget")
	TSubclassOf<UUserWidget> TargetWidgetClass;

	// 初始化Widget组件的辅助函数
	void InitWidgetComponent();

	// 动态生成并显示Widget的函数
	void SpawnAndShowWidget();
	 
};
