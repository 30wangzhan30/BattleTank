// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PlayerTankStateBase.generated.h"

enum EGameState
{
	GameUI,Game,GameOver
	
};

UCLASS()
class BATTLETANK_API APlayerTankStateBase : public AGameStateBase
{
	GENERATED_BODY()
	public:
	int32 Gamestore;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	APlayerTankStateBase ();
	
	void addscore();
	void resetscore();
	int getgamescore() const{return Gamestore;};
	
	
	 
    float GameSpeed; 
    
    EGameState CurrentGameState;
    void ChangeBirdState(EGameState NewState);
     
};
