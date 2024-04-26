// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DodgeballProjectile.generated.h"

UCLASS()
class DODGEBALL_API ADodgeballProjectile : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

protected:

	virtual void BeginPlay() override;

	// The damage the dodgeball will deal to the player's character
	UPROPERTY(EditAnywhere, Category = Damage)
		float Damage = 10.f; // 대미지 10

	UPROPERTY(EditAnywhere, Category = VoteDown)
		float VoteDown = 1.f; // 투표율감소 1

	// The sound the dodgeball will make when it hits the player
	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* DamageSound;

public:

	ADodgeballProjectile();

	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UProjectileMovementComponent* GetProjectileMovementComponent() const
	{
		return ProjectileMovement;
	}

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, // OnHIt 함수
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpulse,
			const FHitResult& Hit);
};
