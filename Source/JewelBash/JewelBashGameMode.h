// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Tile.h"
#include "Grid.h"
#include "JewelSaveGame.h"
#include "JewelBashGameMode.generated.h"

USTRUCT(BlueprintType)
struct FJewelReward
{
	GENERATED_USTRUCT_BODY()

	/** Reward triggers at this interval. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ScoreInterval;

	/** Reward grants this much time upon triggering. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeAwarded;
};
/**
 * 
 */
UCLASS()
class JEWELBASH_API AJewelBashGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AJewelBashGameMode(const FObjectInitializer& ObjectInitializer);

	/** Called when the game starts. */
	virtual void BeginPlay() override;

	/** Remove the current menu widget and create a new one from the specified class, if provided. */
	UFUNCTION(BlueprintCallable, Category = "Game")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	/** How quickly tiles slide into place. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		float TileMoveSpeed;

	/** Function to call when starting a new Jewel game. */
	UFUNCTION(BlueprintCallable, Category = "Game")
		void GameRestart();

	/** Function to call when the game ends. */
	UFUNCTION(BlueprintCallable, Category = "Game")
		void GameOver();

	/** Function to identify whether or not game is currently being played. */
	UFUNCTION(BlueprintCallable, Category = "Game")
		bool IsGameActive() const;

	/** Function to pause the game timer (when things are moving). */
	UFUNCTION(BlueprintCallable, Category = "Game")
		void PauseGameTimer(bool bPause);

	/** Rewards that happen at intervals during the game. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game")
		TArray<FJewelReward> Rewards;

	/** Get remaining game time. */
	UFUNCTION(BlueprintCallable, Category = "Game")
		FString GetRemainingTimeAsString();

	/** Get remaining game time. */
	UFUNCTION(BlueprintCallable, Category = "Game")
		bool GetTimerPaused();

	/** Notifies when the player has taken a new place, e.g. 1st place, by beating one of the current high scores. If called with 0, just a regular scoring event. -1 = lose*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Game")
		void AwardPlace(int32 NewPlace, int32 PointsGiven);

	/** Notifies when the player has received a bonus/reward, currently a time increase. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Game")
		void AwardBonus();

	/** The game mode handles point-scoring. */
	void AddScore(int32 Points);

	/** The game mode understands the concept of combo power. */
	void SetComboPower(int32 NewComboPower);

	/** Combo power request. */
	UFUNCTION(BlueprintPure, Category = "Game")
		int32 GetComboPower();

	/** Combo power request. */
	UFUNCTION(BlueprintPure, Category = "Game")
		int32 GetMaxComboPower();

	/** Bomb power request (current) - susceptible to BP overriding by the JewelPlayerController. */
	UFUNCTION(BlueprintNativeEvent, Category = "Game")
		int32 CalculateBombPower();
	virtual int32 CalculateBombPower_Implementation();

	UFUNCTION(BlueprintImplementableEvent, Category = "Game")
		void GameWasWon(bool bGameWasWon);

	/** Used to force update the scores in the save data, say from the leader boards */
	UFUNCTION(BlueprintCallable, Category = "Save Game")
		void UpdateScoresFromLeaderBoard(int32 GoldScore, int32 SilverScore, int32 BronzeScore);

public:
	/** Current data being saved/loaded. Held as a UPROPERTY for GC reasons. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FJewelLevelSaveData SaveGameData;

	UPROPERTY(BlueprintReadOnly, Category = "Score")
		int32 FinalPlace;

protected:
	/** The widget class we will use as our menu when the game starts. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	/** The widget class we will use as our game over screen when the player loses. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
		TSubclassOf<UUserWidget> DefeatWidgetClass;

	/** The widget class we will use as our game over screen when the player wins. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
		TSubclassOf<UUserWidget> VictoryWidgetClass;

	/** The widget instance that we are using as our menu. */
	UPROPERTY()
		UUserWidget* CurrentWidget;

	/** Time until the game will end. */
	UPROPERTY(EditAnywhere)
		float TimeRemaining;

	FTimerHandle GameOverTimer;

	bool bGameWillBeWon;	
};
