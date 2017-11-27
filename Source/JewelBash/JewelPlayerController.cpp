// Fill out your copyright notice in the Description page of Project Settings.

#include "JewelPlayerController.h"
#include "JewelBash.h"

AJewelPlayerController::AJewelPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// We want the mouse cursor to show immediately on startup, without having to click in the window.
	bShowMouseCursor = true;

	// We need click/touch events to interact with our tiles.
	bEnableTouchEvents = bEnableClickEvents = true;
	bEnableTouchOverEvents = bEnableMouseOverEvents = true;

	ScoreChangeRate = 375.0f;
}

void AJewelPlayerController::AddScore(int32 Points, bool bForceImmediateUpdate)
{
	Score += Points;
	if (bForceImmediateUpdate)
	{
		DisplayedScore = (float)Score;
	}
	else
	{
		GetWorldTimerManager().SetTimer(TickScoreDisplayHandle, this, &AJewelPlayerController::TickScoreDisplay, 0.001f, true);
	}
}

int32 AJewelPlayerController::GetScore()
{
	return Score;
}

int32 AJewelPlayerController::GetDisplayedScore()
{
	return (int32)DisplayedScore;
}

int32 AJewelPlayerController::CalculateBombPower_Implementation()
{
	return 0;
}

void AJewelPlayerController::TickScoreDisplay()
{
	// This assumes score only goes up, or instantly drops when it is decreased.
	DisplayedScore += UGameplayStatics::GetWorldDeltaSeconds(this) * ScoreChangeRate;
	if (DisplayedScore >= (float)Score)
	{
		DisplayedScore = Score;
		GetWorldTimerManager().ClearTimer(TickScoreDisplayHandle);
	}
}
