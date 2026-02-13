

#pragma once

#include "CoreMinimal.h"
#include "tankui.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Pawn/enemypawn.h"
#include "Gameplay.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UGameplay : public UUserWidget
{
	GENERATED_BODY()
public :
	virtual void NativeConstruct() override;
	FDelegateHandle EnemyDestroyedHandle;
	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedActor);
	UFUNCTION()
	 void gaming(int32 bloodToAdd);
	APlayerTankStateBase *TankGameState;
	APlayerHud* CurrentHud;
	UPROPERTY(EditAnywhere, Category="enemycount")
	int enemycount;
	UPROPERTY(EditAnywhere, Category="enemycount")
	TArray<AActor*> enemys;
	//UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	// UGridPanel* panel;
	//UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	//UImage* image;
	//UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	//UWidget* tank;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	UTextBlock* num  ;
	 
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	UTextBlock* blood1;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	UTextBlock* blood2;
};
