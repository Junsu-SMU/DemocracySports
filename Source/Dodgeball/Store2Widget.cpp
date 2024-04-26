// Fill out your copyright notice in the Description page of Project Settings.


#include "Store2Widget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "DodgeballPlayerController.h"
#include "DodgeballCharacter.h"

void UStore2Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Ability1Button != nullptr)
	{
		Ability1Button->OnClicked.AddDynamic(this, &UStore2Widget::OnAbility1Clicked);
	}

	if (Ability2Button != nullptr)
	{
		Ability2Button->OnClicked.AddDynamic(this, &UStore2Widget::OnAbility2Clicked);
	}

	if (Ability3Button != nullptr)
	{
		Ability3Button->OnClicked.AddDynamic(this, &UStore2Widget::OnAbility3Clicked);
	}

	if (Item4Button != nullptr)
	{
		Item4Button->OnClicked.AddDynamic(this, &UStore2Widget::OnItem4Clicked);
	}

	if (Item5Button != nullptr)
	{
		Item5Button->OnClicked.AddDynamic(this, &UStore2Widget::OnItem5Clicked);
	}

	if (Item6Button != nullptr)
	{
		Item6Button->OnClicked.AddDynamic(this, &UStore2Widget::OnItem6Clicked);
	}

	if (BuyButton != nullptr)
	{
		BuyButton->OnClicked.AddDynamic(this, &UStore2Widget::OnBuyClicked);
	}

	if (OutButton != nullptr)
	{
		OutButton->OnClicked.AddDynamic(this, &UStore2Widget::OnOutClicked);
	}

	if (ADodgeballCharacter::buyitem4 == true)
	{
		Item4Button->SetVisibility(ESlateVisibility::Collapsed);
		ItemLock4->SetVisibility(ESlateVisibility::Visible);
	}

	if (ADodgeballCharacter::buyitem5 == true)
	{
		Item5Button->SetVisibility(ESlateVisibility::Collapsed);
		ItemLock5->SetVisibility(ESlateVisibility::Visible);
	}

	if (ADodgeballCharacter::buyitem6 == true)
	{
		Item6Button->SetVisibility(ESlateVisibility::Collapsed);
		ItemLock6->SetVisibility(ESlateVisibility::Visible);
	}

}

void UStore2Widget::UpdateGold(int Gold)
{
	FString NewString = FString::FromInt(Gold);
	FText InText = FText::FromString(NewString);
	InCash->SetText(InText);
}

void UStore2Widget::OnAbility1Clicked()
{
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HideStore1Widget();
		PlayerController->HideStore2Widget();
		PlayerController->HideStore3Widget();
		PlayerController->ShowStore1Widget();
	}
}

void UStore2Widget::OnAbility2Clicked()
{
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HideStore1Widget();
		PlayerController->HideStore2Widget();
		PlayerController->HideStore3Widget();
		PlayerController->ShowStore2Widget();
	}
}

void UStore2Widget::OnAbility3Clicked()
{
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HideStore1Widget();
		PlayerController->HideStore2Widget();
		PlayerController->HideStore3Widget();
		PlayerController->ShowStore3Widget();
	}
}

void UStore2Widget::OnItem4Clicked() // 빈도수 2.5 > 3.5
{
	Selected = 4;
	//FText InText = FText::FromString("언론 매수 : 미션4에서 시위대 등장 빈도 수가 줄어듭니다.");
	Statetext->SetText(FText::FromString("Difficulty of Mission4 becomes easy."));
}

void UStore2Widget::OnItem5Clicked() // 성공 조건 7.5 > 5
{
	Selected = 5;
	//FText InText = FText::FromString("화려한 조명 : 미션3에서 성공 조건이 쉬워집니다.");
	Statetext->SetText(FText::FromString("Difficulty of Mission3 becomes easy."));
}

void UStore2Widget::OnItem6Clicked() // 생명력 10 회복
{
	Selected = 6;
	//FText InText = FText::FromString("복지 정책 : 미션1,2를 성공 시 생명력을 회복합니다.");
	Statetext->SetText(FText::FromString("Recover your health when cleared Mission1,2."));
}

void UStore2Widget::OnBuyClicked()
{
	if (ADodgeballPlayerController::Gold >= 1000)
	{
		if (Selected == 4)
		{
			ADodgeballCharacter::M4cooltime = 3.5f;
			ADodgeballCharacter::buyitem4 = true;
			Item4Button->SetVisibility(ESlateVisibility::Collapsed);
			ItemLock4->SetVisibility(ESlateVisibility::Visible);
		}
		else if (Selected == 5)
		{
			ADodgeballCharacter::M3cleartime = 5.f;
			ADodgeballCharacter::buyitem5 = true;
			Item5Button->SetVisibility(ESlateVisibility::Collapsed);
			ItemLock5->SetVisibility(ESlateVisibility::Visible);
		}
		else if (Selected == 6)
		{
			ADodgeballCharacter::M1M2buff = true;
			ADodgeballCharacter::buyitem6 = true;
			Item6Button->SetVisibility(ESlateVisibility::Collapsed);
			ItemLock6->SetVisibility(ESlateVisibility::Visible);
		}
		ADodgeballPlayerController::Gold -= 1000;
		UpdateGold(ADodgeballPlayerController::Gold);
		Statetext->SetText(FText::FromString("You succeed to buy the Ability."));
	}
	else
	{
		Statetext->SetText(FText::FromString("You don't have enough money."));
	}
}

void UStore2Widget::OnOutClicked()
{
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HideStore2Widget();
		PlayerController->ShowMainMenuWidget();
	}
}
