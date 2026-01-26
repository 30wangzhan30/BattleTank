#include "UI/loadingpage.h"

#include "Pawn/PlayerHud.h"


void Uloadingpage::NativeConstruct()
{
	Super::NativeConstruct();
	PlayAnimation(animation);
	CurrentHud = Cast<APlayerHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
	
	 
	GetWorld()->GetTimerManager().SetTimer(
		MyTimerHandle,            
		this,                      
		&Uloadingpage::OnAnimationFinishedPlaying,   
		3.0f,                       // 延迟3秒
		false                       // 只执行一次
	);
};
 
void Uloadingpage::OnAnimationFinishedPlaying()
{
	 
	CurrentHud->SwitchUI(EUIType::GamePlayUI);

	 
}