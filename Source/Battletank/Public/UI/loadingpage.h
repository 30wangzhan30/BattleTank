

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "loadingpage.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API Uloadingpage : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	UPROPERTY (BlueprintReadWrite, Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* animation  ;
};
