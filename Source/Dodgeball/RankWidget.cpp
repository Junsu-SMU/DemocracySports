// Fill out your copyright notice in the Description page of Project Settings.


#include "RankWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "DodgeballPlayerController.h"
#include "Containers/Array.h"

void URankWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Stage1Button != nullptr)
	{
		Stage1Button->OnClicked.AddDynamic(this, &URankWidget::OnStage1Clicked);
	}

	if (Stage2Button != nullptr)
	{
		Stage2Button->OnClicked.AddDynamic(this, &URankWidget::OnStage2Clicked);
	}

	if (Stage3Button != nullptr)
	{
		Stage3Button->OnClicked.AddDynamic(this, &URankWidget::OnStage3Clicked);
	}

	if (Stage4Button != nullptr)
	{
		Stage4Button->OnClicked.AddDynamic(this, &URankWidget::OnStage4Clicked);
	}

	if (Stage5Button != nullptr)
	{
		Stage5Button->OnClicked.AddDynamic(this, &URankWidget::OnStage5Clicked);
	}

	if (RankoffButton != nullptr)
	{
		RankoffButton->OnClicked.AddDynamic(this, &URankWidget::OnRankoffClicked);
	}

}

void URankWidget::OnStage1Clicked()
{
	if (ADodgeballPlayerController::S1R1Arr[0] > 1) // 기록이 있으면
	{
		if (ADodgeballPlayerController::S1R1Arr[1] >= 160)
		{
			Text_1_0->SetText(FText::FromString("S"));
		}
		else if (ADodgeballPlayerController::S1R1Arr[1] >= 130)
		{
			Text_1_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S1R1Arr[1] >= 100)
		{
			Text_1_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S1R1Arr[1] >= 80)
		{
			Text_1_0->SetText(FText::FromString("B"));
		}
		else if (ADodgeballPlayerController::S1R1Arr[1] >= 60)
		{
			Text_1_0->SetText(FText::FromString("C"));
		}
		else if (ADodgeballPlayerController::S1R1Arr[1] >= 40)
		{
			Text_1_0->SetText(FText::FromString("D"));
		}
		else if (ADodgeballPlayerController::S1R1Arr[1] >= 20)
		{
			Text_1_0->SetText(FText::FromString("E"));
		}
		else if (ADodgeballPlayerController::S1R1Arr[1] >= 0)
		{
			Text_1_0->SetText(FText::FromString("F"));
		}
		else
		{
			Text_1_0->SetText(FText::FromString("G"));
		}

		FString NewString = FString::FromInt(ADodgeballPlayerController::S1R1Arr[1]);
		FText InText = FText::FromString(NewString);
		Text_1_1->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S1R1Arr[2]);
		InText = FText::FromString(NewString);
		Text_1_2->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S1R1Arr[3]);
		InText = FText::FromString(NewString);
		Text_1_3->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S1R1Arr[4]);
		InText = FText::FromString(NewString);
		Text_1_4->SetText(InText);
	}
	else
	{
		Text_1_0->SetText(FText::FromString(" "));
		Text_1_1->SetText(FText::FromString(" "));
		Text_1_2->SetText(FText::FromString(" "));
		Text_1_3->SetText(FText::FromString(" "));
		Text_1_4->SetText(FText::FromString(" "));
	}

	if (ADodgeballPlayerController::S1R2Arr[0] > 1) // 기록이 있으면
	{
		if (ADodgeballPlayerController::S1R2Arr[1] >= 160)
		{
			Text_2_0->SetText(FText::FromString("S"));
		}
		else if (ADodgeballPlayerController::S1R2Arr[1] >= 130)
		{
			Text_2_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S1R2Arr[1] >= 100)
		{
			Text_2_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S1R2Arr[1] >= 80)
		{
			Text_2_0->SetText(FText::FromString("B"));
		}
		else if (ADodgeballPlayerController::S1R2Arr[1] >= 60)
		{
			Text_2_0->SetText(FText::FromString("C"));
		}
		else if (ADodgeballPlayerController::S1R2Arr[1] >= 40)
		{
			Text_2_0->SetText(FText::FromString("D"));
		}
		else if (ADodgeballPlayerController::S1R2Arr[1] >= 20)
		{
			Text_2_0->SetText(FText::FromString("E"));
		}
		else if (ADodgeballPlayerController::S1R2Arr[1] >= 0)
		{
			Text_2_0->SetText(FText::FromString("F"));
		}
		else
		{
			Text_2_0->SetText(FText::FromString("G"));
		}

		FString NewString = FString::FromInt(ADodgeballPlayerController::S1R2Arr[1]);
		FText InText = FText::FromString(NewString);
		Text_2_1->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S1R2Arr[2]);
		InText = FText::FromString(NewString);
		Text_2_2->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S1R2Arr[3]);
		InText = FText::FromString(NewString);
		Text_2_3->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S1R2Arr[4]);
		InText = FText::FromString(NewString);
		Text_2_4->SetText(InText);
	}
	else
	{
		Text_2_0->SetText(FText::FromString(" "));
		Text_2_1->SetText(FText::FromString(" "));
		Text_2_2->SetText(FText::FromString(" "));
		Text_2_3->SetText(FText::FromString(" "));
		Text_2_4->SetText(FText::FromString(" "));
	}

	if (ADodgeballPlayerController::S1R3Arr[0] > 1) // 기록이 있으면
	{
		if (ADodgeballPlayerController::S1R3Arr[1] >= 160)
		{
			Text_3_0->SetText(FText::FromString("S"));
		}
		else if (ADodgeballPlayerController::S1R3Arr[1] >= 130)
		{
			Text_3_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S1R3Arr[1] >= 100)
		{
			Text_3_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S1R3Arr[1] >= 80)
		{
			Text_3_0->SetText(FText::FromString("B"));
		}
		else if (ADodgeballPlayerController::S1R3Arr[1] >= 60)
		{
			Text_3_0->SetText(FText::FromString("C"));
		}
		else if (ADodgeballPlayerController::S1R3Arr[1] >= 40)
		{
			Text_3_0->SetText(FText::FromString("D"));
		}
		else if (ADodgeballPlayerController::S1R3Arr[1] >= 20)
		{
			Text_3_0->SetText(FText::FromString("E"));
		}
		else if (ADodgeballPlayerController::S1R3Arr[1] >= 0)
		{
			Text_3_0->SetText(FText::FromString("F"));
		}
		else
		{
			Text_3_0->SetText(FText::FromString("G"));
		}

		FString NewString = FString::FromInt(ADodgeballPlayerController::S1R3Arr[1]);
		FText InText = FText::FromString(NewString);
		Text_3_1->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S1R3Arr[2]);
		InText = FText::FromString(NewString);
		Text_3_2->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S1R3Arr[3]);
		InText = FText::FromString(NewString);
		Text_3_3->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S1R3Arr[4]);
		InText = FText::FromString(NewString);
		Text_3_4->SetText(InText);
	}
	else
	{
		Text_3_0->SetText(FText::FromString(" "));
		Text_3_1->SetText(FText::FromString(" "));
		Text_3_2->SetText(FText::FromString(" "));
		Text_3_3->SetText(FText::FromString(" "));
		Text_3_4->SetText(FText::FromString(" "));
	}

	RankStage->SetText(FText::FromString("STAGE 1"));
}

