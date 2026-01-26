// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "TankController.generated.h"

/**
 * 坦克1输入委托
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTank1MoveInputDelegate, const int32,const FInputActionValue&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTank1FireInputDelegate, const int32,const FInputActionValue&);

/**
 * 坦克2输入委托
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTank2MoveInputDelegate, const int32 ,const FInputActionValue& );
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTank2FireInputDelegate, const int32 ,const FInputActionValue& );



/**
 * fryrd
 */
UCLASS()
class BATTLETANK_API ATankController : public APlayerController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;
	
	virtual void OnPossess(APawn* InPawn) override;
	
public:

	//坦克1输入委托
	FOnTank1MoveInputDelegate OnTank1MoveInputDelegate;
	FOnTank1FireInputDelegate OnTank1FireInputDelegate;
	//坦克2输入委托
	FOnTank2MoveInputDelegate OnTank2MoveInputDelegate;
	FOnTank2FireInputDelegate OnTank2FireInputDelegate;
	
	//坦克1输入事件
	UFUNCTION()
	void OnTank1MoveInput(const FInputActionValue& Value);
	UFUNCTION()
	void OnTank1FireInput(const FInputActionValue& Value);
	
	//坦克2输入事件
	UFUNCTION()
	void OnTank2MoveInput(const FInputActionValue& Value);
	UFUNCTION()
	void OnTank2FireInput(const FInputActionValue& Value);
};
