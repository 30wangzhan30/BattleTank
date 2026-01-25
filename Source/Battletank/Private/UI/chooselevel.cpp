#include "UI/chooselevel.h"

void Uchooselevel::NativeConstruct()
{
	Super::NativeConstruct();
	
	UClass* WidgetClass = LoadClass<UUserWidget>(nullptr,  TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/StartPawn/LEVEL.LEVEL_C'"));
	 
	{
			// 创建Widget实例 
        	UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);	 
		     
		 VB_MainContainer->AddChildToVerticalBox( NewWidget);
		NewWidget->AddToViewport();
	}


}
