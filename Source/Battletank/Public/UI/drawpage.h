// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map/MapEditer.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Pawn/PlayerHud.h"
#include "drawpage.generated.h"
 
/**
 * 
 */
UCLASS()
class BATTLETANK_API Udrawpage : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;
	UFUNCTION()
	void OnDraw(ETileType TileType);
	UFUNCTION()
	void DrawGrass();
	UFUNCTION()
	void DrawWater();
	UFUNCTION()
	void DrawBrick();
	UFUNCTION()
	void DrawSteelBrick();
	UFUNCTION()
	void Drawhome();
	UFUNCTION()
	void  SaveMap();
	UFUNCTION()
	void OnErase();
	UFUNCTION()
	void  ReturnTo();
	 UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
     UButton* grass;
	 UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	 UButton* brick;
	 UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	 UButton* steelbrick;
	 UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
    UButton* water;
	 UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	 UButton *home;
	 UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	 UButton *erase;
	 UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	UButton *Save;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	UButton *Clear;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "GameEnterPanel",meta = (BindWidget))
	UButton *Return;
	APlayerHud* CurrentHud;
};
