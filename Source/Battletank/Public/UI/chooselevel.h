

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "chooselevel.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API Uchooselevel : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	 

	//  绑定父Widget中的垂直框 
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VB_MainContainer;
};
