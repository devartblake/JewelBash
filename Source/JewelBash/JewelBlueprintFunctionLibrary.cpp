// Fill out your copyright notice in the Description page of Project Settings.

#include "JewelBlueprintFunctionLibrary.h"
#include "JewelBash.h"
#include "JewelBashGameMode.h"

APlayerController* UJewelBlueprintFunctionLibrary::GetLocalPlayerController(UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			APlayerController* PlayerController = Iterator->Get();
			if (PlayerController->IsLocalController())
			{
				// For this project, we will only ever have one local player.
				return PlayerController;
			}
		}
	}
	return nullptr;
}

FString UJewelBlueprintFunctionLibrary::GetOnlineAccountID(APlayerController* PlayerController)
{
	if (PlayerController && PlayerController->PlayerState && PlayerController->PlayerState->UniqueId.IsValid())
	{
		return PlayerController->PlayerState->UniqueId->GetHexEncodedString();
	}
	return FString();
}

bool UJewelBlueprintFunctionLibrary::IsGameActive(UObject* WorldContextObject)
{
	if (AJewelBashGameMode* GameMode = Cast<AJewelBashGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		if (GameMode->IsGameActive())
		{
			return true;
		}
	}
	return false;
}

void UJewelBlueprintFunctionLibrary::PauseGameTimer(UObject* WorldContextObject, bool bPause)
{
	if (AJewelBashGameMode* GameMode = Cast<AJewelBashGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		GameMode->PauseGameTimer(bPause);
	}
}