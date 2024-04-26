// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 *
 */
UCLASS()
class DODGEBALL_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UFUNCTION()
		void OnPlayClicked();

	UFUNCTION()
		void OnStoreClicked();

	UFUNCTION()
		void OnRankClicked();

	UFUNCTION()
		void OnExitClicked();

public:

	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
		class UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* StoreButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* RankButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* ExitButton;

};
