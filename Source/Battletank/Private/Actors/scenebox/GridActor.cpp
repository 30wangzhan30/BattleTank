// Fill out your copyright notice in the Description page of Project Settings.


 
#include "Actors/scenebox/GridActor.h"

#include "PaperFlipbookComponent.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Actors/TankBullet.h"
#include "Components/BoxComponent.h"
#include "Pawn/PlayerTank.h"


// Sets default values
AGridActor::AGridActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	 
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	GridRenderer = CreateDefaultSubobject<UPaperSpriteComponent>("GridRenderer");
	
	GridRenderer->SetupAttachment(RootComponent);
	GridRenderer->SetCollisionProfileName("OverlapAll");
	//GridRenderer -> SetRelativeRotation(FRotator(0.0f,90.0f,0.0f));
	SetActorRotation(FRotator(0.0f,90.0f,0.0f));
	
}

// Called when the game starts or when spawned
void AGridActor::BeginPlay()
{
	Super::BeginPlay();
	for (int32 i = 0; i < BrickGridRenders.Num(); i++)
	{
		if (IsValid(BrickGridComponent[i]))
		{
			BrickGridComponent[i]->OnComponentHit.AddDynamic(this, &AGridActor::OnBrickHit);
			BrickGridComponent[i]->OnComponentBeginOverlap.AddDynamic(this, &AGridActor::OnBrickOverlap);
			BrickGridComponent[i]->OnComponentHit.AddDynamic(this, &AGridActor::OnBrickHit);
			BrickGridRenders[i]->OnComponentBeginOverlap.AddDynamic(this, &AGridActor::OnBrickOverlap);
		}
	}
	for (int32 i = 0; i < SteelGridRenders.Num(); i++)
	{
		if (IsValid(SteelGridRenders[i]))
		{
			 
			SteelGridRenders[i]->OnComponentHit.AddDynamic(this, &AGridActor::OnBrickHit);
			SteelGridRenders[i]->OnComponentBeginOverlap.AddDynamic(this, &AGridActor::OnBrickOverlap);
			BrickGridComponent[i]->OnComponentBeginOverlap.AddDynamic(this, &AGridActor::OnBrickOverlap);
			BrickGridComponent[i]->OnComponentHit.AddDynamic(this, &AGridActor::OnBrickHit);
		}
	}
	if (GridTrigger)
	{
		GridTrigger->OnComponentBeginOverlap.AddDynamic(this, &AGridActor::OnGrassOverlap);
	
	GridTrigger->OnComponentEndOverlap.AddDynamic(this, &AGridActor::OnGrassOverOverlap);
	}
}
 
void AGridActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	GridInit(CurrentGridType);
}

// Called every frame
void AGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
 
}

