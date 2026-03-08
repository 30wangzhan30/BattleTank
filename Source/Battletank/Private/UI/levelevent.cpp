// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/levelevent.h"

#include "Kismet/GameplayStatics.h"
#include "Map/MapEditer.h"
#include "Pawn/PlayerHud.h"


void Ulevelevent::NativeConstruct()
{
	Super::NativeConstruct();
	CurrentHud = Cast<APlayerHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
	enter->OnClicked.AddDynamic(this, &Ulevelevent ::OnEnterButtonClicked); 
	rewrite->OnClicked.AddDynamic(this, &Ulevelevent ::OnRewriteButtonClicked); 
	look->OnClicked.AddDynamic(this, &Ulevelevent ::OnlookButtonClicked); 
	deleted->OnClicked.AddDynamic(this, &Ulevelevent ::OndeletedButtonClicked); 
	newmap->OnClicked.AddDynamic(this, &Ulevelevent ::Onmapcreate); 
}

void Ulevelevent::OnEnterButtonClicked()
{
	CurrentHud->SwitchUI(EUIType::LoadingPage);
	TArray<AActor*> MapEditerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMapEditer::StaticClass(), MapEditerActors);
    
 
	AMapEditer* MapEditer = Cast<AMapEditer>(MapEditerActors[0]);
	MapEditer->LoadMapFromFile("");
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

void Ulevelevent::Onmapcreate()
{
	CurrentHud->SwitchUI(EUIType::Mapcreate);
}

