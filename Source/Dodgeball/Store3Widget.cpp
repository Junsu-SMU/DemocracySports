// Fill out your copyright notice in the Description page of Project Settings.


#include "Store3Widget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "DodgeballPlayerController.h"
#include "DodgeballCharacter.h"

void UStore3Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Ability1Button != nullptr)
	{
		Ability1Button->OnClicked.AddDynamic(this, &UStore3Widget::OnAbility1Clicked);
	}

	if (Ability2Button != nullptr)
	{
		Ability2Button->OnClicked.AddDynamic(this, &UStore3Widget::OnAbility2Clicked);
	}

	if (Ability3Button != nullptr)
	{
		Ability3Button->OnClicked.AddDynamic(this, &UStore3Widget::OnAbility3Clicked);
	}

	if (Item7Button != nullptr)
	{
		Item7Button->OnClicked.AddDynamic(this, &UStore3Widget::OnItem7Clicked);
	}

	if (Item8Button != nullptr)
	{
		Item8Button->OnClicked.AddDynamic(this, &UStore3Widget::OnItem8Clicked);
	}

	if (Item9Button != nullptr)
	{
		Item9Button->OnClicked.AddDynamic(this, &UStore3Widget::OnItem9Clicked);
	}

	if (BuyButton != nullptr)
	{
		BuyButton->OnClicked.AddDynamic(this, &UStore3Widget::OnBuyClicked);
	}

	if (OutButton != nullptr)
	{
		OutButton->OnClicked.AddDynamic(this, &UStore3Widget::OnOutClicked);
	}

	if (ADodgeballCharacter::buyitem7 == true)
	{
		Item7Button->SetVisibility(ESlateVisibility::Collapsed);
		ItemLock7->SetVisibility(ESlateVisibility::Visible);
	}

	if (ADodgeballCharacter::buyitem8 == true)
	{
		Item8Button->SetVisibility(ESlateVisibility::Collapsed);
		ItemLock8->SetVisibility(ESlateVisibility::Visible);
	}

	if (ADodgeballCharacter::buyitem9 == true)
	{
		Item9Button->SetVisibility(ESlateVisibility::Collapsed);
		ItemLock9->SetVisibility(ESlateVisibility::Visible);
	}

}

void UStore3Widget::UpdateGold(int Gold)
{
	FString NewString = FString::FromInt(Gold);
	FText InText = FText::FromString(NewString);
	InCash->SetText(InText);
}

void UStore3Widget::OnAbility1Clicked()
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

void UStore3Widget::OnAbility2Clicked()
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

void UStore3Widget::OnAbility3Clicked()
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

void UStore3Widget::OnItem7Clicked() // 함정 사라지는 속도 10 > 8
{
	Selected = 7;
	//FText InText = FText::FromString("환경 미화 : 함정이 사라지는 속도가 빨라집니다.");
	Statetext->SetText(FText::FromString("Trap duration decreased 20%."));
}

void UStore3Widget::OnItem8Clicked() // 분마다 생명력을 10 회복
{
	Selected = 8;
	//FText InText = FText::FromString("건강 보험 : 1분 마다 생명력을 회복합니다.");
	Statetext->SetText(FText::FromString("Recover your health every minute."));
}

void UStore3Widget::OnItem9Clicked() // 중립 > 적 변하는 조건 지지율 15퍼 > 10퍼
{
	Selected = 9;
	//FText InText = FText::FromString("인맥 관리 : 중립 지지자들이 적대하는 조건이 완화됩니다.");
	Statetext->SetText(FText::FromString("Neutral supporters are more generous."));
}

void UStore3Widget::OnBuyClicked()
{
	if (ADodgeballPlayerController::Gold >= 1000)
	{
		if (Selected == 7)
		{
			ADodgeballCharacter::trapXtime = 8.f;
			ADodgeballCharacter::buyitem7 = true;
			Item7Button->SetVisibility(ESlateVisibility::Collapsed);
			ItemLock7->SetVisibility(ESlateVisibility::Visible);
		}
		else if (Selected == 8)
		{
			ADodgeballCharacter::healperminute = true;
			ADodgeballCharacter::buyitem8 = true;
			Item8Button->SetVisibility(ESlateVisibility::Collapsed);
			ItemLock8->SetVisibility(ESlateVisibility::Visible);
		}
		else if (Selected == 9)
		{
			ADodgeballCharacter::neutralchangebuff = 10.f;
			ADodgeballCharacter::buyitem9 = true;
			Item9Button->SetVisibility(ESlateVisibility::Collapsed);
			ItemLock9->SetVisibility(ESlateVisibility::Visible);
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

void UStore3Widget::OnOutClicked()
{
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HideStore3Widget();
		PlayerController->ShowMainMenuWidget();
	}
}

