// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "DodgeballPlayerController.h"
#include "DodgeballCharacter.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UHUDWidget::UpdateHealthPercent(float HealthPercent)
{
	FString NewString = FString::FromInt(HealthPercent);
	FText InText = FText::FromString(NewString);
	Healthtext->SetText(InText);
	//ADodgeballPlayerController::GoalVote
}

void UHUDWidget::UpdateVotePercent(float VotePercent)
{
	int Value = (int)(round(VotePercent * 100));
	FString NewString = FString::FromInt(Value);
	FText InText = FText::FromString(NewString);
	Votetext->SetText(InText);
	float a = ADodgeballPlayerController::GoalVote / 100.f;
	VotePercent = VotePercent/a;
	VoteBar->SetPercent(VotePercent);
}

void UHUDWidget::UpdateGoalVotePercent(int GoalVotePercent)
{
	FString NewString = FString::FromInt(GoalVotePercent);
	FText InText = FText::FromString(NewString);
	GoalVotetext->SetText(InText);
}

void UHUDWidget::UpdateSlidingBar(float SlidingCool)
{
	SlidingBar->SetPercent(SlidingCool / ADodgeballCharacter::playercooltime);
}

void UHUDWidget::UpdateTime(float Time)
{
	FString NewString = FString::FromInt(Time);
	FText InText = FText::FromString(NewString);
	Timetext->SetText(InText);

	NewString = FString::FromInt(ADodgeballPlayerController::Minutetime);
	InText = FText::FromString(NewString);
	Minutetext->SetText(InText);
}

void UHUDWidget::UpdateMission(int Mission, float Fill, float FillMax, float TimePercent, float FillPercent)
{
	if (Mission == 1)
	{
		Missiontask->SetText(FText::FromString("MISSION1 : Shake hands with 4 Citizen."));
	}
	else if (Mission == 2)
	{
		Missiontask->SetText(FText::FromString("MISSION2 : Carry 3 briquettes on the truck."));
	}
	else if (Mission == 3)
	{
		Missiontask->SetText(FText::FromString("MISSION3 : Interview a Voter."));
	}
	else if (Mission == 4)
	{
		Missiontask->SetText(FText::FromString("MISSION4 : Avoid the demonstrators."));
	}
	else
	{
		Missiontask->SetText(FText::FromString("MISSION : "));
	}

	FString NewString = FString::FromInt(FillMax);
	FText InText = FText::FromString(NewString);
	MFillMax->SetText(InText);

	NewString = FString::FromInt(TimePercent);
	InText = FText::FromString(NewString + "s");
	MTime->SetText(InText);

	NewString = FString::FromInt(Fill);
	InText = FText::FromString(NewString);
	MFill->SetText(InText);

	MissionTime->SetPercent(TimePercent/15);
	if (Fill == 0 && FillMax == 0)
	{
		MissionFill->SetPercent(0);
	}
	else
	{
		MissionFill->SetPercent(Fill / FillMax);
	}
}

void UHUDWidget::ShowClear()
{
	Start->SetVisibility(ESlateVisibility::Collapsed);
	Lose->SetVisibility(ESlateVisibility::Collapsed);
	Clear->SetVisibility(ESlateVisibility::Visible);

}

void UHUDWidget::ShowStart()
{
	Clear->SetVisibility(ESlateVisibility::Collapsed);
	Lose->SetVisibility(ESlateVisibility::Collapsed);
	Start->SetVisibility(ESlateVisibility::Visible);
}

void UHUDWidget::ShowLose()
{
	Start->SetVisibility(ESlateVisibility::Collapsed);
	Clear->SetVisibility(ESlateVisibility::Collapsed);
	Lose->SetVisibility(ESlateVisibility::Visible);
}

void UHUDWidget::Hiding()
{
	Start->SetVisibility(ESlateVisibility::Collapsed);
	Clear->SetVisibility(ESlateVisibility::Collapsed);
	Lose->SetVisibility(ESlateVisibility::Collapsed);
}
