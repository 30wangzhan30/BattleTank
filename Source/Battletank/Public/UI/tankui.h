// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "tankui.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API Utankui : public UUserWidget
{
	GENERATED_BODY()
public:
	 
	virtual void NativeConstruct () override;
	virtual void NativeTick (const FGeometry& MyGeometry, float InDeltaTime) override;
	APlayerController* PC;  
	UPROPERTY
	(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	 UImage* BGImage;
};
