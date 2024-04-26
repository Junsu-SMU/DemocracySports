// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "M1Object.generated.h"

UCLASS()
class DODGEBALL_API AM1Object : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* CapsuleComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* M1touchSound1;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* M1touchSound2;

public:
	AM1Object();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static int M1Count;
	static bool M1delete;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, // OnHIt ÇÔ¼ö
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpulse,
			const FHitResult& Hit);

};