void URankWidget::OnStage2Clicked()
{
	if (ADodgeballPlayerController::S2R1Arr[0] > 1) // 기록이 있으면
	{
		if (ADodgeballPlayerController::S2R1Arr[1] >= 160)
		{
			Text_1_0->SetText(FText::FromString("S"));
		}
		else if (ADodgeballPlayerController::S2R1Arr[1] >= 130)
		{
			Text_1_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S2R1Arr[1] >= 100)
		{
			Text_1_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S2R1Arr[1] >= 80)
		{
			Text_1_0->SetText(FText::FromString("B"));
		}
		else if (ADodgeballPlayerController::S2R1Arr[1] >= 60)
		{
			Text_1_0->SetText(FText::FromString("C"));
		}
		else if (ADodgeballPlayerController::S2R1Arr[1] >= 40)
		{
			Text_1_0->SetText(FText::FromString("D"));
		}
		else if (ADodgeballPlayerController::S2R1Arr[1] >= 20)
		{
			Text_1_0->SetText(FText::FromString("E"));
		}
		else if (ADodgeballPlayerController::S2R1Arr[1] >= 0)
		{
			Text_1_0->SetText(FText::FromString("F"));
		}
		else
		{
			Text_1_0->SetText(FText::FromString("G"));
		}

		FString NewString = FString::FromInt(ADodgeballPlayerController::S2R1Arr[1]);
		FText InText = FText::FromString(NewString);
		Text_1_1->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S2R1Arr[2]);
		InText = FText::FromString(NewString);
		Text_1_2->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S2R1Arr[3]);
		InText = FText::FromString(NewString);
		Text_1_3->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S2R1Arr[4]);
		InText = FText::FromString(NewString);
		Text_1_4->SetText(InText);
	}
	else
	{
		Text_1_0->SetText(FText::FromString(" "));
		Text_1_1->SetText(FText::FromString(" "));
		Text_1_2->SetText(FText::FromString(" "));
		Text_1_3->SetText(FText::FromString(" "));
		Text_1_4->SetText(FText::FromString(" "));
	}

	if (ADodgeballPlayerController::S2R2Arr[0] > 1) // 기록이 있으면
	{
		if (ADodgeballPlayerController::S2R2Arr[1] >= 160)
		{
			Text_2_0->SetText(FText::FromString("S"));
		}
		else if (ADodgeballPlayerController::S2R2Arr[1] >= 130)
		{
			Text_2_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S2R2Arr[1] >= 100)
		{
			Text_2_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S2R2Arr[1] >= 80)
		{
			Text_2_0->SetText(FText::FromString("B"));
		}
		else if (ADodgeballPlayerController::S2R2Arr[1] >= 60)
		{
			Text_2_0->SetText(FText::FromString("C"));
		}
		else if (ADodgeballPlayerController::S2R2Arr[1] >= 40)
		{
			Text_2_0->SetText(FText::FromString("D"));
		}
		else if (ADodgeballPlayerController::S2R2Arr[1] >= 20)
		{
			Text_2_0->SetText(FText::FromString("E"));
		}
		else if (ADodgeballPlayerController::S2R2Arr[1] >= 0)
		{
			Text_2_0->SetText(FText::FromString("F"));
		}
		else
		{
			Text_2_0->SetText(FText::FromString("G"));
		}

		FString NewString = FString::FromInt(ADodgeballPlayerController::S2R2Arr[1]);
		FText InText = FText::FromString(NewString);
		Text_2_1->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S2R2Arr[2]);
		InText = FText::FromString(NewString);
		Text_2_2->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S2R2Arr[3]);
		InText = FText::FromString(NewString);
		Text_2_3->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S2R2Arr[4]);
		InText = FText::FromString(NewString);
		Text_2_4->SetText(InText);
	}
	else
	{
		Text_2_0->SetText(FText::FromString(" "));
		Text_2_1->SetText(FText::FromString(" "));
		Text_2_2->SetText(FText::FromString(" "));
		Text_2_3->SetText(FText::FromString(" "));
		Text_2_4->SetText(FText::FromString(" "));
	}

	if (ADodgeballPlayerController::S2R3Arr[0] > 1) // 기록이 있으면
	{
		if (ADodgeballPlayerController::S2R3Arr[1] >= 160)
		{
			Text_3_0->SetText(FText::FromString("S"));
		}
		else if (ADodgeballPlayerController::S2R3Arr[1] >= 130)
		{
			Text_3_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S2R3Arr[1] >= 100)
		{
			Text_3_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S2R3Arr[1] >= 80)
		{
			Text_3_0->SetText(FText::FromString("B"));
		}
		else if (ADodgeballPlayerController::S2R3Arr[1] >= 60)
		{
			Text_3_0->SetText(FText::FromString("C"));
		}
		else if (ADodgeballPlayerController::S2R3Arr[1] >= 40)
		{
			Text_3_0->SetText(FText::FromString("D"));
		}
		else if (ADodgeballPlayerController::S2R3Arr[1] >= 20)
		{
			Text_3_0->SetText(FText::FromString("E"));
		}
		else if (ADodgeballPlayerController::S2R3Arr[1] >= 0)
		{
			Text_3_0->SetText(FText::FromString("F"));
		}
		else
		{
			Text_3_0->SetText(FText::FromString("G"));
		}

		FString NewString = FString::FromInt(ADodgeballPlayerController::S2R3Arr[1]);
		FText InText = FText::FromString(NewString);
		Text_3_1->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S2R3Arr[2]);
		InText = FText::FromString(NewString);
		Text_3_2->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S2R3Arr[3]);
		InText = FText::FromString(NewString);
		Text_3_3->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S2R3Arr[4]);
		InText = FText::FromString(NewString);
		Text_3_4->SetText(InText);
	}
	else
	{
		Text_3_0->SetText(FText::FromString(" "));
		Text_3_1->SetText(FText::FromString(" "));
		Text_3_2->SetText(FText::FromString(" "));
		Text_3_3->SetText(FText::FromString(" "));
		Text_3_4->SetText(FText::FromString(" "));
	}

	RankStage->SetText(FText::FromString("STAGE 2"));
}

