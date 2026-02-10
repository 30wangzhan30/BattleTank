#include "UI/Gameplay.h"

#include "GameStateBase/PlayerTankStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/tankui.h"

void UGameplay::NativeConstruct()
{
	Super::NativeConstruct();
	TankGameState = Cast<APlayerTankStateBase>(GetWorld()->GetGameState());
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),   Aenemypawn::StaticClass(), enemys);
	enemycount = enemys.Num();
	TankGameState->OnbloodChanged.AddDynamic(this, &UGameplay::gaming);
 num ->SetText(FText::FromString(FString::Printf(TEXT("剩余敌人：%d"), enemycount)));
	 
	//panel->AddChildToGrid(tank);
}
 
void UGameplay::gaming(int32 bloodToAdd)
{//
	blood->SetText(FText::FromString(FString::Printf(TEXT("血条：%d"),TankGameState->GetSessionData().blood)));
}
