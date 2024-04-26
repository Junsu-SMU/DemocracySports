// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClearWidget.generated.h"

/**
 *
 */
UCLASS()
class DODGEBALL_API UClearWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UFUNCTION()
		void OnNextLevelClicked();

	UFUNCTION()
		void OnRestartClicked();

	UFUNCTION()
		void OnExitClicked();

private:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		FString Level2;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		FString Level3;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		FString Level4;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		FString Level5;

public:

	virtual void NativeOnInitialized() override;

	void UpdateHealth(float Health);
	void UpdateGold(int Gold);
	void UpdateStage(int Stage);
	void UpdateTime(float Time, float Minute);
	void UpdateRank(float Score);

	UPROPERTY(meta = (BindWidget))
		class UButton* NextLevelButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* ExitButton;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Ranktext;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* GetCointext;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Stagetext;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Healthtext;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Timetext;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Minutetext;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* RankScore;

};
