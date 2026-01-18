// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUI.h"


#include "EditorFontGlyphs.h"
#include "Animation/WidgetAnimation.h"
 
#include "Components/Button.h"
#include "Engine/Engine.h"
#include "UI/tankui.h"
 
void UMainUI ::NativeConstruct()
{
	 
	Super::NativeConstruct();
 
	PlayAnimation(animationstart); 
	if (PlayerSingle)
	{ // 绑定"按下时"的事件
		PlayerSingle->OnClicked.AddDynamic(this, &UMainUI ::OnGameEnterButtonClicked); 
		
	  
	
	}
	 
}

 
 void UMainUI::OnGameEnterButtonClicked()
{     // Utankui*uitank =Cast<Utankui>(Widget 
//float pos=	PlayerSingle->GetRenderTransform().Translation.X;
		//uitank.SetRenderTranslation( FVector2D(pos,PlayerSingle->GetRenderTransform().Translation.Y));
	this->SetVisibility(ESlateVisibility::Hidden);
}