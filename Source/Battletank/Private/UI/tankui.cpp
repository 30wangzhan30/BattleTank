// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/tankui.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
 
 
void Utankui::NativeConstruct()
{
	Super::NativeConstruct();
		
	// 可选：设置UI位置/大小 
	this->SetRenderTranslation(FVector2D(500, 300)); // 屏幕中心位置
	this->SetRenderScale(FVector2D( 0.03,0.07)) ;
}

void Utankui::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	 
	if (!PC)
	{
		PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (!PC) return;
	}

	//  获取鼠标屏幕坐标
	FVector2D MouseScreenPos;
	if (!PC->GetMousePosition(MouseScreenPos.X, MouseScreenPos.Y))
	{
		return;
	}

	//  屏幕坐标转世界坐标 
	FVector WorldPos;
	FVector WorldDir;
	if (!PC->DeprojectScreenPositionToWorld(MouseScreenPos.X, MouseScreenPos.Y, WorldPos, WorldDir))
	{
		return;
	}
	WorldPos.Z = 0;

	// 3. 获取坦克当前位置 
	//FVector ActorPos = this->GetActorLocation();
	 
	FVector  ActorPos =  FVector(this->GetRenderTransform().Translation,0);
	//this->SetActorLocation(ActorPos); 
	 this->SetRenderTransform;
	 

	//  计算方向+转向 
	FVector DirectionToMouse = (WorldPos - ActorPos).GetSafeNormal();
	FRotator TargetRot = UKismetMathLibrary::MakeRotFromX(DirectionToMouse);
	if (DirectionToMouse.IsNearlyZero())
	{
		DirectionToMouse = FVector(100, 0, 0); //  
	}
	DirectionToMouse.Normalize();
	// 调整速度 
	float TankRotateSpeed = 3.0f;    
	float TankMoveSpeed = 100.0f;    

	// 平滑转向
	 
	 
	TargetRot.Pitch = 0.0f;
	TargetRot.Roll =  0.0f;
	 
	 
	FRotator TargetRotation = FRotator( TargetRot );
	if (TargetRotation.Yaw < 0)
		TargetRotation.Yaw += 360.0f;
	FRotator Rotation = FRotator(this->GetRenderTransform().Angle);
	if (Rotation.Yaw < 0)
		Rotation.Yaw += 360.0f;
	if (!FMath::IsNearlyEqual(TargetRotation.Yaw,Rotation.Yaw))
	{
		float ActorYaw = TargetRotation.Yaw;
		// 转成UI的2D旋转（UE UI旋转单位是度，直接传值即可）
	 
		//this -> SetActorRotation(FRotator(0.0f, TargetRotation.Yaw, 90.0f));
	
		this -> SetRenderTransformAngle(ActorYaw);
		 
		 
	}
	  

	// 计算移动增量
	FVector MoveDelta = DirectionToMouse  * TankMoveSpeed ;//* DeltaTime;
	MoveDelta.Z = 0.0f; // 
	FVector NewActorPos = ActorPos + MoveDelta;

  

		 
 //this->SetActorLocation(NewActorPos);
	 
}
 