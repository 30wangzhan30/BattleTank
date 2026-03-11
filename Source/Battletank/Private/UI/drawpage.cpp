// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/drawpage.h"

#include "Editor/WidgetCompilerLog.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/PlayerHud.h"

void Udrawpage::NativeConstruct()
{
	Super::NativeConstruct();
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	CurrentHud = Cast<APlayerHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
	Return->OnClicked.AddDynamic(this, &Udrawpage ::ReturnTo);
	 grass->OnClicked.AddDynamic(this, &Udrawpage ::DrawGrass); 
	 brick->OnClicked.AddDynamic(this, &Udrawpage ::DrawBrick); 
	 water->OnClicked.AddDynamic(this, &Udrawpage ::DrawWater); 
	 steelbrick->OnClicked.AddDynamic(this, &Udrawpage ::DrawSteelBrick); 
	if (Save != nullptr)
	{   Save->OnClicked.AddDynamic(this, &Udrawpage ::SaveMap);}
 
}
void Udrawpage::ReturnTo()
{   if (CurrentHud)
 CurrentHud->SwitchUI(EUIType::SettingUI);
		 
	 
}
void Udrawpage:: SaveMap()
{
	
	 
	TArray<AActor*> MapEditerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMapEditer::StaticClass(), MapEditerActors);
    
 
	AMapEditer* MapEditer = Cast<AMapEditer>(MapEditerActors[0]);
	 
 
	// 3. 调用地图编辑器的保存函数
	 bool bSaveSuccess = MapEditer->SaveMapToFile();
    
	// 4. 保存结果反馈（日志+可选UI提示）
	 if (bSaveSuccess)
	{
		UE_LOG(LogTemp, Log, TEXT("地图保存成功！关卡名：%s"), *MapEditer->CurrentLevelName);
		 
	}else
	{
		UE_LOG(LogTemp, Log, TEXT("保存地图失败")) ;
	} 
}
void Udrawpage::OnDraw(ETileType TileType)
{   
	TArray<AActor*> MapEditerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMapEditer::StaticClass(), MapEditerActors);
	

	AMapEditer* MapEditer = Cast<AMapEditer>(MapEditerActors[0]);
	if (!IsValid(MapEditer))
	{
		 
		return;
	}

	// 2. 根据UI传入的ETileType，转换为地图格子的EGridType
	 
	EGridType TargetGridType = EGridType::Empty; 

	switch (TileType)
	{
	case ETileType::Forest:     TargetGridType=EGridType::Forest;   break;
	case ETileType::River:       TargetGridType=EGridType::River;   break;
	case ETileType::Brick:       TargetGridType=EGridType::Brick;   break;
	case ETileType::Steel:      TargetGridType=EGridType::Steel;   break;
	case ETileType::PlayerStart: TargetGridType=EGridType::PlayerStart;   break;
	case ETileType::Empty:       TargetGridType=EGridType::Empty;   break;
	default:break;
	}    MapEditer->SelectedTileType = TargetGridType;
}


void Udrawpage::DrawGrass()
{OnDraw (ETileType::Forest);
}

void Udrawpage::DrawWater()
{OnDraw (ETileType::River);
}

void Udrawpage::DrawBrick()
{OnDraw (ETileType::Brick);
}

void Udrawpage::DrawSteelBrick()
{OnDraw (ETileType::Steel);
}

void Udrawpage::Drawhome()
{OnDraw (ETileType::PlayerStart);
}

void Udrawpage::OnErase()
{
}
