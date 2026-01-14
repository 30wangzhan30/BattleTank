// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/StartPagePawn.h"

 
#include "UObject/ConstructorHelpers.h"
#include "Components/WidgetComponent.h"
 
#include "UI/MainUI.h"
 
// Sets default values
AStartPagePawn::AStartPagePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<UMainUI> WidgetFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/StartPawn/StartPage.StartPage_C'"));
	 
	TankWidgetComponent = Cast<UMainUI>(this->GetComponentByClass(UMainUI::StaticClass()));
	TargetWidgetClass =WidgetFinder.Class;
	 
	 
		 
	 
 
}

// Called when the game starts or when spawned
void AStartPagePawn::BeginPlay()
{
	Super::BeginPlay();
	TankWidgetComponent->AddToViewport();
}

// Called every frame
void AStartPagePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
 