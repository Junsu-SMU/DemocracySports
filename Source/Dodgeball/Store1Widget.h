// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Store1Widget.generated.h"

/**
 * 
 */
UCLASS()
class DODGEBALL_API UStore1Widget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UFUNCTION()
		void OnAbility1Clicked();

	UFUNCTION()
		void OnAbility2Clicked();

	UFUNCTION()
		void OnAbility3Clicked();

	UFUNCTION()
		void OnBuyClicked();

	UFUNCTION()
		void OnOutClicked();

	UFUNCTION()
		void OnItem1Clicked();

	UFUNCTION()
		void OnItem2Clicked();

	UFUNCTION()
		void OnItem3Clicked();

	int Selected = 0;

public:

	virtual void NativeOnInitialized() override;

	void UpdateGold(int Gold);

	UPROPERTY(meta = (BindWidget))
		class UButton* Ability1Button;

	UPROPERTY(meta = (BindWidget))
		class UButton* Ability2Button;

	UPROPERTY(meta = (BindWidget))
		class UButton* Ability3Button;

	UPROPERTY(meta = (BindWidget))
		class UButton* BuyButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* OutButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* Item1Button;

	UPROPERTY(meta = (BindWidget))
		class UButton* Item2Button;

	UPROPERTY(meta = (BindWidget))
		class UButton* Item3Button;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* InCash;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Statetext;

	UPROPERTY(meta = (BindWidget))
		class UImage* ItemLock1;

	UPROPERTY(meta = (BindWidget))
		class UImage* ItemLock2;

	UPROPERTY(meta = (BindWidget))
		class UImage* ItemLock3;
	
};
