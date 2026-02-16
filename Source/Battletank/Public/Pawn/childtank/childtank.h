// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/enemypawn.h"
 
#include "childtank.generated.h"

UCLASS()
class BATTLETANK_API Achildtank1 : public Aenemypawn
{
	GENERATED_BODY()
 
public:
    Achildtank1();
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	 

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