void AGridActor::GridInit(EGridType GridType)
{
	CurrentGridType = GridType;
	
	ClearBrickGrids();
	ClearSteelGrids();
	RemoveGridTrigger();
	RemoveGridCollision();
	RemoveBrickGridCollision();
	GridRenderer -> SetSprite(nullptr);

	switch (CurrentGridType) {
	case EGridType::Empty:
		GridRenderer -> SetSprite(EmptyGrid);
		break;
	case EGridType::Brick:
		{
			AddBrickGrids();
			 
		}
		break;
	case EGridType::Steel:
		{
			AddSteelGrids();
		}
		break;
	case EGridType::River:
		{
			GridRenderer -> SetSprite(RiverGrid);
			AddTrigger();
		}
		break;
	case EGridType::Forest:
		{
			GridRenderer -> SetSprite(ForestGrid);
			AddTrigger();
		}
		break;
	case EGridType::Ice:
		{
			GridRenderer -> SetSprite(IceGrid);
			AddTrigger();
		}
		break;
	case EGridType::Home:
		GridRenderer -> SetSprite(HomeGrid);
		break;
	case EGridType::PlayerStart:
		GridRenderer -> SetSprite(PlayerStartGrid);
		break;
	case EGridType::Boundary:
		GridRenderer -> SetSprite(BoundaryGrid);
		break;
	}
}
//河流碰撞
void AGridActor::AddGridCollision()
{
	RemoveGridCollision();
	RemoveBrickGridCollision();
	GridCollision = NewObject<UBoxComponent>(this,"GridCollision");
	FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative,true);
	GridCollision->AttachToComponent(GridRenderer,Rules);
	GridCollision -> RegisterComponentWithWorld(GetWorld());
	FVector Extent{0.0f,10.0f,0.0f};
	Extent.X = GridRenderer -> GetSprite() ? GridRenderer -> GetSprite() ->GetSourceSize().X / 2.0f : 32.f;
	Extent.Z = GridRenderer -> GetSprite() ? GridRenderer -> GetSprite()->GetSourceSize().Y / 2.0f : 32.f;
	GridCollision -> SetBoxExtent(Extent);
	GridCollision -> SetCollisionProfileName("BlockAll");
}
//砖块钢砖碰撞
void AGridActor::AddBrickGridCollision(UPaperSpriteComponent*BrickRenderer,int Index )
{ //先删除
	RemoveGridCollision();

	//逻辑有问题 
	FString CollisionName = FString::Printf(TEXT("BrickGridCollision_%d"), Index);
	UBoxComponent* BrickGridCollision = NewObject<UBoxComponent>(this, *CollisionName);
	BrickGridComponent.SetNum(16);
	BrickGridComponent[Index]=BrickGridCollision;
	if(!BrickGridComponent[Index])
	{return;}
	FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative,true);
	BrickGridComponent[Index]->AttachToComponent(BrickRenderer,Rules);
	BrickGridComponent[Index]-> RegisterComponentWithWorld(GetWorld());
	FVector Extent{0.0f,10.0f,0.0f};
	Extent.X = BrickRenderer -> GetSprite() ? BrickRenderer -> GetSprite() ->GetSourceSize().X / 2.0f : 32.f;
	Extent.Z = BrickRenderer -> GetSprite() ? BrickRenderer -> GetSprite()->GetSourceSize().Y / 2.0f : 32.f;
	BrickGridComponent[Index] -> SetBoxExtent(Extent);
	BrickGridComponent[Index]-> SetCollisionProfileName("BlockAll");
 
}
//删除普通
void AGridActor::RemoveGridCollision()
{
	if (GridCollision)
	{
		FDetachmentTransformRules Rules(EDetachmentRule::KeepRelative,true);
		GridCollision -> DetachFromComponent(Rules);
		GridCollision -> UnregisterComponent();
		GridCollision -> DestroyComponent();
		GridCollision = nullptr;
	}
}
//删除砖
void AGridActor::RemoveBrickGridCollision()
{ 
	 //逻辑有问题
	 
 
	for (UBoxComponent* CollisionComp : BrickGridComponent)
	{
		 
		if (CollisionComp)
		{
		 
		 
			FDetachmentTransformRules DetachRules(EDetachmentRule::KeepRelative, true);
			CollisionComp->DetachFromComponent(DetachRules);
	 
			CollisionComp->UnregisterComponent();
		 
		}
	}
	
	
}
 
void AGridActor::OnGridTriggered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerTank* PlayerTank = Cast<APlayerTank>(OtherActor))
	{
		switch (CurrentGridType)
		{
			case EGridType::River:
			break;
			case  EGridType::Forest:
			break;
			case EGridType::Ice:
			break;
			default:
			break;
		}
	}
	
}
//River:Forest:Ice:碰撞
void AGridActor::AddTrigger()
{
	RemoveGridTrigger();
	GridTrigger = NewObject<UBoxComponent>(this,"BrickTrigger");
	FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative,true);
	GridTrigger->AttachToComponent(GridRenderer,Rules);
	GridTrigger -> RegisterComponentWithWorld(GetWorld());
	FVector Extent{0.0f,10.0f,0.0f};
	Extent.X = GridRenderer -> GetSprite() ? GridRenderer -> GetSprite() ->GetSourceSize().X / 2.0f : 32.f;
	Extent.Z = GridRenderer -> GetSprite() ? GridRenderer -> GetSprite()->GetSourceSize().Y / 2.0f : 32.f;
	GridTrigger -> SetBoxExtent(Extent);
	GridTrigger -> SetCollisionProfileName("OverlapAll");
	GridTrigger  -> OnComponentBeginOverlap.AddDynamic(this,&AGridActor::OnGridTriggered);
}
void AGridActor::RemoveGridTrigger()
{
	if (GridTrigger)
	{
		FDetachmentTransformRules Rules(EDetachmentRule::KeepRelative,true);
		GridTrigger -> DetachFromComponent(Rules);
		GridTrigger -> UnregisterComponent();
		GridTrigger -> DestroyComponent();
		GridTrigger = nullptr;
	}
}
 //砖块图片
