// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
 
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera2DActor.generated.h"

UCLASS()
class BATTLETANK_API ACamera2DActor : public AActor
{
	GENERATED_BODY()
public:
	ACamera2DActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// 2D摄像机核心组件
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraSpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Main2DCamera;

	//  跟踪玩家（让摄像机跟随玩家，但不绑定）
	UPROPERTY(EditAnywhere, Category = "Camera")
	APawn* TargetPawn;

	// 摄像机跟随速度
	UPROPERTY(EditAnywhere, Category = "Camera")
	float FollowSpeed = 5.0f;
};
