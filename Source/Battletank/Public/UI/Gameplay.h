

#pragma once

#include "CoreMinimal.h"
#include "tankui.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Pawn/enemypawn.h"
#include "Gameplay.generated.h"
class APlayerTankStateBase;
/**
 * 
 */
UCLASS()
class BATTLETANK_API UGameplay : public UUserWidget
{
	GENERATED_BODY()
public :
	virtual void NativeConstruct() override;
	UFUNCTION()
	 void gaming(int32 bloodToAdd);
	APlayerTankStateBase *TankGameState;
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
	UTextBlock* num ;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	UTextBlock* blood;
};
