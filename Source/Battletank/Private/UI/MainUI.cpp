// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUI.h"

#include "Components/Button.h"
#include "Engine/Engine.h"

void UMainUI ::NativeConstruct()
{
	 
	Super::NativeConstruct();

	 
	if (GameEnterButton)
	{ // 绑定"按下时"的事件
		GameEnterButton->OnClicked.AddDynamic(this, &UMainUI ::OnGameEnterButtonClicked); 
	}
	 
	else
	{
		 
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT(" GameEnterButton绑定失败！请检查蓝图中控件名是否一致！"));
	}
}

// 按钮点击的测试函数（核心测试逻辑）
void UMainUI ::OnGameEnterButtonClicked()
{
	 
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT(" 开始游戏按钮点击成功！"));
	}
