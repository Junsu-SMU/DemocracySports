// Fill out your copyright notice in the Description page of Project Settings.


#include "RestartWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "DodgeballPlayerController.h"
#include "SpawnObject.h"
#include "MusicManager.h"
#include "EngineUtils.h"

void URestartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (RestartButton != nullptr)
	{
		RestartButton->OnClicked.AddDynamic(this, &URestartWidget::OnRestartClicked);
	}

	if (ExitButton != nullptr)
	{
		ExitButton->OnClicked.AddDynamic(this, &URestartWidget::OnExitClicked);
	}
}

void URestartWidget::OnRestartClicked()
{
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HideRestartWidget();
	}
	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}

void URestartWidget::OnExitClicked()
{
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		ADodgeballPlayerController::GameIn = false;

		for (TActorIterator<AMusicManager> Iter(GetWorld()); Iter; ++Iter) // 월드에 있는 DodgeballCharacter 찾기
		{
			AMusicManager* Music = *Iter; // Player 변수에 DodgeballCharacter 담기

			if (Music != nullptr)
			{
				Music->StopMusic();
				Music->PlayMainSound();
			}
		}

		PlayerController->HideRestartWidget();
		PlayerController->ShowMainMenuWidget();
	}
}

void URestartWidget::UpdateHealth(float Health)
{
	FString NewString = FString::FromInt(Health);
	FText InText = FText::FromString(NewString);
	Healthtext->SetText(InText);
}

void URestartWidget::UpdateGold(int Gold)
{
	FString NewString = FString::FromInt(Gold);
	FText InText = FText::FromString(NewString);
	GetCointext->SetText(InText);
}

void URestartWidget::UpdateStage(int Stage)
{
	FString NewString = FString::FromInt(Stage);
	FText InText = FText::FromString(NewString);
	Stagetext->SetText(InText);
}

void URestartWidget::UpdateTime(float Time, float Minute)
{
	FString NewString = FString::FromInt(Time);
	FText InText = FText::FromString(NewString);
	Timetext->SetText(InText);

	NewString = FString::FromInt(Minute);
	InText = FText::FromString(NewString);
	Minutetext->SetText(InText);
}

