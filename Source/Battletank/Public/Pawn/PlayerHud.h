// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
 
 
#include "GameFramework/Hud.h"
#include "UI/gameoverpage.h"
#include "PlayerHud.generated.h"
UENUM(BlueprintType)
enum class EUIType : uint8
{
	StartPage,    // 开始页面
	LoadingPage,  //加载页面
	GameOverPage, // 游戏结束页面
	GamePlayUI,   // 游戏中UI 
	SettingUI     // 设置UI 
};

//  
USTRUCT(BlueprintType)
struct FUIConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUIType UITypes;  

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WidgetPath;
};
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
	 
	void CreateWidgetInstance();
	void SwitchUI(EUIType TargetUIType);  
	void HideUI();

	// 保存当前显示的Widget实例
	UPROPERTY(VisibleAnywhere, Category = "UI State")
	UUserWidget* CurrentActiveWidget;
	// 声明Widget组件（用于承载UI的核心组件）
	//UPROPERTY(VisibleAnywhere, Category = "UI Widget")
	//UMainUI* TankWidgetComponent;
	//UPROPERTY(VisibleAnywhere, Category = "UI Widget")
	//Ugameoverpage* OVERComponent;

	// 要加载的Widget蓝图类（在蓝图中指定，比如你的GameEnterPanel）
	UPROPERTY(EditAnywhere, Category = "UI Widget")
	TSubclassOf<UUserWidget> TargetWidgetClass;
	
	UPROPERTY(EditAnywhere, Category = "UI Widget")
	TSubclassOf<UUserWidget> StartPageWidgetClass; // 开始游戏页面

	UPROPERTY(EditAnywhere, Category = "UI Widget")
	TSubclassOf<UUserWidget> InGameWidgetClass; // 游戏中页面

	UPROPERTY(EditAnywhere, Category = "UI Widget")
	TSubclassOf<UUserWidget> GameOverWidgetClass; //   
	
	UPROPERTY(EditAnywhere, Category = "UI Widget")
	TSubclassOf<UUserWidget> LoadingWidgetClass; //  
	
	UPROPERTY(EditAnywhere, Category = "UI Widget")
	TSubclassOf<UUserWidget> SettingWidgetClass; //  
	 
	// 存储所有UI实例 
	TMap<EUIType, UUserWidget*> AllUIInstances;

	// 当前显示的UI类型
	EUIType CurrentUIType = EUIType::StartPage;

	// UI配置列表 
	UPROPERTY(EditDefaultsOnly, Category = "UI Config")
	TArray<FUIConfig> UIConfigList;
	 
};
