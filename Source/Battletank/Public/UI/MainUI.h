// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "tankui.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "MainUI.generated.h"

 

 

struct FTimerHandle;



  UCLASS()	
class BATTLETANK_API UMainUI : public UUserWidget
  {
	  GENERATED_BODY()
  
private:
	TArray<FWidgetAnimationDynamicEvent> StoredAnimationDelegates;
	
	FTimerHandle TimerHandle;
	int CurrentBGIndex;
	int MaxBGIndex;
	float BGBlendInterval;
	
	//void SetBGSwitcherTimer();
	//void ClearBGSwitcherTimer();
	
	//void PlayBGBlendInAnimation();
	//void PlayBGBlendOutAnimation();
	//void StopBGBlendInAnimation();
	//void StopBGBlendOutAnimation();
	 
	virtual void NativeConstruct() override;
	//virtual void NativePreConstruct() override;
	
	 
	 //void OnGameEnterBtnClick();
	
	//void OnGameEneter();
  public:
  	 
	//UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	//UTextBlock* HintText;
	
	//UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	//UImage* BGImage;
	
	//UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel")
	//TArray<UTexture2D*> BGTextures;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	UButton* PlayerSingle;
	
	UPROPERTY(Transient,EditDefaultsOnly,blueprintReadWrite,Category = "GameEnterPanel|Animations",meta = (BindWidgetAnim))
	UWidgetAnimation* MainImage_1;
	
	 
	
	//UGameEntryPanelWidget(const FObjectInitializer& ObjectInitializer)
	 
	
	 
	//void ChangeBGTextures();
	//virtual bool Initialize() override;
	//virtual void PanelInitialize() ;
	
	//virtual void EnterPanel()  ;
	//virtual void LeavePanel() ;
	
	//UI Input Event
//	virtual void OnConfirmInputPressed() ;
//	virtual void OnGoBackInputPressed(bool& bHandled)  ;
	  UFUNCTION()
	 void OnGameEnterButtonClicked();
	
protected:
	//virtual void TickNative(const FGeometry& MyGeometry, float InDeltaTime) ;
	
	//virtual void OnEnterPanel()  ;
	//virtual void OnLeavePanel() ;
	
	//virtual void RemoveFromParent() override;
	
	//virtual void NativeDestruct() override;
	
};
