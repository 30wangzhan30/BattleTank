// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/PlayerTank.h"
#include "enemypawn.generated.h"

UCLASS()
class BATTLETANK_API Aenemypawn : public APlayerTank
{
	GENERATED_BODY()

	 
	 
	 
	

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:	
		// Called every frame
		virtual void Tick(float DeltaTime) override;
	    Aenemypawn();
		UPROPERTY()
		class Achildtank* NextBody;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UPaperFlipbookComponent* FlipbookComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UPaperFlipbook* Sprites;
		void SetSpawnNextBody( );
	void BodyMove(float Deltatime);
		void  SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
	};
 
