// Fill out your copyright notice in the Description page of Project Settings.


#include "FrameWork/TankController.h"

//#include "InputCoreTypes.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void ATankController::BeginPlay()
{
	Super::BeginPlay();
	UInputMappingContext* MappingContext = LoadObject<UInputMappingContext>(this,TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Blueprints/Inputs/IMC_Tank.IMC_Tank'"));
	
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if (EnhancedInputSubsystem)
	{
		EnhancedInputSubsystem -> ClearAllMappings();
		EnhancedInputSubsystem -> AddMappingContext(MappingContext,0);
	}
	
	UInputAction* MoveActionTank1 = LoadObject<UInputAction>(this,TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Inputs/Actions/IA_Move_Tank1.IA_Move_Tank1'"));
	UInputAction* FireActionTank1 = LoadObject<UInputAction>(this,TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Inputs/Actions/IA_Fire_Tank1.IA_Fire_Tank1'"));

	
	UInputAction* MoveActionTank2 = LoadObject<UInputAction>(this,TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Inputs/Actions/IA_Move_Tank2.IA_Move_Tank2'"));
	UInputAction* FireActionTank2 = LoadObject<UInputAction>(this,TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Inputs/Actions/IA_Fire_Tank2.IA_Fire_Tank2'"));
	
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveActionTank1,ETriggerEvent::Triggered,this,&ATankController::OnTank1MoveInput);
		EnhancedInputComponent->BindAction(FireActionTank1,ETriggerEvent::Started,this,&ATankController::OnTank1FireInput);
		
		EnhancedInputComponent->BindAction(MoveActionTank2,ETriggerEvent::Triggered,this,&ATankController::OnTank2MoveInput);
		EnhancedInputComponent->BindAction(FireActionTank2,ETriggerEvent::Started,this,&ATankController::OnTank2FireInput);
	}
}

void ATankController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
}

void ATankController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
}

void ATankController::OnTank1MoveInput(const FInputActionValue& Value)
{
	
	if (OnTank1MoveInputDelegate.IsBound())
	{
		OnTank1MoveInputDelegate.Broadcast(0,Value);
	}
}

void ATankController::OnTank1FireInput(const FInputActionValue& Value)
{
	
	if (OnTank1FireInputDelegate.IsBound())
	{
		OnTank1FireInputDelegate.Broadcast(0,Value);
	}
}

void ATankController::OnTank2MoveInput(const FInputActionValue& Value)
{
	
	if (OnTank2MoveInputDelegate.IsBound())
	{
		OnTank2MoveInputDelegate.Broadcast(1,Value);
	}
}

void ATankController::OnTank2FireInput(const FInputActionValue& Value)
{
	
	if (OnTank2FireInputDelegate.IsBound())
	{
		OnTank2FireInputDelegate.Broadcast(1,Value);
	}
}
