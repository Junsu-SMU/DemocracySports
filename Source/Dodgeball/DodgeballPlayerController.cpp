// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeballPlayerController.h"
#include "DodgeballCharacter.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RestartWidget.h"
#include "HUDWidget.h"
#include "MainMenuWidget.h"
#include "ClearWidget.h"
#include "StageWidget.h"
#include "RankWidget.h"
#include "Store1Widget.h"
#include "Store2Widget.h"
#include "Store3Widget.h"
#include "SpawnObject.h"
#include "TimerManager.h"
#include "EngineUtils.h"
#include "Containers/Array.h"

int ADodgeballPlayerController::GameStart = 0;
int ADodgeballPlayerController::ReachedLevel = 0;
int ADodgeballPlayerController::CurrentLevel = 0;
int ADodgeballPlayerController::Gold = 0;
int ADodgeballPlayerController::InGameMission = 0;
float ADodgeballPlayerController::GoalVote = 25.f;
float ADodgeballPlayerController::Minutetime = 0.f;
bool ADodgeballPlayerController::GameIn = false;
TArray<float> ADodgeballPlayerController::S1R1Arr = { 0, 0, 0, 0, 0 }; // 기록유무, 스코어, 스테이지, 체력, 시간
TArray<float> ADodgeballPlayerController::S1R2Arr = { 0, 0, 0, 0, 0 };
TArray<float> ADodgeballPlayerController::S1R3Arr = { 0, 0, 0, 0, 0 };
TArray<float> ADodgeballPlayerController::S2R1Arr = { 0, 0, 0, 0, 0 };
TArray<float> ADodgeballPlayerController::S2R2Arr = { 0, 0, 0, 0, 0 };
TArray<float> ADodgeballPlayerController::S2R3Arr = { 0, 0, 0, 0, 0 };
TArray<float> ADodgeballPlayerController::S3R1Arr = { 0, 0, 0, 0, 0 };
TArray<float> ADodgeballPlayerController::S3R2Arr = { 0, 0, 0, 0, 0 };
TArray<float> ADodgeballPlayerController::S3R3Arr = { 0, 0, 0, 0, 0 };
TArray<float> ADodgeballPlayerController::S4R1Arr = { 0, 0, 0, 0, 0 };
TArray<float> ADodgeballPlayerController::S4R2Arr = { 0, 0, 0, 0, 0 };
TArray<float> ADodgeballPlayerController::S4R3Arr = { 0, 0, 0, 0, 0 };
TArray<float> ADodgeballPlayerController::S5R1Arr = { 0, 0, 0, 0, 0 };
TArray<float> ADodgeballPlayerController::S5R2Arr = { 0, 0, 0, 0, 0 };
TArray<float> ADodgeballPlayerController::S5R3Arr = { 0, 0, 0, 0, 0 };

void ADodgeballPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (ADodgeballPlayerController::GameStart < 1)
	{
		ShowMainMenuWidget();
	}

	if (BP_HUDWidget != nullptr && ADodgeballPlayerController::GameStart > 0)
	{
		GetWorldTimerManager().SetTimer(GameTimerHandle,
			this,
			&ADodgeballPlayerController::UpdateTimeShape, // 사용할 함수
			60, // 쿨타임
			true); // 루프X

		HUDWidget = CreateWidget<UHUDWidget>(this, BP_HUDWidget);
		ADodgeballPlayerController::UpdateGoalVotePercent();
		ADodgeballPlayerController::UpdateVotePercent(0.2);
		ADodgeballPlayerController::UpdateHealthPercent(ADodgeballCharacter::playerhp);
		HUDWidget->AddToViewport();
	}

	ADodgeballCharacter::SlidingCooltime = false;

}

void ADodgeballPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateGameTime();

	if (ADodgeballCharacter::SlidingCooltime == true)
	{
		UpdateSlidingBar();
	}
}

void ADodgeballPlayerController::SlidingOn()
{
	if (ADodgeballCharacter::SlidingCooltime == true)
	{
		GetWorldTimerManager().SetTimer(SlidingTimerHandle,
			this,
			&ADodgeballPlayerController::ClearSlidingTime, // 사용할 함수
			ADodgeballCharacter::playercooltime, // 쿨타임
			false); // 루프
	}

}

