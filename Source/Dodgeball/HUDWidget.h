// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 *
 */
UCLASS()
class DODGEBALL_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpdateHealthPercent(float HealthPercent);
	void UpdateVotePercent(float VotePercent);
	void UpdateGoalVotePercent(int GoalVotePercent);
	void UpdateSlidingBar(float SlidingCool);
	void UpdateTime(float Time);
	void UpdateMission(int Mission, float Fill, float FillMax, float TimePercent, float FillPercent);
	void ShowClear();
	void ShowStart();
	void ShowLose();
	void Hiding();

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* VoteBar;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* MissionTime;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* MissionFill;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* SlidingBar;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Healthtext;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Votetext;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* GoalVotetext;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Timetext;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Minutetext;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Missiontask;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MTime;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MFillMax;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MFill;

	UPROPERTY(meta = (BindWidget))
		class UImage* Start;

	UPROPERTY(meta = (BindWidget))
		class UImage* Clear;

	UPROPERTY(meta = (BindWidget))
		class UImage* Lose;

};