void AGridActor::AddBrickGrids()
{
	  RemoveBrickGridCollision();
	FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative,true);
 	for (int i = 0; i < 16; i++)
	{ 
		UPaperSpriteComponent*BrickRenderer = NewObject<UPaperSpriteComponent>(this);
		BrickRenderer -> AttachToComponent(GridRenderer,Rules);
		BrickRenderer -> RegisterComponentWithWorld(GetWorld());
		FVector LocationOffset{-12.f,GetActorLocation().Z,-12.f};
		LocationOffset.X += (i % 4) * 8;
		LocationOffset.Z += (i / 4) * 8; 
 		
		BrickRenderer -> SetRelativeLocation(LocationOffset);
		if (BrickGrid.Num() > i)
			BrickRenderer -> SetSprite(BrickGrid[i]);
		    BrickGridRenders.Add(BrickRenderer);
 		
 		 AddBrickGridCollision( BrickRenderer,i);
 	 
	}
}

void AGridActor::ClearBrickGrids()
{  
	if (BrickGridRenders.Num() > 0)
	{
		FDetachmentTransformRules  Rules(EDetachmentRule::KeepRelative,true);
		for (int i = 0; i < BrickGridRenders.Num(); i++)
		{
			if (!BrickGridRenders[i]) continue;
			BrickGridRenders[i] -> DetachFromComponent(Rules); 
			BrickGridRenders[i] -> UnregisterComponent();
			BrickGridRenders[i] -> DestroyComponent();
			BrickGridRenders[i] = nullptr;
		}
		//BrickGridRenders.Empty();
		BrickGridRenders.Reset();
	}
	
}
//钢砖图片
void AGridActor::AddSteelGrids()
{RemoveBrickGridCollision();
	 
	FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative,true);
	for (int i = 0; i < 16; i++)
	{
		UPaperSpriteComponent* SteelRenderer = NewObject<UPaperSpriteComponent>(this);
		SteelRenderer -> AttachToComponent(GridRenderer,Rules);
		SteelRenderer -> RegisterComponentWithWorld(GetWorld());
		FVector LocationOffset{-12.f,GetActorLocation().Z,-12.f};
		LocationOffset.X += (i % 4) * 8;
		LocationOffset.Z += (i / 4) * 8; 
		SteelRenderer -> SetRelativeLocation(LocationOffset);
		if (SteelGrid.Num() > i)
		
			SteelRenderer -> SetSprite(SteelGrid[i]);
		SteelGridRenders.Add(SteelRenderer);
		 AddBrickGridCollision( SteelRenderer,i);
	}
}

void AGridActor::ClearSteelGrids()
{
	if (SteelGridRenders.Num() > 0)
	{
		FDetachmentTransformRules  Rules(EDetachmentRule::KeepRelative,true);
		for (int i = 0; i < SteelGridRenders.Num(); i++)
		{
			if (!SteelGridRenders[i]) continue;
			SteelGridRenders[i] -> DetachFromComponent(Rules);
			SteelGridRenders[i] -> UnregisterComponent();
			SteelGridRenders[i] -> DestroyComponent();
			SteelGridRenders[i] = nullptr;
		}
		SteelGridRenders.Reset();
	}
}

void AGridActor:: OnBrickHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{ 	  
	HitComp->SetGenerateOverlapEvents(false);
	HitComp->DestroyComponent();
	HitComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BrickGridComponent.Remove(Cast<UBoxComponent>(HitComp));

}
 void AGridActor:: OnGrassOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
 	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerTank *istank=Cast<APlayerTank>(OtherActor);
	if (istank)
	{UE_LOG(LogTemp, Log, TEXT("已隐身 ") );
		istank->RenderTankComponent->SetVisibility(false);
	}
}
void AGridActor:: OnGrassOverOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerTank *istank=Cast<APlayerTank>(OtherActor);
	if (istank)
	{ 
		istank->RenderTankComponent->SetVisibility(true);
	}
}
void AGridActor:: OnBrickOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{ 	 	 
	ATankBullet *isbullet=Cast<ATankBullet>(OtherActor); 
	if (isbullet)
	{
	OverlappedComponent->SetGenerateOverlapEvents(false);
	OverlappedComponent->DestroyComponent();
	OverlappedComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BrickGridComponent.Remove(Cast<UBoxComponent>(OverlappedComponent));
    }
}