void URankWidget::OnStage3Clicked()
{
	if (ADodgeballPlayerController::S3R1Arr[0] > 1) // 기록이 있으면
	{
		if (ADodgeballPlayerController::S3R1Arr[1] >= 160)
		{
			Text_1_0->SetText(FText::FromString("S"));
		}
		else if (ADodgeballPlayerController::S3R1Arr[1] >= 130)
		{
			Text_1_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S3R1Arr[1] >= 100)
		{
			Text_1_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S3R1Arr[1] >= 80)
		{
			Text_1_0->SetText(FText::FromString("B"));
		}
		else if (ADodgeballPlayerController::S3R1Arr[1] >= 60)
		{
			Text_1_0->SetText(FText::FromString("C"));
		}
		else if (ADodgeballPlayerController::S3R1Arr[1] >= 40)
		{
			Text_1_0->SetText(FText::FromString("D"));
		}
		else if (ADodgeballPlayerController::S3R1Arr[1] >= 20)
		{
			Text_1_0->SetText(FText::FromString("E"));
		}
		else if (ADodgeballPlayerController::S3R1Arr[1] >= 0)
		{
			Text_1_0->SetText(FText::FromString("F"));
		}
		else
		{
			Text_1_0->SetText(FText::FromString("G"));
		}

		FString NewString = FString::FromInt(ADodgeballPlayerController::S3R1Arr[1]);
		FText InText = FText::FromString(NewString);
		Text_1_1->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S3R1Arr[2]);
		InText = FText::FromString(NewString);
		Text_1_2->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S3R1Arr[3]);
		InText = FText::FromString(NewString);
		Text_1_3->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S3R1Arr[4]);
		InText = FText::FromString(NewString);
		Text_1_4->SetText(InText);
	}
	else
	{
		Text_1_0->SetText(FText::FromString(" "));
		Text_1_1->SetText(FText::FromString(" "));
		Text_1_2->SetText(FText::FromString(" "));
		Text_1_3->SetText(FText::FromString(" "));
		Text_1_4->SetText(FText::FromString(" "));
	}

	if (ADodgeballPlayerController::S3R2Arr[0] > 1) // 기록이 있으면
	{
		if (ADodgeballPlayerController::S3R2Arr[1] >= 160)
		{
			Text_2_0->SetText(FText::FromString("S"));
		}
		else if (ADodgeballPlayerController::S3R2Arr[1] >= 130)
		{
			Text_2_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S3R2Arr[1] >= 100)
		{
			Text_2_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S3R2Arr[1] >= 80)
		{
			Text_2_0->SetText(FText::FromString("B"));
		}
		else if (ADodgeballPlayerController::S3R2Arr[1] >= 60)
		{
			Text_2_0->SetText(FText::FromString("C"));
		}
		else if (ADodgeballPlayerController::S3R2Arr[1] >= 40)
		{
			Text_2_0->SetText(FText::FromString("D"));
		}
		else if (ADodgeballPlayerController::S3R2Arr[1] >= 20)
		{
			Text_2_0->SetText(FText::FromString("E"));
		}
		else if (ADodgeballPlayerController::S3R2Arr[1] >= 0)
		{
			Text_2_0->SetText(FText::FromString("F"));
		}
		else
		{
			Text_2_0->SetText(FText::FromString("G"));
		}

		FString NewString = FString::FromInt(ADodgeballPlayerController::S3R2Arr[1]);
		FText InText = FText::FromString(NewString);
		Text_2_1->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S3R2Arr[2]);
		InText = FText::FromString(NewString);
		Text_2_2->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S3R2Arr[3]);
		InText = FText::FromString(NewString);
		Text_2_3->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S3R2Arr[4]);
		InText = FText::FromString(NewString);
		Text_2_4->SetText(InText);
	}
	else
	{
		Text_2_0->SetText(FText::FromString(" "));
		Text_2_1->SetText(FText::FromString(" "));
		Text_2_2->SetText(FText::FromString(" "));
		Text_2_3->SetText(FText::FromString(" "));
		Text_2_4->SetText(FText::FromString(" "));
	}

	if (ADodgeballPlayerController::S3R3Arr[0] > 1) // 기록이 있으면
	{
		if (ADodgeballPlayerController::S3R3Arr[1] >= 160)
		{
			Text_3_0->SetText(FText::FromString("S"));
		}
		else if (ADodgeballPlayerController::S3R3Arr[1] >= 130)
		{
			Text_3_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S3R3Arr[1] >= 100)
		{
			Text_3_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S3R3Arr[1] >= 80)
		{
			Text_3_0->SetText(FText::FromString("B"));
		}
		else if (ADodgeballPlayerController::S3R3Arr[1] >= 60)
		{
			Text_3_0->SetText(FText::FromString("C"));
		}
		else if (ADodgeballPlayerController::S3R3Arr[1] >= 40)
		{
			Text_3_0->SetText(FText::FromString("D"));
		}
		else if (ADodgeballPlayerController::S3R3Arr[1] >= 20)
		{
			Text_3_0->SetText(FText::FromString("E"));
		}
		else if (ADodgeballPlayerController::S3R3Arr[1] >= 0)
		{
			Text_3_0->SetText(FText::FromString("F"));
		}
		else
		{
			Text_3_0->SetText(FText::FromString("G"));
		}

		FString NewString = FString::FromInt(ADodgeballPlayerController::S3R3Arr[1]);
		FText InText = FText::FromString(NewString);
		Text_3_1->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S3R3Arr[2]);
		InText = FText::FromString(NewString);
		Text_3_2->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S3R3Arr[3]);
		InText = FText::FromString(NewString);
		Text_3_3->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S3R3Arr[4]);
		InText = FText::FromString(NewString);
		Text_3_4->SetText(InText);
	}
	else
	{
		Text_3_0->SetText(FText::FromString(" "));
		Text_3_1->SetText(FText::FromString(" "));
		Text_3_2->SetText(FText::FromString(" "));
		Text_3_3->SetText(FText::FromString(" "));
		Text_3_4->SetText(FText::FromString(" "));
	}

	RankStage->SetText(FText::FromString("STAGE 3"));
}

