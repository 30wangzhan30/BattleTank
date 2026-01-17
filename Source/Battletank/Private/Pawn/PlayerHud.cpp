// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PlayerHud.h"

 
#include "UObject/ConstructorHelpers.h"
#include "Components/WidgetComponent.h"
 
#include "UI/MainUI.h"
 
// Sets default values
APlayerHud::APlayerHud()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	 
	
}

// Called when the game starts or when spawned
void APlayerHud::BeginPlay()
{
	Super::BeginPlay();
	CreateWidgetInstance();
	if (TankWidgetComponent)
	{     
			 TankWidgetComponent->AddToViewport();
	}

}

// Called every frame
void APlayerHud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerHud::CreateWidgetInstance()
{//static ConstructorHelpers::FClassFinder<UMainUI> WidgetFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/StartPawn/StartPage.StartPage_C'"));
	 TargetWidgetClass= LoadClass<UMainUI>(this, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/StartPawn/StartPage.StartPage_C'")); 
	//TargetWidgetClass =WidgetFinder.Class;
	TankWidgetComponent =  CreateWidget<UMainUI>(GetOwningPlayerController(),TargetWidgetClass);
}
 