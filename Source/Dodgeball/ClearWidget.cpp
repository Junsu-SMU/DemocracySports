// Fill out your copyright notice in the Description page of Project Settings.


#include "ClearWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "DodgeballPlayerController.h"
#include "SpawnObject.h"
#include "MusicManager.h"
#include "EngineUtils.h"

void UClearWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (NextLevelButton != nullptr)
	{
		NextLevelButton->OnClicked.AddDynamic(this, &UClearWidget::OnNextLevelClicked);
	}

	if (RestartButton != nullptr)
	{
		RestartButton->OnClicked.AddDynamic(this, &UClearWidget::OnRestartClicked);
	}

	if (ExitButton != nullptr)
	{
		ExitButton->OnClicked.AddDynamic(this, &UClearWidget::OnExitClicked);
	}
}

void UClearWidget::OnNextLevelClicked()
{
	ADodgeballPlayerController::CurrentLevel += 1;
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HideClearWidget();
	}
	if (ADodgeballPlayerController::CurrentLevel == 1)
	{
		UGameplayStatics::OpenLevel(this, FName("Level2"));
	}
	else if (ADodgeballPlayerController::CurrentLevel == 2)
	{
		UGameplayStatics::OpenLevel(this, FName("Level3"));
	}
	else if (ADodgeballPlayerController::CurrentLevel == 3)
	{
		UGameplayStatics::OpenLevel(this, FName("Level4"));
	}
	else if (ADodgeballPlayerController::CurrentLevel == 4)
	{
		UGameplayStatics::OpenLevel(this, FName("Level5"));
	}
}

void UClearWidget::OnRestartClicked()
{
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HideRestartWidget();
	}
	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}

void UClearWidget::OnExitClicked()
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

void UClearWidget::UpdateRank(float Score)
{
	FString NewString = FString::FromInt(Score);
	FText InText = FText::FromString(NewString);
	RankScore->SetText(InText);
	if (Score >= 160)
	{
		Ranktext->SetText(FText::FromString("S"));
	}
	else if (Score >= 130)
	{
		Ranktext->SetText(FText::FromString("A"));
	}
	else if (Score >= 100)
	{
		Ranktext->SetText(FText::FromString("A"));
	}
	else if (Score >= 80)
	{
		Ranktext->SetText(FText::FromString("B"));
	}
	else if (Score >= 60)
	{
		Ranktext->SetText(FText::FromString("C"));
	}
	else if (Score >= 40)
	{
		Ranktext->SetText(FText::FromString("D"));
	}
	else if (Score >= 20)
	{
		Ranktext->SetText(FText::FromString("E"));
	}
	else if (Score >= 0)
	{
		Ranktext->SetText(FText::FromString("F"));
	}
	else
	{
		Ranktext->SetText(FText::FromString("G"));
	}
}

void UClearWidget::UpdateHealth(float Health)
{
	FString NewString = FString::FromInt(Health);
	FText InText = FText::FromString(NewString);
	Healthtext->SetText(InText);
}

void UClearWidget::UpdateGold(int Gold)
{
	FString NewString = FString::FromInt(Gold);
	FText InText = FText::FromString(NewString);
	GetCointext->SetText(InText);
}

void UClearWidget::UpdateStage(int Stage)
{
	FString NewString = FString::FromInt(Stage);
	FText InText = FText::FromString(NewString);
	Stagetext->SetText(InText);
}

void UClearWidget::UpdateTime(float Time, float Minute)
{
	FString NewString = FString::FromInt(Time);
	FText InText = FText::FromString(NewString);
	Timetext->SetText(InText);

	NewString = FString::FromInt(Minute);
	InText = FText::FromString(NewString);
	Minutetext->SetText(InText);
}
