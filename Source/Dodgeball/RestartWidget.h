// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RestartWidget.generated.h"

/**
 *
 */
UCLASS()
class DODGEBALL_API URestartWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UFUNCTION()
		void OnRestartClicked();

	UFUNCTION()
		void OnExitClicked();

private:


public:

	virtual void NativeOnInitialized() override;

	void UpdateHealth(float Health);
	void UpdateGold(int Gold);
	void UpdateStage(int Stage);
	void UpdateTime(float Time, float Minute);

	UPROPERTY(meta = (BindWidget))
		class UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* ExitButton;

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

};
