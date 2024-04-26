// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Store3Widget.generated.h"

/**
 * 
 */
UCLASS()
class DODGEBALL_API UStore3Widget : public UUserWidget
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
		void OnItem7Clicked();

	UFUNCTION()
		void OnItem8Clicked();

	UFUNCTION()
		void OnItem9Clicked();

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
		class UButton* Item7Button;

	UPROPERTY(meta = (BindWidget))
		class UButton* Item8Button;

	UPROPERTY(meta = (BindWidget))
		class UButton* Item9Button;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* InCash;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Statetext;

	UPROPERTY(meta = (BindWidget))
		class UImage* ItemLock7;

	UPROPERTY(meta = (BindWidget))
		class UImage* ItemLock8;

	UPROPERTY(meta = (BindWidget))
		class UImage* ItemLock9;

};
