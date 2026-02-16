#include "UI/Gameplay.h"

#include "GameStateBase/PlayerTankStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/PlayerHud.h"
#include "UI/tankui.h"

void UGameplay::NativeConstruct()
{
	Super::NativeConstruct();
	//enemycount=2;
	TankGameState = Cast<APlayerTankStateBase>(GetWorld()->GetGameState());
	TankGameState->OnbloodChanged.AddDynamic(this, &UGameplay::gaming);
	CurrentHud = Cast<APlayerHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),  Aenemypawn::StaticClass(), enemys);
	EnemyDestroyedHandle = GetWorld()->AddOnActorDestroyedHandler(
	   FOnActorDestroyed::FDelegate::CreateUObject(this, &UGameplay::OnEnemyDestroyed));
  
	//panel->AddChildToGrid(tank);
}

void UGameplay::OnEnemyDestroyed(AActor* DestroyedActor)
{ 
	 
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),  Aenemypawn::StaticClass(), enemys);
	enemycount = enemys.Num();
	num ->SetText(FText::FromString(FString::Printf(TEXT("剩余敌人：%d"), enemycount)));
	if (enemycount<=2)
	{
		CurrentHud->SwitchUI(EUIType::GameOverPage);
	}
	;
}

void UGameplay::gaming(int32 bloodToAdd)
{  
	
	 blood1->SetText(FText::FromString(FString::Printf(TEXT("坦克1血条：%d"),TankGameState->GetSessionData(0).blood)));
	 blood2->SetText(FText::FromString(FString::Printf(TEXT("坦克2血条：%d"),TankGameState->GetSessionData(1).blood)));
}