void URankWidget::OnStage4Clicked()
{
	if (ADodgeballPlayerController::S4R1Arr[0] > 1) // 기록이 있으면
	{
		if (ADodgeballPlayerController::S4R1Arr[1] >= 160)
		{
			Text_1_0->SetText(FText::FromString("S"));
		}
		else if (ADodgeballPlayerController::S4R1Arr[1] >= 130)
		{
			Text_1_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S4R1Arr[1] >= 100)
		{
			Text_1_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S4R1Arr[1] >= 80)
		{
			Text_1_0->SetText(FText::FromString("B"));
		}
		else if (ADodgeballPlayerController::S4R1Arr[1] >= 60)
		{
			Text_1_0->SetText(FText::FromString("C"));
		}
		else if (ADodgeballPlayerController::S4R1Arr[1] >= 40)
		{
			Text_1_0->SetText(FText::FromString("D"));
		}
		else if (ADodgeballPlayerController::S4R1Arr[1] >= 20)
		{
			Text_1_0->SetText(FText::FromString("E"));
		}
		else if (ADodgeballPlayerController::S4R1Arr[1] >= 0)
		{
			Text_1_0->SetText(FText::FromString("F"));
		}
		else
		{
			Text_1_0->SetText(FText::FromString("G"));
		}

		FString NewString = FString::FromInt(ADodgeballPlayerController::S4R1Arr[1]);
		FText InText = FText::FromString(NewString);
		Text_1_1->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S4R1Arr[2]);
		InText = FText::FromString(NewString);
		Text_1_2->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S4R1Arr[3]);
		InText = FText::FromString(NewString);
		Text_1_3->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S4R1Arr[4]);
		InText = FText::FromString(NewString);
		Text_1_4->SetText(InText);
	}
	else
	{
		Text_1_0->SetText(FText::FromString(" "));
		Text_1_1->SetText(FText::FromString(" "));
		Text_1_2->SetText(FText::FromString(" "));
		Text_1_3->SetText(FText::FromString(" "));
		Text_1_4->SetText(FText::FromString(" "));
	}

	if (ADodgeballPlayerController::S4R2Arr[0] > 1) // 기록이 있으면
	{
		if (ADodgeballPlayerController::S4R2Arr[1] >= 160)
		{
			Text_2_0->SetText(FText::FromString("S"));
		}
		else if (ADodgeballPlayerController::S4R2Arr[1] >= 130)
		{
			Text_2_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S4R2Arr[1] >= 100)
		{
			Text_2_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S4R2Arr[1] >= 80)
		{
			Text_2_0->SetText(FText::FromString("B"));
		}
		else if (ADodgeballPlayerController::S4R2Arr[1] >= 60)
		{
			Text_2_0->SetText(FText::FromString("C"));
		}
		else if (ADodgeballPlayerController::S4R2Arr[1] >= 40)
		{
			Text_2_0->SetText(FText::FromString("D"));
		}
		else if (ADodgeballPlayerController::S4R2Arr[1] >= 20)
		{
			Text_2_0->SetText(FText::FromString("E"));
		}
		else if (ADodgeballPlayerController::S4R2Arr[1] >= 0)
		{
			Text_2_0->SetText(FText::FromString("F"));
		}
		else
		{
			Text_2_0->SetText(FText::FromString("G"));
		}

		FString NewString = FString::FromInt(ADodgeballPlayerController::S4R2Arr[1]);
		FText InText = FText::FromString(NewString);
		Text_2_1->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S4R2Arr[2]);
		InText = FText::FromString(NewString);
		Text_2_2->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S4R2Arr[3]);
		InText = FText::FromString(NewString);
		Text_2_3->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S4R2Arr[4]);
		InText = FText::FromString(NewString);
		Text_2_4->SetText(InText);
	}
	else
	{
		Text_2_0->SetText(FText::FromString(" "));
		Text_2_1->SetText(FText::FromString(" "));
		Text_2_2->SetText(FText::FromString(" "));
		Text_2_3->SetText(FText::FromString(" "));
		Text_2_4->SetText(FText::FromString(" "));
	}

	if (ADodgeballPlayerController::S4R3Arr[0] > 1) // 기록이 있으면
	{
		if (ADodgeballPlayerController::S4R3Arr[1] >= 160)
		{
			Text_3_0->SetText(FText::FromString("S"));
		}
		else if (ADodgeballPlayerController::S4R3Arr[1] >= 130)
		{
			Text_3_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S4R3Arr[1] >= 100)
		{
			Text_3_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S4R3Arr[1] >= 80)
		{
			Text_3_0->SetText(FText::FromString("B"));
		}
		else if (ADodgeballPlayerController::S4R3Arr[1] >= 60)
		{
			Text_3_0->SetText(FText::FromString("C"));
		}
		else if (ADodgeballPlayerController::S4R3Arr[1] >= 40)
		{
			Text_3_0->SetText(FText::FromString("D"));
		}
		else if (ADodgeballPlayerController::S4R3Arr[1] >= 20)
		{
			Text_3_0->SetText(FText::FromString("E"));
		}
		else if (ADodgeballPlayerController::S4R3Arr[1] >= 0)
		{
			Text_3_0->SetText(FText::FromString("F"));
		}
		else
		{
			Text_3_0->SetText(FText::FromString("G"));
		}

		FString NewString = FString::FromInt(ADodgeballPlayerController::S4R3Arr[1]);
		FText InText = FText::FromString(NewString);
		Text_3_1->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S4R3Arr[2]);
		InText = FText::FromString(NewString);
		Text_3_2->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S4R3Arr[3]);
		InText = FText::FromString(NewString);
		Text_3_3->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S4R3Arr[4]);
		InText = FText::FromString(NewString);
		Text_3_4->SetText(InText);
	}
	else
	{
		Text_3_0->SetText(FText::FromString(" "));
		Text_3_1->SetText(FText::FromString(" "));
		Text_3_2->SetText(FText::FromString(" "));
		Text_3_3->SetText(FText::FromString(" "));
		Text_3_4->SetText(FText::FromString(" "));
	}

	RankStage->SetText(FText::FromString("STAGE 4"));
}

