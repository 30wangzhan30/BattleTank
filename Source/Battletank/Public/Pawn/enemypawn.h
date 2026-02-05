// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/PlayerTank.h"
#include "PaperCharacter.h"
#include "Components/BoxComponent.h"
#include "enemypawn.generated.h"

UCLASS()
class BATTLETANK_API Aenemypawn : public APaperCharacter
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
	UCapsuleComponent* RootCapsule;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent*box;
	 
	void SetSpawnNextBody( );
	void BodyMove(float Deltatime);
	UFUNCTION()
	void OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	};
 
