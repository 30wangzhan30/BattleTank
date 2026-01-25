// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Pawn/PlayerHud.h"
#include "levelevent.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API Ulevelevent : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void OnRewriteButtonClicked();
	UFUNCTION()
	void OnEnterButtonClicked();
	UFUNCTION()
	void OnlookButtonClicked();
	UFUNCTION()
	void OndeletedButtonClicked();
	virtual void NativeConstruct() override;
	UPROPERTY()
	APlayerHud* CurrentHud;
	 
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	UButton* enter;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	UButton* rewrite;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	UButton* look;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	UButton* deleted;
};
