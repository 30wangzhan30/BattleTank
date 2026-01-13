// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HomeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API AHomeGameModeBase : public AGameModeBase
{
public:
	GENERATED_BODY()
	
public:
	
	AHomeGameModeBase();
	virtual void BeginPlay() override;
};