void URankWidget::OnStage5Clicked()
{
	if (ADodgeballPlayerController::S5R1Arr[0] > 1) // 기록이 있으면
	{
		if (ADodgeballPlayerController::S5R1Arr[1] >= 160)
		{
			Text_1_0->SetText(FText::FromString("S"));
		}
		else if (ADodgeballPlayerController::S5R1Arr[1] >= 130)
		{
			Text_1_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S5R1Arr[1] >= 100)
		{
			Text_1_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S5R1Arr[1] >= 80)
		{
			Text_1_0->SetText(FText::FromString("B"));
		}
		else if (ADodgeballPlayerController::S5R1Arr[1] >= 60)
		{
			Text_1_0->SetText(FText::FromString("C"));
		}
		else if (ADodgeballPlayerController::S5R1Arr[1] >= 40)
		{
			Text_1_0->SetText(FText::FromString("D"));
		}
		else if (ADodgeballPlayerController::S5R1Arr[1] >= 20)
		{
			Text_1_0->SetText(FText::FromString("E"));
		}
		else if (ADodgeballPlayerController::S5R1Arr[1] >= 0)
		{
			Text_1_0->SetText(FText::FromString("F"));
		}
		else
		{
			Text_1_0->SetText(FText::FromString("G"));
		}

		FString NewString = FString::FromInt(ADodgeballPlayerController::S5R1Arr[1]);
		FText InText = FText::FromString(NewString);
		Text_1_1->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S5R1Arr[2]);
		InText = FText::FromString(NewString);
		Text_1_2->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S5R1Arr[3]);
		InText = FText::FromString(NewString);
		Text_1_3->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S5R1Arr[4]);
		InText = FText::FromString(NewString);
		Text_1_4->SetText(InText);
	}
	else
	{
		Text_1_0->SetText(FText::FromString(" "));
		Text_1_1->SetText(FText::FromString(" "));
		Text_1_2->SetText(FText::FromString(" "));
		Text_1_3->SetText(FText::FromString(" "));
		Text_1_4->SetText(FText::FromString(" "));
	}

	if (ADodgeballPlayerController::S5R2Arr[0] > 1) // 기록이 있으면
	{
		if (ADodgeballPlayerController::S5R2Arr[1] >= 160)
		{
			Text_2_0->SetText(FText::FromString("S"));
		}
		else if (ADodgeballPlayerController::S5R2Arr[1] >= 130)
		{
			Text_2_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S5R2Arr[1] >= 100)
		{
			Text_2_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S5R2Arr[1] >= 80)
		{
			Text_2_0->SetText(FText::FromString("B"));
		}
		else if (ADodgeballPlayerController::S5R2Arr[1] >= 60)
		{
			Text_2_0->SetText(FText::FromString("C"));
		}
		else if (ADodgeballPlayerController::S5R2Arr[1] >= 40)
		{
			Text_2_0->SetText(FText::FromString("D"));
		}
		else if (ADodgeballPlayerController::S5R2Arr[1] >= 20)
		{
			Text_2_0->SetText(FText::FromString("E"));
		}
		else if (ADodgeballPlayerController::S5R2Arr[1] >= 0)
		{
			Text_2_0->SetText(FText::FromString("F"));
		}
		else
		{
			Text_2_0->SetText(FText::FromString("G"));
		}

		FString NewString = FString::FromInt(ADodgeballPlayerController::S5R2Arr[1]);
		FText InText = FText::FromString(NewString);
		Text_2_1->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S5R2Arr[2]);
		InText = FText::FromString(NewString);
		Text_2_2->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S5R2Arr[3]);
		InText = FText::FromString(NewString);
		Text_2_3->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S5R2Arr[4]);
		InText = FText::FromString(NewString);
		Text_2_4->SetText(InText);
	}
	else
	{
		Text_2_0->SetText(FText::FromString(" "));
		Text_2_1->SetText(FText::FromString(" "));
		Text_2_2->SetText(FText::FromString(" "));
		Text_2_3->SetText(FText::FromString(" "));
		Text_2_4->SetText(FText::FromString(" "));
	}

	if (ADodgeballPlayerController::S5R3Arr[0] > 1) // 기록이 있으면
	{
		if (ADodgeballPlayerController::S5R3Arr[1] >= 160)
		{
			Text_3_0->SetText(FText::FromString("S"));
		}
		else if (ADodgeballPlayerController::S5R3Arr[1] >= 130)
		{
			Text_3_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S5R3Arr[1] >= 100)
		{
			Text_3_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S5R3Arr[1] >= 80)
		{
			Text_3_0->SetText(FText::FromString("B"));
		}
		else if (ADodgeballPlayerController::S5R3Arr[1] >= 60)
		{
			Text_3_0->SetText(FText::FromString("C"));
		}
		else if (ADodgeballPlayerController::S5R3Arr[1] >= 40)
		{
			Text_3_0->SetText(FText::FromString("D"));
		}
		else if (ADodgeballPlayerController::S5R3Arr[1] >= 20)
		{
			Text_3_0->SetText(FText::FromString("E"));
		}
		else if (ADodgeballPlayerController::S5R3Arr[1] >= 0)
		{
			Text_3_0->SetText(FText::FromString("F"));
		}
		else
		{
			Text_3_0->SetText(FText::FromString("G"));
		}

		FString NewString = FString::FromInt(ADodgeballPlayerController::S5R3Arr[1]);
		FText InText = FText::FromString(NewString);
		Text_3_1->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S5R3Arr[2]);
		InText = FText::FromString(NewString);
		Text_3_2->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S5R3Arr[3]);
		InText = FText::FromString(NewString);
		Text_3_3->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S5R3Arr[4]);
		InText = FText::FromString(NewString);
		Text_3_4->SetText(InText);
	}
	else
	{
		Text_3_0->SetText(FText::FromString(" "));
		Text_3_1->SetText(FText::FromString(" "));
		Text_3_2->SetText(FText::FromString(" "));
		Text_3_3->SetText(FText::FromString(" "));
		Text_3_4->SetText(FText::FromString(" "));
	}

	RankStage->SetText(FText::FromString("STAGE 5"));
}

