// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MainUI.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Hud.h"
#include "UI/gameoverpage.h"
#include "PlayerHud.generated.h"

UCLASS()
class BATTLETANK_API APlayerHud : public AHUD
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerHud();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	 
	virtual void Tick(float DeltaTime) override;
	 
	 
	void SwitchUI(const FString& WidgetPath);  

	// 保存当前显示的Widget实例
	UPROPERTY(VisibleAnywhere, Category = "UI State")
	UUserWidget* CurrentActiveWidget;
	// 声明Widget组件（用于承载UI的核心组件）
	UPROPERTY(VisibleAnywhere, Category = "UI Widget")
	UMainUI* TankWidgetComponent;
	UPROPERTY(VisibleAnywhere, Category = "UI Widget")
	Ugameoverpage* OVERComponent;

	// 要加载的Widget蓝图类（在蓝图中指定，比如你的GameEnterPanel）
	UPROPERTY(EditAnywhere, Category = "UI Widget")
	TSubclassOf<UUserWidget> TargetWidgetClass;
	
    UPROPERTY(EditAnywhere, Category = "UI Widget")
	TSubclassOf<UUserWidget> StartPageWidgetClass; // 开始游戏页面

	UPROPERTY(EditAnywhere, Category = "UI Widget")
	TSubclassOf<UUserWidget> InGameWidgetClass; // 游戏中页面

	UPROPERTY(EditAnywhere, Category = "UI Widget")
	TSubclassOf<UUserWidget> AddPointWidgetClass; // 加点数页面
	
	void CreateWidgetInstance();
	// 初始化Widget组件的辅助函数
	void InitWidgetComponent();

	// 动态生成并显示Widget的函数
	void SpawnAndShowWidget();
	 
};
