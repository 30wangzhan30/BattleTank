// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TankBullet.h"
 
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
  
#include "Battletank/HomeGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATankBullet::ATankBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
 // 创建根组件
	 RootComponent = CreateDefaultSubobject<USceneComponent>("DRootComponent");
	//创建渲染组件 
    	RenderBulletComponent = CreateDefaultSubobject<UPaperFlipbookComponent>("RenderBulletComponent");
    	RenderBulletComponent->SetupAttachment(RootComponent);
	
	// 创建碰撞组件b
	BulletCollision = CreateDefaultSubobject<UBoxComponent>("BulletCollision");
	BulletCollision->SetupAttachment(RootComponent);
	//BulletCollision->SetSimulatePhysics(true);
	 
	 BulletCollision->bHiddenInGame =false;//测试阶段
	
}

// Called when the game starts or when spawned
void ATankBullet::BeginPlay()
{
	Super::BeginPlay();
	 NormalBulletFlipbook = LoadObject<UPaperFlipbook>(  this,  TEXT("/Script/Paper2D.PaperFlipbook'/Game/SceneSprite/Bullet/Bullect1.Bullect1'"));
	// HitBulletFlipbook = LoadObject<UPaperFlipbook>(  this,  TEXT("/Script/Paper2D.PaperFlipbook'/Game/FlappyBird/Animations/PF_Hit_Bullet.PF_Hit_Bullet'"));//爆炸时
	 RenderBulletComponent->SetFlipbook(NormalBulletFlipbook);
	 RenderBulletComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	 
	 
	if (IsValid(BulletCollision))
	{
		BulletCollision->SetCollisionProfileName("OverlapAll"); 
		BulletCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);  
		BulletCollision->SetGenerateOverlapEvents(true);  
		BulletCollision->SetBoxExtent(FVector(1, 15, 1));  
		
		
		 BulletCollision->OnComponentHit.AddDynamic(this, &ATankBullet::OnBulletHit);
		// BulletCollision->OnComponentBeginOverlap.AddDynamic(this, &ATankBullet::OnComponentBeginOverlapEvent);
	}
		
	 HomeGameMode = Cast<AHomeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void ATankBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 每帧调用BulletMove，让子弹持续移动
	BulletMove(DeltaTime);
}

void ATankBullet::OnComponentBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{ UE_LOG(LogTemp, Log, TEXT("HIT"));
	//OverlappedComponent->DestroyComponent();
	 
	// {if (OtherActor != this)
// {
// 	// 判断是否碰撞到"Enemy"标签的Actor
// 	if (OtherActor->ActorHasTag(TEXT("Enemy")))
// 	{
// 		// 切换到碰撞后的动画（停止循环）
// 		RenderBulletComponent->SetLooping(false);
// 		BulletMoveSpeed = 0.f;
// 		RenderBulletComponent->SetFlipbook(HitBulletFlipbook);
//
// 		// 延迟销毁子弹
// 		FTimerHandle TimerHandle;
// 		GetWorldTimerManager().SetTimer(  TimerHandle, this,  &ATankBullet::BulletDestroy, 3.f);
// 	}
// }
}

void ATankBullet::OnBulletHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{ UE_LOG(LogTemp, Log, TEXT("HIT"));
     //HitComp->DestroyComponent();
	//OtherActor->Destroy ();
	HitComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
 
}


void  ATankBullet::BulletDestroy()
{
	// 重置动画状态：恢复循环播放
	//RenderBulletComponent->SetLooping(true);
	//RenderBulletComponent->Play(); // 重新播放动画
	//RenderBulletComponent->SetFlipbook(NormalBulletFlipbook); // 切回正常动画

	// 重置碰撞体半径：根据动画第一帧的尺寸调整，避免碰撞体和渲染尺寸不匹配
	//BulletCollision->SetSphereRadius(
	//	RenderBulletComponent->GetFlipbook()->GetSpriteAtFrame(0)->GetSourceSize().X / 2.f + 1.f
	//);
	if (HomeGameMode)
	{ 
		HomeGameMode->AddBulletActor(this);
	}
	 //隐藏子弹
	RenderBulletComponent->SetHiddenInGame(true);
}
void ATankBullet::SetBulletMoveDirection(FVector NewDirection)
{
	BulletMoveDirection = NewDirection;
}

 

void ATankBullet::BulletMove(float DeltaTime)
{  
	
	// 计算本次帧的移动距离（速度 × 时间）
	float MoveDistance = BulletMoveSpeed * DeltaTime;
	// 根据“移动方向”和“距离”，计算新位置
	FVector NewLocation = GetActorLocation() + (BulletMoveDirection.GetSafeNormal() * MoveDistance);
	// 更新子弹的位置
	  this->SetActorLocation(NewLocation);
	//if (IsValid(BulletCollision))
	//BulletCollision->AddForce(FVector(BulletMoveDirection.X*100,BulletMoveDirection.Y*100, 0));
	 
}
