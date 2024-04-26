// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "M4Object.generated.h"

UCLASS()
class DODGEBALL_API AM4Object : public AActor
{
	GENERATED_BODY()
	
private:	
	// Sets default values for this actor's properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* BoxComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* M4touchSound;

	FRotator FinalRotator;

public:	
	AM4Object();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static bool M4delete;
	static bool M4Count;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, // OnHIt ÇÔ¼ö
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpulse,
			const FHitResult& Hit);

};