void ADodgeballPlayerController::UpdateSlidingBar()
{
	if (HUDWidget != nullptr)
	{
		float GameTimerElapsed = GetWorldTimerManager().GetTimerElapsed(SlidingTimerHandle);
		HUDWidget->UpdateSlidingBar(ADodgeballCharacter::playercooltime - GameTimerElapsed);
	}
}

void ADodgeballPlayerController::ClearSlidingTime()
{
	if (HUDWidget != nullptr)
	{
		float GameTimerElapsed = GetWorldTimerManager().GetTimerElapsed(SlidingTimerHandle);
		HUDWidget->UpdateSlidingBar(0);
	}
	GetWorldTimerManager().ClearTimer(SlidingTimerHandle);
}

void ADodgeballPlayerController::UpdateMission(int Mission, float Fill, float FillMax, float TimePercent, float FillPercent)
{
	if (HUDWidget != nullptr)
	{
		HUDWidget->UpdateMission(Mission, Fill,  FillMax, TimePercent, FillPercent);
	}
}

void ADodgeballPlayerController::ShowRestartWidget()
{
	if (BP_RestartWidget != nullptr)
	{
		if (StageFailSound != nullptr)
		{
			UGameplayStatics::PlaySound2D(GetPawn(), StageFailSound);
		}
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		RestartWidget = CreateWidget<URestartWidget>(this, BP_RestartWidget);

		ADodgeballPlayerController::Minutetime = 0;
		RestartWidget->AddToViewport();
	}
}

