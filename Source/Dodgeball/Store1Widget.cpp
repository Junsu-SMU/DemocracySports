// Fill out your copyright notice in the Description page of Project Settings.


#include "Store1Widget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "DodgeballPlayerController.h"
#include "DodgeballCharacter.h"

void UStore1Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Ability1Button != nullptr)
	{
		Ability1Button->OnClicked.AddDynamic(this, &UStore1Widget::OnAbility1Clicked);
	}

	if (Ability2Button != nullptr)
	{
		Ability2Button->OnClicked.AddDynamic(this, &UStore1Widget::OnAbility2Clicked);
	}

	if (Ability3Button != nullptr)
	{
		Ability3Button->OnClicked.AddDynamic(this, &UStore1Widget::OnAbility3Clicked);
	}

	if (Item1Button != nullptr)
	{
		Item1Button->OnClicked.AddDynamic(this, &UStore1Widget::OnItem1Clicked);
	}

	if (Item2Button != nullptr)
	{
		Item2Button->OnClicked.AddDynamic(this, &UStore1Widget::OnItem2Clicked);
	}

	if (Item3Button != nullptr)
	{
		Item3Button->OnClicked.AddDynamic(this, &UStore1Widget::OnItem3Clicked);
	}

	if (BuyButton != nullptr)
	{
		BuyButton->OnClicked.AddDynamic(this, &UStore1Widget::OnBuyClicked);
	}

	if (OutButton != nullptr)
	{
		OutButton->OnClicked.AddDynamic(this, &UStore1Widget::OnOutClicked);
	}

	if (ADodgeballCharacter::buyitem1 == true)
	{
		Item1Button->SetVisibility(ESlateVisibility::Collapsed);
		ItemLock1->SetVisibility(ESlateVisibility::Visible);
	}

	if (ADodgeballCharacter::buyitem2 == true)
	{
		Item2Button->SetVisibility(ESlateVisibility::Collapsed);
		ItemLock2->SetVisibility(ESlateVisibility::Visible);
	}

	if (ADodgeballCharacter::buyitem3 == true)
	{
		Item3Button->SetVisibility(ESlateVisibility::Collapsed);
		ItemLock3->SetVisibility(ESlateVisibility::Visible);
	}

}

void UStore1Widget::UpdateGold(int Gold)
{
	FString NewString = FString::FromInt(Gold);
	FText InText = FText::FromString(NewString);
	InCash->SetText(InText);
}

void UStore1Widget::OnAbility1Clicked()
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

void UStore1Widget::OnAbility2Clicked()
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

void UStore1Widget::OnAbility3Clicked()
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

void UStore1Widget::OnItem1Clicked() // 생명력 100 > 150
{
	Selected = 1;
	//FText InText = FText::FromString("정치 생명 : 최대 생명력이 상승합니다.");
	Statetext->SetText(FText::FromString("Max Health increased 50%."));
}

void UStore1Widget::OnItem2Clicked() // 기본 이속 600 > 720
{
	Selected = 2;
	//FText InText = FText::FromString("처세술 : 기본 이동속도가 상승합니다.");
	Statetext->SetText(FText::FromString("Max Speed increased 20%."));
}

void UStore1Widget::OnItem3Clicked() // 슬라이딩 쿨타임 5초 > 4초
{
	Selected = 3;
	//FText InText = FText::FromString("오버 액션 : 슬라이딩 쿨타임이 줄어듭니다.");
	Statetext->SetText(FText::FromString("Sliding cooltime decreased 20%."));
}

void UStore1Widget::OnBuyClicked()
{
	if (ADodgeballPlayerController::Gold >= 1000)
	{
		if (Selected == 1)
		{
			ADodgeballCharacter::playerhp = 150.f;
			ADodgeballCharacter::buyitem1 = true;
			Item1Button->SetVisibility(ESlateVisibility::Collapsed);
			ItemLock1->SetVisibility(ESlateVisibility::Visible);
		}
		else if (Selected == 2)
		{
			ADodgeballCharacter::playerspeed = 720.f;
			ADodgeballCharacter::buyitem2 = true;
			Item2Button->SetVisibility(ESlateVisibility::Collapsed);
			ItemLock2->SetVisibility(ESlateVisibility::Visible);
		}
		else if (Selected == 3)
		{
			ADodgeballCharacter::playercooltime = 4.f;
			ADodgeballCharacter::buyitem3 = true;
			Item3Button->SetVisibility(ESlateVisibility::Collapsed);
			ItemLock3->SetVisibility(ESlateVisibility::Visible);
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

void UStore1Widget::OnOutClicked()
{
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HideStore1Widget();
		PlayerController->ShowMainMenuWidget();
	}
}
