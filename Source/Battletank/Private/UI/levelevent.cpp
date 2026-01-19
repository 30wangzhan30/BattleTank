// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/levelevent.h"
 
 

void Ulevelevent::NativeConstruct()
{
	Super::NativeConstruct();
	enter->OnClicked.AddDynamic(this, &Ulevelevent ::OnEnterButtonClicked); 
	rewrite->OnClicked.AddDynamic(this, &Ulevelevent ::OnRewriteButtonClicked); 
	look->OnClicked.AddDynamic(this, &Ulevelevent ::OnlookButtonClicked); 
	deleted->OnClicked.AddDynamic(this, &Ulevelevent ::OndeletedButtonClicked); 
}

void Ulevelevent::OnEnterButtonClicked()
{
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

