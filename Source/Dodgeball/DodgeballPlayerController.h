// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "DodgeballPlayerController.generated.h"

/**
 *
 */
UCLASS()
class DODGEBALL_API ADodgeballPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class URestartWidget> BP_RestartWidget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UHUDWidget> BP_HUDWidget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UMainMenuWidget> BP_MainMenuWidget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UClearWidget> BP_ClearWidget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class URankWidget> BP_RankWidget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UStore1Widget> BP_Store1Widget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UStore2Widget> BP_Store2Widget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UStore3Widget> BP_Store3Widget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UStageWidget> BP_StageWidget;

	void ShowRestartWidget();
	void HideRestartWidget();
	void ShowMainMenuWidget();
	void HideMainMenuWidget();
	void ShowStageWidget();
	void HideStageWidget();
	void ShowClearWidget(float Health);
	void HideClearWidget();
	void ShowRankWidget();
	void HideRankWidget();
	void ShowStore1Widget();
	void HideStore1Widget();
	void ShowStore2Widget();
	void HideStore2Widget();
	void ShowStore3Widget();
	void HideStore3Widget();
	void UpdateHealthPercent(float HealthPercent);
	void UpdateVotePercent(float VotePercent);
	void UpdateGoalVotePercent();
	void UpdateGameTime();
	void UpdateTimeShape();
	void UpdateSlidingBar();
	void ClearSlidingTime();
	void UpdateMission(int Mission, float Fill, float FillMax, float TimePercent, float FillPercent);
	void SlidingOn();
	void ShowHUDStart();
	void ShowHUDClear();
	void ShowHUDLose();
	void Hiding();

	virtual void Tick(float DeltaTime) override;

	static int GameStart; // 게임 전 값 0, 한판 할 때 마다 1 증가
	static int ReachedLevel; // 클리어한 레벨의 값
	static int CurrentLevel;
	static int Gold;
	static float GoalVote;
	static float Minutetime;
	static int InGameMission;
	static bool GameIn;
	static TArray<float> S1R1Arr;
	static TArray<float> S1R2Arr;
	static TArray<float> S1R3Arr;
	static TArray<float> S2R1Arr;
	static TArray<float> S2R2Arr;
	static TArray<float> S2R3Arr;
	static TArray<float> S3R1Arr;
	static TArray<float> S3R2Arr;
	static TArray<float> S3R3Arr;
	static TArray<float> S4R1Arr;
	static TArray<float> S4R2Arr;
	static TArray<float> S4R3Arr;
	static TArray<float> S5R1Arr;
	static TArray<float> S5R2Arr;
	static TArray<float> S5R3Arr;

protected:

	virtual void BeginPlay() override;

	FTimerHandle GameTimerHandle;
	FTimerHandle SlidingTimerHandle;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* StageClearSound;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* StageFailSound;

private:

	UPROPERTY()
		class URestartWidget* RestartWidget;

	UPROPERTY()
		class UHUDWidget* HUDWidget;

	UPROPERTY()
		class UMainMenuWidget* MainMenuWidget;

	UPROPERTY()
		class UClearWidget* ClearWidget;

	UPROPERTY()
		class URankWidget* RankWidget;

	UPROPERTY()
		class UStore1Widget* Store1Widget;

	UPROPERTY()
		class UStore2Widget* Store2Widget;

	UPROPERTY()
		class UStore3Widget* Store3Widget;

	UPROPERTY()
		class UStageWidget* StageWidget;

};
