// Fill out your copyright notice in the Description page of Project Settings.

 
#include "UI/MainUI.h"


#include "EditorFontGlyphs.h"
#include "Animation/WidgetAnimation.h"
 
#include "Components/Button.h"
#include "Engine/Engine.h"
#include "UI/tankui.h"
 
 
void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();
PlayAnimation(animationstart);
	  
	if (PlayerSingle)
	{
	 
		PlayerSingle->OnClicked.AddDynamic(this, &UMainUI::OnGameEnterButtonClicked);
		PlayerSingle->OnHovered.AddDynamic(this, &UMainUI::OnGameEnterButtonHold);
		PlayerSingle->OnUnhovered.AddDynamic(this, &UMainUI::OnGameEnterButtonHold);
	}
	if (GetWorld() && GetWorld()->GetFirstPlayerController())
	{
		CurrentHud = Cast<APlayerHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
	}
}
 
 void UMainUI::OnGameEnterButtonClicked()
{ if (CurrentHud)
  	{ CurrentHud->SwitchUI(EUIType::SettingUI);
	 //CurrentHud->SwitchUI(EUIType:: LoadingPage);
  		//CurrentHud->SwitchUI(EUIType::GamePlayUI); // 切换到游戏中UI
  
  	 
  	}
}
void UMainUI::OnGameEnterButtonHold()
{
	
	PlayerSingle->SetBackgroundColor(FLinearColor(0.2f, 0.8f, 0.2f, 0.5f)); // 浅绿色（半透明）
	 
}
void UMainUI::OnGameEnterButtonHoldOver()
{
	PlayerSingle->SetBackgroundColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
	 
}
 
  