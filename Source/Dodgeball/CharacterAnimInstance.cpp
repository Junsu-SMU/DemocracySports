// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"
#include "HealthComponent.h"
#include "DodgeballCharacter.h"
#include "DodgeballPlayerController.h"
#include "EngineUtils.h"




void UCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Switch = false;
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	for (TActorIterator<ADodgeballCharacter> Iter(GetWorld()); Iter; ++Iter) // ���忡 �ִ� DodgeballCharacter ã��
	{
		ADodgeballCharacter* Player = *Iter; // Player ������ DodgeballCharacter ���

		if (Player != nullptr)
		{
			UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();
			if (HealthComponent != nullptr)
			{
				float x = 100 * (HealthComponent->GetVotePercent());
				if (x <= ADodgeballCharacter::neutralchangebuff)
				{
					Switch = true;
				}
				else
				{
					Switch = false;
				}
			}
		}
	}


}

