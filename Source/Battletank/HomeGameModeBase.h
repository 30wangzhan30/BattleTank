// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HomeGameModeBase.generated.h"



 
UCLASS()
class BATTLETANK_API AHomeGameModeBase : public AGameModeBase
{private:
	UPROPERTY( )
	int32 MaxBulletCount = 7;  
	UPROPERTY()
	 TArray<class ATankBullet*> BulletObjectPool; // 子弹对象池

public:
	virtual void BeginPlay() override;
	GENERATED_BODY()
	
public:
	
	AHomeGameModeBase();
	
	 
	void Addinitilize();
	void AddBulletActor(ATankBullet* BulletActor);
	ATankBullet* GetBulletObject();
};
