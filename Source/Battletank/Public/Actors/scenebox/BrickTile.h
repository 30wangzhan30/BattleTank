// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "boxbase.h"
#include "BrickTile.generated.h"

UCLASS()
class BATTLETANK_API ABrickTile : public Aboxbase
{
	GENERATED_BODY()

 
public:
	ABrickTile();

	// 普通砖块特有：血量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick")
	int32 BrickHealth = 2;

	// 被炮弹击中
	UFUNCTION(BlueprintCallable, Category = "Brick")
	void OnHitByBullet(int32 Damage = 1);

protected:
	virtual void BeginPlay() override;
};

 
 
