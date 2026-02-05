#include "UI/Gameplay.h"

#include "Kismet/GameplayStatics.h"
#include "UI/tankui.h"

void UGameplay::NativeConstruct()
{
	Super::NativeConstruct();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),   Aenemypawn::StaticClass(), enemys);
	enemycount = enemys.Num();
	num ->SetText(FText::FromString(FString::Printf(TEXT("剩余敌人：%d"), enemycount)));

	//panel->AddChildToGrid(tank);
}