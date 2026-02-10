// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
 
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Pawn/PlayerTank.h"
#include "EffectObject.generated.h"
UENUM()
enum class EEffectType: uint8
{
	addoneBlood = 0 UMETA(DisplayName = "血条加一"),
	cantbeattacked = 1 UMETA(DisplayName = "无敌10秒"),
	clearall = 2 UMETA(DisplayName = "消灭所有在场敌人"),
	protecthome = 3 UMETA(DisplayName = "基地无敌10秒"),
	addattackspeed = 4 UMETA(DisplayName = "攻速增加（最多叠加三次）"),
	addatk = 5 UMETA(DisplayName = "攻击增加（最多叠加三次）"),
	timer= 6 UMETA(DisplayName = "时间暂停5秒"),
};
UCLASS()
class BATTLETANK_API AEffectObject : public AActor
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

 
	


public:AEffectObject();
	
	void OnConstruction(const FTransform& Transform);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere)
	
	UPaperSpriteComponent* EffectRenderer;
	
 
	
	UPROPERTY(EditAnywhere,Category="Effect|Sprites")
	UPaperSprite*addoneBloodeffect;
	UPROPERTY(EditAnywhere,Category="Effect|Sprites")
	UPaperSprite*  cantbeattackedeffect;
	UPROPERTY(EditAnywhere,Category="Effect|Sprites")
	UPaperSprite*   clearalleffect;
	UPROPERTY(EditAnywhere,Category="Effect|Sprites")
	UPaperSprite* protecthomeeffect;
	UPROPERTY(EditAnywhere,Category="Effect|Sprites")
	UPaperSprite* addattackspeedeffect;
	UPROPERTY(EditAnywhere,Category="Effect|Sprites")
	UPaperSprite* addatkeffect;
	UPROPERTY(EditAnywhere,Category="Effect|Sprites")
	UPaperSprite* timereffect;
	UPROPERTY(EditAnywhere,Category="GridActor|GridType")
	EEffectType CurrentEffectType;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* EffectTrigger;
	void AddTrigger();
	void  EffectInit(EEffectType  EffectType);
	 
	UFUNCTION()
	void ObjectOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//UFUNCTION()
	//void OnGridTriggered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	// UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void  ApplyAddBloodEffect(APlayerTank* PlayerTank);
	void  ApplyCantBeAttackedEffect(APlayerTank* PlayerTank);
	void  ApplyClearAllEffect();
	void  ApplyProtectHomeEffect();
	void  ApplyAddAttackSpeedEffect(APlayerTank* PlayerTank);
	void  ApplyAddAtkEffect(APlayerTank* PlayerTank);
	void  ApplyTimerEffect(APlayerTank* PlayerTank);
};