void ADodgeballPlayerController::HideRestartWidget()
{
	if (RestartWidget != nullptr)
	{
		RestartWidget->RemoveFromParent();
		RestartWidget->Destruct();
		SetPause(false);
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void ADodgeballPlayerController::ShowClearWidget(float Health)
{
	if (BP_ClearWidget != nullptr)
	{
		if (StageClearSound != nullptr)
		{
			UGameplayStatics::PlaySound2D(GetPawn(), StageClearSound);
		}
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		ClearWidget = CreateWidget<UClearWidget>(this, BP_ClearWidget);
		ClearWidget->UpdateHealth(Health);
		ClearWidget->UpdateGold(1000 * (ADodgeballPlayerController::CurrentLevel + 1));
		ClearWidget->UpdateStage(ADodgeballPlayerController::CurrentLevel + 1);
		float GameTimerElapsed = GetWorldTimerManager().GetTimerElapsed(GameTimerHandle);
		ClearWidget->UpdateTime(GameTimerElapsed, ADodgeballPlayerController::Minutetime);
		float Score = 100 + Health - (0.5 * (GameTimerElapsed + (60 * ADodgeballPlayerController::Minutetime)));
		ClearWidget->UpdateRank(Score);

		if (ADodgeballPlayerController::CurrentLevel == 0) 
		{
			if (ADodgeballPlayerController::S1R1Arr[1] < Score) // 기록유무, 스코어, 스테이지, 체력, 시간
			{
				ADodgeballPlayerController::S1R3Arr = ADodgeballPlayerController::S1R2Arr;
				ADodgeballPlayerController::S1R2Arr = ADodgeballPlayerController::S1R1Arr;
				ADodgeballPlayerController::S1R1Arr = { 10, Score, 1, Health, GameTimerElapsed + (60 * ADodgeballPlayerController::Minutetime) };
			}
			else if (ADodgeballPlayerController::S1R2Arr[1] < Score) // 기록유무, 스코어, 스테이지, 체력, 시간
			{
				ADodgeballPlayerController::S1R3Arr = ADodgeballPlayerController::S1R2Arr;
				ADodgeballPlayerController::S1R2Arr = { 10, Score, 1, Health, GameTimerElapsed + (60 * ADodgeballPlayerController::Minutetime) };
			}
			else if (ADodgeballPlayerController::S1R3Arr[1] < Score) // 기록유무, 스코어, 스테이지, 체력, 시간
			{
				ADodgeballPlayerController::S1R3Arr = { 10, Score, 1, Health, GameTimerElapsed + (60 * ADodgeballPlayerController::Minutetime) };
			}
		}
		else if (ADodgeballPlayerController::CurrentLevel == 1)
		{
			if (ADodgeballPlayerController::S2R1Arr[1] < Score) // 기록유무, 스코어, 스테이지, 체력, 시간
			{
				ADodgeballPlayerController::S2R3Arr = ADodgeballPlayerController::S2R2Arr;
				ADodgeballPlayerController::S2R2Arr = ADodgeballPlayerController::S2R1Arr;
				ADodgeballPlayerController::S2R1Arr = { 10, Score, 2, Health, GameTimerElapsed + (60 * ADodgeballPlayerController::Minutetime) };
			}
			else if (ADodgeballPlayerController::S2R2Arr[1] < Score) // 기록유무, 스코어, 스테이지, 체력, 시간
			{
				ADodgeballPlayerController::S2R3Arr = ADodgeballPlayerController::S2R2Arr;
				ADodgeballPlayerController::S2R2Arr = { 10, Score, 2, Health, GameTimerElapsed + (60 * ADodgeballPlayerController::Minutetime) };
			}
			else if (ADodgeballPlayerController::S2R3Arr[1] < Score) // 기록유무, 스코어, 스테이지, 체력, 시간
			{
				ADodgeballPlayerController::S2R3Arr = { 10, Score, 2, Health, GameTimerElapsed + (60 * ADodgeballPlayerController::Minutetime) };
			}
		}
		else if (ADodgeballPlayerController::CurrentLevel == 2)
		{
			if (ADodgeballPlayerController::S3R1Arr[1] < Score) // 기록유무, 스코어, 스테이지, 체력, 시간
			{
				ADodgeballPlayerController::S3R3Arr = ADodgeballPlayerController::S3R2Arr;
				ADodgeballPlayerController::S3R2Arr = ADodgeballPlayerController::S3R1Arr;
				ADodgeballPlayerController::S3R1Arr = { 10, Score, 3, Health, GameTimerElapsed + (60 * ADodgeballPlayerController::Minutetime) };
			}
			else if (ADodgeballPlayerController::S3R2Arr[1] < Score) // 기록유무, 스코어, 스테이지, 체력, 시간
			{
				ADodgeballPlayerController::S3R3Arr = ADodgeballPlayerController::S3R2Arr;
				ADodgeballPlayerController::S3R2Arr = { 10, Score, 3, Health, GameTimerElapsed + (60 * ADodgeballPlayerController::Minutetime) };
			}
			else if (ADodgeballPlayerController::S3R3Arr[1] < Score) // 기록유무, 스코어, 스테이지, 체력, 시간
			{
				ADodgeballPlayerController::S3R3Arr = { 10, Score, 3, Health, GameTimerElapsed + (60 * ADodgeballPlayerController::Minutetime) };
			}
		}
		else if (ADodgeballPlayerController::CurrentLevel == 3)
		{
			if (ADodgeballPlayerController::S4R1Arr[1] < Score) // 기록유무, 스코어, 스테이지, 체력, 시간
			{
				ADodgeballPlayerController::S4R3Arr = ADodgeballPlayerController::S4R2Arr;
				ADodgeballPlayerController::S4R2Arr = ADodgeballPlayerController::S4R1Arr;
				ADodgeballPlayerController::S4R1Arr = { 10, Score, 4, Health, GameTimerElapsed + (60 * ADodgeballPlayerController::Minutetime) };
			}
			else if (ADodgeballPlayerController::S4R2Arr[1] < Score) // 기록유무, 스코어, 스테이지, 체력, 시간
			{
				ADodgeballPlayerController::S4R3Arr = ADodgeballPlayerController::S4R2Arr;
				ADodgeballPlayerController::S4R2Arr = { 10, Score, 4, Health, GameTimerElapsed + (60 * ADodgeballPlayerController::Minutetime) };
			}
			else if (ADodgeballPlayerController::S4R3Arr[1] < Score) // 기록유무, 스코어, 스테이지, 체력, 시간
			{
				ADodgeballPlayerController::S4R3Arr = { 10, Score, 4, Health, GameTimerElapsed + (60 * ADodgeballPlayerController::Minutetime) };
			}
			else if (ADodgeballPlayerController::CurrentLevel == 4)
			{
				if (ADodgeballPlayerController::S5R1Arr[1] < Score) // 기록유무, 스코어, 스테이지, 체력, 시간
				{
					ADodgeballPlayerController::S5R3Arr = ADodgeballPlayerController::S5R2Arr;
					ADodgeballPlayerController::S5R2Arr = ADodgeballPlayerController::S5R1Arr;
					ADodgeballPlayerController::S5R1Arr = { 10, Score, 5, Health, GameTimerElapsed + (60 * ADodgeballPlayerController::Minutetime) };
				}
				else if (ADodgeballPlayerController::S5R2Arr[1] < Score) // 기록유무, 스코어, 스테이지, 체력, 시간
				{
					ADodgeballPlayerController::S5R3Arr = ADodgeballPlayerController::S5R2Arr;
					ADodgeballPlayerController::S5R2Arr = { 10, Score, 5, Health, GameTimerElapsed + (60 * ADodgeballPlayerController::Minutetime) };
				}
				else if (ADodgeballPlayerController::S5R3Arr[1] < Score) // 기록유무, 스코어, 스테이지, 체력, 시간
				{
					ADodgeballPlayerController::S5R3Arr = { 10, Score, 5, Health, GameTimerElapsed + (60 * ADodgeballPlayerController::Minutetime) };
				}
			}
		}
		ADodgeballPlayerController::Minutetime = 0;

		ClearWidget->AddToViewport();
	}
}

void ADodgeballPlayerController::HideClearWidget()
{
	if (ClearWidget != nullptr)
	{
		ClearWidget->RemoveFromParent();
		ClearWidget->Destruct();
		SetPause(false);
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void ADodgeballPlayerController::ShowMainMenuWidget()
{
	if (BP_MainMenuWidget != nullptr)
	{
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		MainMenuWidget = CreateWidget<UMainMenuWidget>(this, BP_MainMenuWidget);
		MainMenuWidget->AddToViewport();
	}
}

void ADodgeballPlayerController::HideMainMenuWidget()
{
	if (MainMenuWidget != nullptr)
	{
		MainMenuWidget->RemoveFromParent();
		MainMenuWidget->Destruct();
		SetPause(false);
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void ADodgeballPlayerController::ShowStageWidget()
{
	if (BP_StageWidget != nullptr)
	{
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		StageWidget = CreateWidget<UStageWidget>(this, BP_StageWidget);
		StageWidget->AddToViewport();
	}
}

void ADodgeballPlayerController::HideStageWidget()
{
	if (StageWidget != nullptr)
	{
		StageWidget->RemoveFromParent();
		StageWidget->Destruct();
		SetPause(false);
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void ADodgeballPlayerController::ShowRankWidget()
{
	if (BP_RankWidget != nullptr)
	{
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		RankWidget = CreateWidget<URankWidget>(this, BP_RankWidget);
		RankWidget->AddToViewport();
		RankWidget->EnterRankingUI();
	}
}

void ADodgeballPlayerController::HideRankWidget()
{
	if (RankWidget != nullptr)
	{
		RankWidget->RemoveFromParent();
		RankWidget->Destruct();
		SetPause(false);
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void ADodgeballPlayerController::ShowStore1Widget()
{
	if (BP_Store1Widget != nullptr)
	{
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		Store1Widget = CreateWidget<UStore1Widget>(this, BP_Store1Widget);
		Store1Widget->UpdateGold(ADodgeballPlayerController::Gold);
		Store1Widget->AddToViewport();
	}
}

void ADodgeballPlayerController::HideStore1Widget()
{
	if (Store1Widget != nullptr)
	{
		Store1Widget->RemoveFromParent();
		Store1Widget->Destruct();
		SetPause(false);
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void ADodgeballPlayerController::ShowStore2Widget()
{
	if (BP_Store2Widget != nullptr)
	{
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		Store2Widget = CreateWidget<UStore2Widget>(this, BP_Store2Widget);
		Store2Widget->UpdateGold(ADodgeballPlayerController::Gold);
		Store2Widget->AddToViewport();
	}
}

void ADodgeballPlayerController::HideStore2Widget()
{
	if (Store2Widget != nullptr)
	{
		Store2Widget->RemoveFromParent();
		Store2Widget->Destruct();
		SetPause(false);
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void ADodgeballPlayerController::ShowStore3Widget()
{
	if (BP_Store3Widget != nullptr)
	{
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		Store3Widget = CreateWidget<UStore3Widget>(this, BP_Store3Widget);
		Store3Widget->UpdateGold(ADodgeballPlayerController::Gold);
		Store3Widget->AddToViewport();
	}
}

void ADodgeballPlayerController::HideStore3Widget()
{
	if (Store3Widget != nullptr)
	{
		Store3Widget->RemoveFromParent();
		Store3Widget->Destruct();
		SetPause(false);
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void ADodgeballPlayerController::UpdateHealthPercent(float HealthPercent)
{
	if (HUDWidget != nullptr)
	{
		HUDWidget->UpdateHealthPercent(HealthPercent);
	}
}

void ADodgeballPlayerController::UpdateVotePercent(float VotePercent)
{
	if (HUDWidget != nullptr)
	{
		HUDWidget->UpdateVotePercent(VotePercent);
	}
}

void ADodgeballPlayerController::UpdateGoalVotePercent()
{
	if (HUDWidget != nullptr)
	{
		if (ADodgeballPlayerController::CurrentLevel == 0)
		{
			ADodgeballPlayerController::GoalVote = 25.f;
			HUDWidget->UpdateGoalVotePercent(25);
		}
		else if (ADodgeballPlayerController::CurrentLevel == 1)
		{
			ADodgeballPlayerController::GoalVote = 30.f;
			HUDWidget->UpdateGoalVotePercent(30);
		}
		else if (ADodgeballPlayerController::CurrentLevel == 2)
		{
			ADodgeballPlayerController::GoalVote = 35.f;
			HUDWidget->UpdateGoalVotePercent(35);
		}
		else if (ADodgeballPlayerController::CurrentLevel == 3)
		{
			ADodgeballPlayerController::GoalVote = 40.f;
			HUDWidget->UpdateGoalVotePercent(40);
		}
		else if (ADodgeballPlayerController::CurrentLevel == 4)
		{
			ADodgeballPlayerController::GoalVote = 45.f;
			HUDWidget->UpdateGoalVotePercent(45);
		}
	}
}

void ADodgeballPlayerController::UpdateGameTime()
{
	if (HUDWidget != nullptr)
	{
		float GameTimerElapsed = GetWorldTimerManager().GetTimerElapsed(GameTimerHandle);
		HUDWidget->UpdateTime(GameTimerElapsed);
	}
}

void ADodgeballPlayerController::UpdateTimeShape()
{
	if (ADodgeballCharacter::healperminute == true)
	{
		ADodgeballCharacter* MyPlayer = Cast<ADodgeballCharacter>(GetPawn()); // Player 변수에 DodgeballCharacter 담기

		if (MyPlayer != nullptr)
		{
			UHealthComponent* HealthComponent = MyPlayer->FindComponentByClass<UHealthComponent>();
			if (HealthComponent != nullptr)
			{
				HealthComponent->LoseHealth(-10); // HealthComponent에 있는 LoseVote함수 실행
			}
		}
	}
	ADodgeballPlayerController::Minutetime += 1;
}

void ADodgeballPlayerController::ShowHUDStart()
{
	if (HUDWidget != nullptr)
	{
		HUDWidget->ShowStart();
	}
}

void ADodgeballPlayerController::ShowHUDClear()
{
	if (HUDWidget != nullptr)
	{
		HUDWidget->ShowClear();
	}
}

void ADodgeballPlayerController::ShowHUDLose()
{
	if (HUDWidget != nullptr)
	{
		HUDWidget->ShowLose();
	}
}

void ADodgeballPlayerController::Hiding()
{
	if (HUDWidget != nullptr)
	{
		HUDWidget->Hiding();
	}
}
