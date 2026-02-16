// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/enemypawn.h"
#include "childtank2.generated.h"

UCLASS()
class BATTLETANK_API Achildtank2 : public Aenemypawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Achildtank2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	 
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
