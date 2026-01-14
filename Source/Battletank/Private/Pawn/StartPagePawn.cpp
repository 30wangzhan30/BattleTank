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
	 	TargetWidgetClass =WidgetFinder.Class;
	TankWidgetComponent =  CreateWidget<UMainUI>(GetWorld(), TargetWidgetClass);;

	 
	 
		 
	 
 
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
 