// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RankWidget.generated.h"

/**
 * 
 */
UCLASS()
class DODGEBALL_API URankWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UFUNCTION()
		void OnStage1Clicked();

	UFUNCTION()
		void OnStage2Clicked();

	UFUNCTION()
		void OnStage3Clicked();

	UFUNCTION()
		void OnStage4Clicked();

	UFUNCTION()
		void OnStage5Clicked();

	UFUNCTION()
		void OnRankoffClicked();

public:

	virtual void NativeOnInitialized() override;

	void EnterRankingUI();

	UPROPERTY(meta = (BindWidget))
		class UButton* Stage1Button;

	UPROPERTY(meta = (BindWidget))
		class UButton* Stage2Button;

	UPROPERTY(meta = (BindWidget))
		class UButton* Stage3Button;

	UPROPERTY(meta = (BindWidget))
		class UButton* Stage4Button;

	UPROPERTY(meta = (BindWidget))
		class UButton* Stage5Button;

	UPROPERTY(meta = (BindWidget))
		class UButton* RankoffButton;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* RankStage;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_1_0;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_1_1;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_1_2;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_1_3;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_1_4;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_2_0;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_2_1;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_2_2;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_2_3;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_2_4;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_3_0;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_3_1;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_3_2;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_3_3;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_3_4;
	
};
