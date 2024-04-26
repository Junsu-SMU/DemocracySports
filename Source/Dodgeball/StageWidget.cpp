// Fill out your copyright notice in the Description page of Project Settings.


#include "StageWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "DodgeballPlayerController.h"

void UStageWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Stage1Button != nullptr)
	{
		Stage1Button->OnClicked.AddDynamic(this, &UStageWidget::OnStage1Clicked);
	}

	if (Stage2Button != nullptr)
	{
		Stage2Button->OnClicked.AddDynamic(this, &UStageWidget::OnStage2Clicked);
	}

	if (Stage3Button != nullptr)
	{
		Stage3Button->OnClicked.AddDynamic(this, &UStageWidget::OnStage3Clicked);
	}

	if (Stage4Button != nullptr)
	{
		Stage4Button->OnClicked.AddDynamic(this, &UStageWidget::OnStage4Clicked);
	}

	if (Stage5Button != nullptr)
	{
		Stage5Button->OnClicked.AddDynamic(this, &UStageWidget::OnStage5Clicked);
	}

	if (ExitButton != nullptr)
	{
		ExitButton->OnClicked.AddDynamic(this, &UStageWidget::OnExitClicked);
	}

}

void UStageWidget::OnStage1Clicked()
{
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HideStageWidget();
	}
	ADodgeballPlayerController::GameStart += 1;
	ADodgeballPlayerController::CurrentLevel = 0;
	ADodgeballPlayerController::GameIn = true;
	UGameplayStatics::OpenLevel(this, FName("Level1"));
}

void UStageWidget::OnStage2Clicked()
{
	if (ADodgeballPlayerController::ReachedLevel >= 1)
	{
		ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
		if (PlayerController != nullptr)
		{
			PlayerController->HideStageWidget();
		}
		ADodgeballPlayerController::GameStart += 1;
		ADodgeballPlayerController::CurrentLevel = 1;
		ADodgeballPlayerController::GameIn = true;
		UGameplayStatics::OpenLevel(this, FName("Level2"));
	}
}

void UStageWidget::OnStage3Clicked()
{
	if (ADodgeballPlayerController::ReachedLevel >= 2)
	{
		ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
		if (PlayerController != nullptr)
		{
			PlayerController->HideStageWidget();
		}
		ADodgeballPlayerController::GameStart += 1;
		ADodgeballPlayerController::CurrentLevel = 2;
		ADodgeballPlayerController::GameIn = true;
		UGameplayStatics::OpenLevel(this, FName("Level3"));
	}
}

void UStageWidget::OnStage4Clicked()
{
	if (ADodgeballPlayerController::ReachedLevel >= 3)
	{
		ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
		if (PlayerController != nullptr)
		{
			PlayerController->HideStageWidget();
		}
		ADodgeballPlayerController::GameStart += 1;
		ADodgeballPlayerController::CurrentLevel = 3;
		ADodgeballPlayerController::GameIn = true;
		UGameplayStatics::OpenLevel(this, FName("Level4"));
	}
}

void UStageWidget::OnStage5Clicked()
{
	if (ADodgeballPlayerController::ReachedLevel >= 4)
	{
		ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
		if (PlayerController != nullptr)
		{
			PlayerController->HideStageWidget();
		}ADodgeballPlayerController::GameStart += 1;
		ADodgeballPlayerController::CurrentLevel = 4;
		ADodgeballPlayerController::GameIn = true;
		UGameplayStatics::OpenLevel(this, FName("Level5"));
	}
}

void UStageWidget::OnExitClicked()
{
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HideStageWidget();
		PlayerController->ShowMainMenuWidget();
	}
}
