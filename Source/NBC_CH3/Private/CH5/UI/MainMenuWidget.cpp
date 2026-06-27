#include "CH5/UI/MainMenuWidget.h"

#include "CH5/CH5_GameInstance.h"
#include "Components/Button.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton){
		StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartClicked);
	}

	if (QuitButton){
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
	}
}

void UMainMenuWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (StartButton){
		StartButton->OnClicked.RemoveDynamic(this, &UMainMenuWidget::OnStartClicked);
	}

	if (QuitButton){
		QuitButton->OnClicked.RemoveDynamic(this, &UMainMenuWidget::OnQuitClicked);
	}
}

void UMainMenuWidget::OnStartClicked()
{
	if (UCH5_GameInstance* GameInstance = GetGameInstance<UCH5_GameInstance>()){
		GameInstance->StartGame(this);
	}
}

void UMainMenuWidget::OnQuitClicked()
{
	if (UCH5_GameInstance* GameInstance = GetGameInstance<UCH5_GameInstance>()){
		GameInstance->QuitGame(this);
	}
}
