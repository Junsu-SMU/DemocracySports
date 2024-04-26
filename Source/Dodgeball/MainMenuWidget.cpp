// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "DodgeballPlayerController.h"

void UMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (PlayButton != nullptr)
	{
		PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPlayClicked);
	}

	if (StoreButton != nullptr)
	{
		StoreButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStoreClicked);
	}

	if (RankButton != nullptr)
	{
		RankButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnRankClicked);
	}

	if (ExitButton != nullptr)
	{
		ExitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitClicked);
	}
}

void UMainMenuWidget::OnPlayClicked()
{
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HideMainMenuWidget();
		PlayerController->ShowStageWidget();
	}
}

void UMainMenuWidget::OnStoreClicked()
{
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HideMainMenuWidget();
		PlayerController->ShowStore1Widget();
	}
}

void UMainMenuWidget::OnRankClicked()
{
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HideMainMenuWidget();
		PlayerController->ShowRankWidget();
	}
}

void UMainMenuWidget::OnExitClicked()
{
	UKismetSystemLibrary::QuitGame(this,
		nullptr,
		EQuitPreference::Quit,
		true);
}
