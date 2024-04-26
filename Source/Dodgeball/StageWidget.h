// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StageWidget.generated.h"

/**
 * 
 */
UCLASS()
class DODGEBALL_API UStageWidget : public UUserWidget
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
		void OnExitClicked();

private:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		FString Level1;
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
		class UButton* ExitButton;
	
};
