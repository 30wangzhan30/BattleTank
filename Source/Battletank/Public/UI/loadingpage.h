

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "Pawn/PlayerHud.h"

#include "loadingpage.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API Uloadingpage : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void OnAnimationFinishedPlaying();
	UPROPERTY (BlueprintReadWrite, Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* animation  ;
	FTimerHandle MyTimerHandle;
	APlayerHud* CurrentHud;
};
