// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/scenebox/EffectObject.h"


// Sets default values
AEffectObject::AEffectObject()
{
	 
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	EffectRenderer = CreateDefaultSubobject<UPaperSpriteComponent>("EffectRenderer");
	EffectRenderer ->SetupAttachment(RootComponent);
	SetActorRotation(FRotator(0.0f,90.0f,0.0f));
}

// Called when the game starts or when spawned
void AEffectObject::BeginPlay()
{
	Super::BeginPlay();
	 
 
}
void AEffectObject::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	EffectInit(CurrentEffectType);
	 
}
void AEffectObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

 

void AEffectObject::EffectInit(EEffectType  EffectType)
{
 CurrentEffectType = EffectType;
	
	 

	switch (CurrentEffectType) {
	case EEffectType::addoneBlood:
		EffectRenderer -> SetSprite(addoneBloodeffect );
		AddTrigger();
		break;
	case EEffectType::cantbeattacked:
		{EffectRenderer -> SetSprite(cantbeattackedeffect);
			AddTrigger();
		}
		break;
	case EEffectType ::clearall:
		{
			EffectRenderer -> SetSprite( clearalleffect);
			AddTrigger();
		}
		break;
	case EEffectType::protecthome:
		{
			EffectRenderer -> SetSprite( protecthomeeffect);
			AddTrigger();
		}
		break;
	case EEffectType::addattackspeed:
		{
			EffectRenderer -> SetSprite( addattackspeedeffect);	 
			AddTrigger();
		}
		break;
	case EEffectType::addatk:
		{
			EffectRenderer -> SetSprite( addatkeffect);
			AddTrigger();
		}
		break;
	case EEffectType::timer:
		{
			EffectRenderer -> SetSprite(timereffect);
			AddTrigger();
		}
		break;
	}
	 
 
}
 
// 碰撞
void AEffectObject::AddTrigger()
{
	 
//	GridTrigger = CreateDefaultSubobject<UBoxComponent>(" Trigger");
	EffectTrigger = NewObject<UBoxComponent>(this
		," Trigger");
	FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative,true);
	EffectTrigger->AttachToComponent(EffectRenderer,Rules);
	EffectTrigger -> RegisterComponentWithWorld(GetWorld());
	
	FVector Extent{10.0f,10.0f,10.0f};
	EffectTrigger -> SetBoxExtent(Extent);
	EffectTrigger -> SetCollisionProfileName("OverlapAll");
   EffectTrigger -> OnComponentBeginOverlap.AddDynamic(this,&AEffectObject::ObjectOverlap);
}
void AEffectObject::ObjectOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{    bool bEffectExecuted=false;
	if (bEffectExecuted)
	{
		return;
	}

	// 标记为已执行（后续重叠不再触发）
	bEffectExecuted = true;
 OverlappedComponent->DestroyComponent() ;
	 UE_LOG(LogTemp, Log, TEXT("destroy"));
	 EffectRenderer->SetVisibility(false);
	APlayerTank* Tank = Cast<APlayerTank>(OtherActor);
	// 3. 根据特效类型执行对应功能（核心分发）
	switch (CurrentEffectType)
	{
	case EEffectType::addoneBlood:
		ApplyAddBloodEffect(Tank);
		break;
	case EEffectType::cantbeattacked:
		ApplyCantBeAttackedEffect(Tank);
		break;
	case EEffectType::clearall:
		ApplyClearAllEffect();
		break;
	case EEffectType::protecthome:
		ApplyProtectHomeEffect();
		break;
	case EEffectType::addattackspeed:
		ApplyAddAttackSpeedEffect(Tank);
		break;
	case EEffectType::addatk:
		ApplyAddAtkEffect(Tank);
		break;
	case EEffectType::timer:
		ApplyTimerEffect(Tank);
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("未定义的特效类型：%d"), (int32)CurrentEffectType);
		break;
	}

}

// 1. 加血道具
void AEffectObject::ApplyAddBloodEffect(APlayerTank* PlayerTank)
{
   
    PlayerTank->ApplyAddBloodEffect( );  
	 
}

// 2. 无敌道具
void AEffectObject::ApplyCantBeAttackedEffect(APlayerTank* PlayerTank)
{
	PlayerTank->ApplyCantBeAttackedEffect( ); 
	
}

// 3. 清屏道具（销毁所有敌方坦克 )
void AEffectObject::ApplyClearAllEffect()
{
    UWorld* World = GetWorld();
    if (!World) return;

    
}

// 4. 保护基地道具
void AEffectObject::ApplyProtectHomeEffect()
{
  
}

// 5. 加攻速道具
void AEffectObject::ApplyAddAttackSpeedEffect(APlayerTank* PlayerTank)
{  
	PlayerTank->ApplyAddAttackSpeedEffect( ); 
    
}

// 6. 加攻击力道具
void AEffectObject::ApplyAddAtkEffect(APlayerTank* PlayerTank)
{
  
  
}

// 7. 暂停敌方行动 
void AEffectObject::ApplyTimerEffect(APlayerTank* PlayerTank)
{
   
    UWorld* World = GetWorld();
    if (!World) return;
 
       
    }