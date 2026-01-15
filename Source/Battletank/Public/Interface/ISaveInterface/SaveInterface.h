// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SaveInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USaveInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BATTLETANK_API ISaveInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	// 保存游戏状态
	virtual void OnSave(FJsonObject& OutJson) = 0;
	// 加载游戏状态
	virtual void OnLoad(const FJsonObject& InJson) = 0;
};
