// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankBullet.generated.h"

UCLASS()
class BATTLETANK_API ATankBullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATankBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	
	UPROPERTY(VisibleAnywhere, Category = "Bullet|Collision")
	class USphereComponent* CollisionComp;

 

	// 子弹移动组件（控制飞行）
	UPROPERTY(VisibleAnywhere, Category = "Bullet|Movement")
	class UProjectileMovementComponent* ProjectileMovement;

	// --- 可配置参数 ---
	// 子弹速度
	UPROPERTY(EditAnywhere, Category = "Bullet|Settings", meta = (ClampMin = "100.0", ClampMax = "5000.0"))
	float BulletSpeed = 2000.0f;

	// 子弹伤害
	UPROPERTY(EditAnywhere, Category = "Bullet|Settings", meta = (ClampMin = "1", ClampMax = "100"))
	int32 Damage = 10;

	// 子弹生命周期（超时自动销毁）
	UPROPERTY(EditAnywhere, Category = "Bullet|Settings", meta = (ClampMin = "0.5", ClampMax = "10.0"))
	float LifeTime = 3.0f;

	 

private:
	// 计时：用于生命周期销毁
	float LifeTimer = 0.0f;

	// 碰撞回调函数
	//UFUNCTION()
	//void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
