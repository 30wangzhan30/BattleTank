// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/PlayerTank.h"

#include <ThirdParty/ShaderConductor/ShaderConductor/External/DirectXShaderCompiler/include/dxc/DXIL/DxilConstants.h>

#include "PaperFlipbookComponent.h"
 
#include "PaperFlipbook.h"
#include "InputActionValue.h"
#include "Actors/TankBullet.h"
#include "TimerManager.h" 
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "FrameWork/TankController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameStateBase/PlayerTankStateBase.h"
#include "Physics/ImmediatePhysics/ImmediatePhysicsShared/ImmediatePhysicsCore.h"
 
// Sets default values
APlayerTank::APlayerTank()
{
	 
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UCapsuleComponent* RootCapsule  = Cast<UCapsuleComponent>(GetRootComponent());
	if (IsValid(RootComponent))
	{
		RootCapsule ->SetCapsuleRadius (15.0f);
		RootCapsule->SetCapsuleHalfHeight (15.0f);
	//	RootCapsule->SetSimulatePhysics(true);
	}
	//RootComponent= CreateDefaultSubobject<USceneComponent >(TEXT("root"));
	RenderTankComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("RenderFlipbookComponent"));
	RenderTankComponent->SetupAttachment(RootComponent);
	RenderTankComponent->SetCollisionProfileName(TEXT("BlockAll"));
	
	 
 
    //BoxComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	// 创建浮动物体移动组件
	TankMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("TankMovement"));
	//TankMovementComponent -> UpdatedComponent = RootComponent;
	
	TankMovementComponent -> bConstrainToPlane = true;
	TankMovementComponent -> SetPlaneConstraintNormal(FVector(0.0f, 0.0f, 1.0f));
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	//设置速度
	RotationSpeed = 5.0f;
	MoveSpeed = 500.f;
	TankMovementComponent -> MaxSpeed = MoveSpeed;
	
	//玩家2 移动速度设置
	MaxVelocity = TankMovementComponent -> GetMaxSpeed();
	Acceleration = TankMovementComponent -> Acceleration;
	Deceleration = TankMovementComponent -> Deceleration;
}

void APlayerTank::InitializeTankController(ATankController* TankController)
{
	if (IsValid(TankController))
	{
		if (PlayerIndex == 0)
		{
			TankController ->OnTank1MoveInputDelegate.AddUFunction(this,FName("MoveInputHandler"));
			TankController ->OnTank1FireInputDelegate.AddUFunction(this,FName("FireInputHandler"));
		}
		else if (PlayerIndex == 1)
		{
			TankController ->OnTank2MoveInputDelegate.AddUFunction(this,FName("MoveInputHandler"));
			TankController ->OnTank2FireInputDelegate.AddUFunction(this,FName("FireInputHandler"));
		}
	}
}

FGameSessionData APlayerTank::GetTankSessionDataByID( )
{ 
	//TankGameState = Cast<APlayerTankStateBase>(GetWorld()->GetGameState());
	 //return TankGameState->GetSessionData();
	return GetTankSessionData();
}

// Called when the game starts or when spawned
void APlayerTank::BeginPlay()
{ 
	Super::BeginPlay();
	//UpdateTankGridLocation();
	 TankGameState = Cast<APlayerTankStateBase>(GetWorld()->GetGameState());
	TankFlipbook=LoadObject<UPaperFlipbook>(  this , TEXT("/Script/Paper2D.PaperFlipbook'/Game/PlayerControler/TankSprite/Player3.Player3'"));
 
	if (RenderTankComponent && TankFlipbook)
	{
		RenderTankComponent->SetFlipbook(TankFlipbook);
		RenderTankComponent->SetRelativeRotation(FRotator(0.0f, 90.f, 90.0f));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("TANk绑定失败！"));
	}
	
}
// void APlayerTank::BindTankState(APlayerTankStateBase* InTankState)
// {
// 	if (InTankState)
// 	{
// 		TankGameState = InTankState;
// 		UE_LOG(LogTemp, Log, TEXT("坦克%d绑定State成功！"), TankID);
// 	}
// 	else
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("坦克%d绑定State失败：State为空！"), TankID);
// 	}
// }
void APlayerTank::OnKillEnemy()
{
	 TankGameState = Cast<APlayerTankStateBase>(GetWorld()->GetGameState());
	if (TankGameState)
	{
		 
		TankGameState->AddKillCount(1);
	}
}
// Called every frame
void APlayerTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
 
	//玩家2的移动处理
 	if (PlayerIndex == 1)
	{
		FVector PendingMovementInputVector = GetPendingMovementInputVector();
		PendingMovementInputVector = PendingMovementInputVector.GetSafeNormal();
		if (!PendingMovementInputVector.IsNearlyZero())
		{
			CurrentVelocity += PendingMovementInputVector * DeltaTime * Acceleration;
		}
		else
		{
			CurrentVelocity = FMath::VInterpTo(CurrentVelocity,FVector::ZeroVector,DeltaTime,Deceleration);
		}
		
		CurrentVelocity = CurrentVelocity.GetClampedToMaxSize(MaxVelocity);
		 

		AddActorWorldOffset(CurrentVelocity * DeltaTime,true);
 
		ConsumeMovementInputVector();
	}
}

