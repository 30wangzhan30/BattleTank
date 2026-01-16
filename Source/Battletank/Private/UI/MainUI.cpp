// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUI.h"

#include "Components/Button.h"
#include "Engine/Engine.h"

void UMainUI ::NativeConstruct()
{
	 
	Super::NativeConstruct();

	 
	if (PlayerSingle)
	{ // 绑定"按下时"的事件
		PlayerSingle->OnClicked.AddDynamic(this, &UMainUI ::OnGameEnterButtonClicked); 
	}
	 
}

 
 void UMainUI::OnGameEnterButtonClicked() 
{   UE_LOG(LogTemp, Warning, TEXT("游戏进入按钮点击事件触发"));
 	}
