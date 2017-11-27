// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "JewelBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class JEWELBASH_API UJewelBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	/** Get a list of all player controllers, then pick the first local one we find. */
	UFUNCTION(BlueprintCallable, Category = "Match3 Gameplay", Meta = (WorldContext = "WorldContextObject"))
		static APlayerController* GetLocalPlayerController(UObject* WorldContextObject);

	/** Get the online account ID (as an encoded hex string) associated with the provided player controller's player state. Returns a blank string on failure. */
	UFUNCTION(BlueprintCallable, Category = "Match3 Gameplay")
		static FString GetOnlineAccountID(APlayerController* PlayerController);

	/** Function to identify whether or not game is currently being played. */
	UFUNCTION(BlueprintCallable, Category = "Match3 Gameplay", Meta = (WorldContext = "WorldContextObject"))
		static bool IsGameActive(UObject* WorldContextObject);

	/** Function to identify whether or not game is currently being played. */
	UFUNCTION(BlueprintCallable, Category = "Match3 Gameplay", Meta = (WorldContext = "WorldContextObject"))
		static void PauseGameTimer(UObject* WorldContextObject, bool bPause);
};