// Called to bind functionality to input
void APlayerTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	 
	    
	 
	
	// 绑定操作映射到函数 (玩家坦克写在子类里)
	// PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &APlayerTank::OnMoveRightPressed);
	// PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &APlayerTank::OnMoveLeftPressed);
	// PlayerInputComponent->BindAction("MoveUp", IE_Pressed, this, &APlayerTank::OnMoveUpPressed);
	// PlayerInputComponent->BindAction("MoveDown", IE_Pressed, this, &APlayerTank::OnMoveDownPressed);
	 
}

void APlayerTank::MoveInputHandler(const int32 InPlayerIndex, const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();
	float Angle = FMath::Atan2(InputVector.X, InputVector.Y) * (180.0f / PI);
	FRotator TargetRotation = FRotator(0.0f, Angle, 0.0f);
	if (TargetRotation.Yaw < 0)
		TargetRotation.Yaw += 360.0f;
	FRotator Rotation = RenderTankComponent -> GetRelativeRotation();
	if (Rotation.Yaw < 0)
		Rotation.Yaw += 360.0f;
	if (!FMath::IsNearlyEqual(TargetRotation.Yaw,Rotation.Yaw))
	{
		if (abs(TargetRotation.Yaw - Rotation.Yaw) <= RotationSpeed)
			RenderTankComponent -> SetRelativeRotation(FRotator(0.0f, TargetRotation.Yaw, 90.0f));
		else
		{
			int64 RotationDelta = (TargetRotation.Yaw - Rotation.Yaw) > 0.0f  ? 1.0f * RotationSpeed : -1.0f * RotationSpeed;
			//if(abs(TargetRotation.Yaw - Rotation.Yaw) > abs((360.f - TargetRotation.Yaw) - Rotation.Yaw))  RotationDelta *= -1.0f;
			if (abs(TargetRotation.Yaw - Rotation.Yaw) > 180.0f) 
				RotationDelta *= -1.0f;
			RenderTankComponent -> AddRelativeRotation(FRotator(0.0f, RotationDelta, 0.0f));
		}
		
	}
	else
	{
		//AddMovementInput(FVector(InputVector.Y, InputVector.X, 0.0f));
		//TankMovementComponent -> AddInputVector(FVector(InputVector.X, InputVector.Y, 0.0f));
		FVector MovementDirection=FVector(InputVector.Y, InputVector.X, 0.0f);
		//TankMovementComponent->Velocity =MovementDirection*500;
		if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
		{
			MoveComp->Velocity =MovementDirection*5 ;
			AddActorWorldOffset(MovementDirection*5,true );
			UE_LOG(LogTemp, Error, TEXT("%s"),*InputVector.ToString());
		}
	 
		 
	}
	
	 
	 
	
}

