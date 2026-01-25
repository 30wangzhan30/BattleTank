// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/levelevent.h"

#include "Pawn/PlayerHud.h"


void Ulevelevent::NativeConstruct()
{
	Super::NativeConstruct();
	CurrentHud = Cast<APlayerHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
	enter->OnClicked.AddDynamic(this, &Ulevelevent ::OnEnterButtonClicked); 
	rewrite->OnClicked.AddDynamic(this, &Ulevelevent ::OnRewriteButtonClicked); 
	look->OnClicked.AddDynamic(this, &Ulevelevent ::OnlookButtonClicked); 
	deleted->OnClicked.AddDynamic(this, &Ulevelevent ::OndeletedButtonClicked); 
}

void Ulevelevent::OnEnterButtonClicked()
{
	CurrentHud->SwitchUI(EUIType::LoadingPage);
}

void Ulevelevent::OnRewriteButtonClicked()
{
}

void Ulevelevent::OnlookButtonClicked()
{
}

void Ulevelevent::OndeletedButtonClicked()
{
}