void URankWidget::EnterRankingUI()
{
	if (ADodgeballPlayerController::S1R1Arr[0] > 1) // 기록이 있으면
	{
		if (ADodgeballPlayerController::S1R1Arr[1] >= 160)
		{
			Text_1_0->SetText(FText::FromString("S"));
		}
		else if (ADodgeballPlayerController::S1R1Arr[1] >= 130)
		{
			Text_1_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S1R1Arr[1] >= 100)
		{
			Text_1_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S1R1Arr[1] >= 80)
		{
			Text_1_0->SetText(FText::FromString("B"));
		}
		else if (ADodgeballPlayerController::S1R1Arr[1] >= 60)
		{
			Text_1_0->SetText(FText::FromString("C"));
		}
		else if (ADodgeballPlayerController::S1R1Arr[1] >= 40)
		{
			Text_1_0->SetText(FText::FromString("D"));
		}
		else if (ADodgeballPlayerController::S1R1Arr[1] >= 20)
		{
			Text_1_0->SetText(FText::FromString("E"));
		}
		else if (ADodgeballPlayerController::S1R1Arr[1] >= 0)
		{
			Text_1_0->SetText(FText::FromString("F"));
		}
		else
		{
			Text_1_0->SetText(FText::FromString("G"));
		}

		FString NewString = FString::FromInt(ADodgeballPlayerController::S1R1Arr[1]);
		FText InText = FText::FromString(NewString);
		Text_1_1->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S1R1Arr[2]);
		InText = FText::FromString(NewString);
		Text_1_2->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S1R1Arr[3]);
		InText = FText::FromString(NewString);
		Text_1_3->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S1R1Arr[4]);
		InText = FText::FromString(NewString);
		Text_1_4->SetText(InText);
	}
	else
	{
		Text_1_0->SetText(FText::FromString(" "));
		Text_1_1->SetText(FText::FromString(" "));
		Text_1_2->SetText(FText::FromString(" "));
		Text_1_3->SetText(FText::FromString(" "));
		Text_1_4->SetText(FText::FromString(" "));
	}

	if (ADodgeballPlayerController::S1R2Arr[0] > 1) // 기록이 있으면
	{
		if (ADodgeballPlayerController::S1R2Arr[1] >= 160)
		{
			Text_2_0->SetText(FText::FromString("S"));
		}
		else if (ADodgeballPlayerController::S1R2Arr[1] >= 130)
		{
			Text_2_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S1R2Arr[1] >= 100)
		{
			Text_2_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S1R2Arr[1] >= 80)
		{
			Text_2_0->SetText(FText::FromString("B"));
		}
		else if (ADodgeballPlayerController::S1R2Arr[1] >= 60)
		{
			Text_2_0->SetText(FText::FromString("C"));
		}
		else if (ADodgeballPlayerController::S1R2Arr[1] >= 40)
		{
			Text_2_0->SetText(FText::FromString("D"));
		}
		else if (ADodgeballPlayerController::S1R2Arr[1] >= 20)
		{
			Text_2_0->SetText(FText::FromString("E"));
		}
		else if (ADodgeballPlayerController::S1R2Arr[1] >= 0)
		{
			Text_2_0->SetText(FText::FromString("F"));
		}
		else
		{
			Text_2_0->SetText(FText::FromString("G"));
		}

		FString NewString = FString::FromInt(ADodgeballPlayerController::S1R2Arr[1]);
		FText InText = FText::FromString(NewString);
		Text_2_1->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S1R2Arr[2]);
		InText = FText::FromString(NewString);
		Text_2_2->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S1R2Arr[3]);
		InText = FText::FromString(NewString);
		Text_2_3->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S1R2Arr[4]);
		InText = FText::FromString(NewString);
		Text_2_4->SetText(InText);
	}
	else
	{
		Text_2_0->SetText(FText::FromString(" "));
		Text_2_1->SetText(FText::FromString(" "));
		Text_2_2->SetText(FText::FromString(" "));
		Text_2_3->SetText(FText::FromString(" "));
		Text_2_4->SetText(FText::FromString(" "));
	}

	if (ADodgeballPlayerController::S1R3Arr[0] > 1) // 기록이 있으면
	{
		if (ADodgeballPlayerController::S1R3Arr[1] >= 160)
		{
			Text_3_0->SetText(FText::FromString("S"));
		}
		else if (ADodgeballPlayerController::S1R3Arr[1] >= 130)
		{
			Text_3_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S1R3Arr[1] >= 100)
		{
			Text_3_0->SetText(FText::FromString("A"));
		}
		else if (ADodgeballPlayerController::S1R3Arr[1] >= 80)
		{
			Text_3_0->SetText(FText::FromString("B"));
		}
		else if (ADodgeballPlayerController::S1R3Arr[1] >= 60)
		{
			Text_3_0->SetText(FText::FromString("C"));
		}
		else if (ADodgeballPlayerController::S1R3Arr[1] >= 40)
		{
			Text_3_0->SetText(FText::FromString("D"));
		}
		else if (ADodgeballPlayerController::S1R3Arr[1] >= 20)
		{
			Text_3_0->SetText(FText::FromString("E"));
		}
		else if (ADodgeballPlayerController::S1R3Arr[1] >= 0)
		{
			Text_3_0->SetText(FText::FromString("F"));
		}
		else
		{
			Text_3_0->SetText(FText::FromString("G"));
		}

		FString NewString = FString::FromInt(ADodgeballPlayerController::S1R3Arr[1]);
		FText InText = FText::FromString(NewString);
		Text_3_1->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S1R3Arr[2]);
		InText = FText::FromString(NewString);
		Text_3_2->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S1R3Arr[3]);
		InText = FText::FromString(NewString);
		Text_3_3->SetText(InText);
		NewString = FString::FromInt(ADodgeballPlayerController::S1R3Arr[4]);
		InText = FText::FromString(NewString);
		Text_3_4->SetText(InText);
	}
	else
	{
		Text_3_0->SetText(FText::FromString(" "));
		Text_3_1->SetText(FText::FromString(" "));
		Text_3_2->SetText(FText::FromString(" "));
		Text_3_3->SetText(FText::FromString(" "));
		Text_3_4->SetText(FText::FromString(" "));
	}

	RankStage->SetText(FText::FromString("STAGE 1"));
}

void URankWidget::OnRankoffClicked()
{
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HideRankWidget();
		PlayerController->ShowMainMenuWidget();
	}
}
