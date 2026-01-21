// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PlayerHud.h"

 
#include "UObject/ConstructorHelpers.h"
#include "Components/WidgetComponent.h"
#include "UI/gameoverpage.h"

#include "UI/MainUI.h"
#include "UObject/ObjectMacros.h"

// Sets default values
APlayerHud::APlayerHud()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	 
	
}

// Called when the game starts or when spawned
void APlayerHud::BeginPlay()
{
	Super::BeginPlay();
	 
	// 初始化并预加载所有UI实例
	CreateWidgetInstance();
	SwitchUI(EUIType::StartPage);
	 

}

// Called every frame
void APlayerHud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

 

void APlayerHud::SwitchUI(EUIType TargetUIType)
{HideUI();
	FString TargetPath;
	for (const FUIConfig& Config : UIConfigList)
	{
		if (Config.UITypes == TargetUIType)
		{
			TargetPath = Config.WidgetPath;
			break;
		}
	}
	 
	UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, *TargetPath);
	if (!WidgetClass) {
		 
		return;
	}
	UUserWidget* TargetWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	if (TargetWidget)
	{
		TargetWidget->AddToViewport();
		TargetWidget->SetVisibility(ESlateVisibility::Visible);
		CurrentActiveWidget = TargetWidget;
		 
	}

 }

void APlayerHud::HideUI()
{  
 
	if (CurrentActiveWidget)
	{
		CurrentActiveWidget->SetVisibility(ESlateVisibility::Hidden);
		CurrentActiveWidget = nullptr;
	}
}

//把所有ui都创建出来然后隐藏
void APlayerHud::CreateWidgetInstance()
{
	
	
	// 清空旧实例，避免重复创建
	AllUIInstances.Empty();
	 

	// 遍历UI配置列表 
	for (const FUIConfig& Config : UIConfigList)
	{
		if (Config.WidgetPath.IsEmpty())
		{
			 
			continue;
		}
		// 从路径加载Widget类 
		UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, *Config.WidgetPath);
		if (!WidgetClass)
		{
			 
			continue;
		}

		// 创建Widget实例 
		UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		if (NewWidget)
		{
			// 先隐藏，加入管理Map
			NewWidget->SetVisibility(ESlateVisibility::Hidden);
			AllUIInstances.Add(Config.UITypes, NewWidget);
		 
		}
	}
}
 