void APlayerTank::FireInputHandler(const int32 InPlayerIndex, const FInputActionValue& Value)
{
	if (CanFire())
	{
		Onshoot();
		 
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
 
}

 
//想要实现计算瓦片地图每个格子的位置然后SetRelativeLocation到将要移动到的位置
void APlayerTank::OnMoveRightPressed( )
{
	// 向右移动1格
	CurrentGridX += 1;
	//更新朝向
	CurrentDirection = ETankDirection::Right; 
	UpdateTankRotation();
	// 更新实际位置
	UpdateTankGridLocation();  

}

void APlayerTank::OnMoveLeftPressed()
{ 
	
	CurrentGridX -= 1;
	//更新朝向
	CurrentDirection = ETankDirection::Left; 
	UpdateTankRotation();
	// 更新实际位置
	UpdateTankGridLocation();
}

void APlayerTank::OnMoveUpPressed( )
{
	CurrentGridY -= 1;
	//更新朝向
	CurrentDirection = ETankDirection::Up; 
	UpdateTankRotation();
	// 更新实际位置
	UpdateTankGridLocation();
}
void APlayerTank::OnMoveDownPressed( )
{
	CurrentGridY += 1;
	//更新朝向
	CurrentDirection = ETankDirection::Down; 
	UpdateTankRotation();
	// 更新实际位置
	UpdateTankGridLocation();
}

void APlayerTank::Onshoot()
{
	 
	//ATankBullet* Bullet=GetWorld()->SpawnActor<ATankBullet>(this->GetActorLocation(),this->GetActorRotation());
	UClass* BulletClass = LoadClass<ATankBullet>(this, TEXT("/Script/Engine.Blueprint'/Game/BulletClass/MyTankBullet.MyTankBullet_C'"));
	 
	 ATankBullet* BulletActor = GetWorld()->SpawnActor<ATankBullet>(BulletClass, this->GetActorLocation()+FVector( 0,0 ,5),FRotator::ZeroRotator);//要隐藏
     	BulletActor->SetBulletMoveDirection(RenderTankComponent->GetForwardVector());
	if (BulletActor)
	{
		BulletActor->BindShooterTank(this);
		UE_LOG(LogTemp, Log, TEXT("坦克[%s]发射子弹！"), *GetName());
	}
	
}
bool APlayerTank::CanFire() const
{
	 
	if (!GetWorld())
	{
		return false;
	}

	 
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	 
	return (CurrentTime - LastFireTime) >= FireCooldownTime;
}

void APlayerTank::PressedFunction()
{
}

void APlayerTank::ReleasedFunction()
{
}

void APlayerTank::UpdateTankGridStartLocation()
{
}

void APlayerTank::UpdateTankGridLocation()
{
	FVector TargetPos = MapStartPos;//初始位置
	// 左右移动  
	TargetPos.Y += CurrentGridX * GridStep;
	// 上下移动  
	TargetPos.X -= CurrentGridY * GridStep;

	// 瞬移到目标格子
  SetActorLocation(TargetPos);
}

void APlayerTank::SpawnBulletActor()
{
}

 
void APlayerTank::ApplyAddBloodEffect( )
{TankGameState->AddBlood(this->GetPlayerIndex(),1);
	 
}

void APlayerTank::ApplyCantBeAttackedEffect( )
{ TankGameState->cantbeattack(this->GetPlayerIndex());
	              // 不循环（只执行一次）
 
	TankFlipbook=LoadObject<UPaperFlipbook>(  this , TEXT("/Script/Paper2D.PaperFlipbook'/Game/SceneSprite/Shield1.Shield1'"));
	
}

void APlayerTank::ApplyClearAllEffect()
{
}

void APlayerTank::ApplyProtectHomeEffect()
{
}

void APlayerTank::ApplyAddAttackSpeedEffect()
{TankGameState->AddATKSpeed(this->GetPlayerIndex(),1); 
	FireCooldownTime=  FireCooldownTime/TankGameState->GetSessionData(this->GetPlayerIndex()).atkspeed;
	GetWorld()->GetTimerManager().SetTimer(
		ResetTimerHandle,          
		this,                       
		&APlayerTank::ResetCooldownToZero, 
		5.0f,                        
		false                        
	);
}

void APlayerTank::ApplyAddAtkEffect()
{TankGameState->AddATK(this->GetPlayerIndex(),5); 
}

void APlayerTank::ApplyTimerEffect()
{
}


// 核心：根据朝向更新旋转角度
void  APlayerTank::UpdateTankRotation()
{
	FRotator NewRotation = FRotator::ZeroRotator;
    
	// UE中Yaw（偏航角）：0°=朝右，90°=朝上（前），180°=朝左，270°=朝下（后）
	switch (CurrentDirection)
	{
	case ETankDirection::Left:
		NewRotation.Yaw = 180.0f; // 初始朝向：左
		break;
	case ETankDirection::Right:
		NewRotation.Yaw = 0.0f;    // 朝右
		break;
	case ETankDirection::Up:
		NewRotation.Yaw =  270.0f;   // 朝上（前）
		break;
	case ETankDirection::Down:
		NewRotation.Yaw =90.0f;  // 朝下（后）
		break;
	}

	// 设置坦克旋转（平滑旋转可选，直接设置更适配格子移动）
	SetActorRotation(NewRotation);
}

void APlayerTank::ResetCooldownToZero()
{TankGameState->ResetSessionData(this->GetPlayerIndex());
}


//子弹逻辑