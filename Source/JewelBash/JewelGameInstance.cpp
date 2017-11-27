// Fill out your copyright notice in the Description page of Project Settings.

#include "JewelGameInstance.h"
#include "JewelBash.h"
#include "JewelSaveGame.h"
#include "UnrealClient.h"

UJewelGameInstance::UJewelGameInstance()
{
	DefaultSaveGameSlot = TEXT("_JewelGame");
}

bool UJewelGameInstance::FindSaveDataForLevel(UObject* WorldContextObject, FJewelLevelSaveData& OutSaveData)
{
	const FString LevelName = UGameplayStatics::GetCurrentLevelName(WorldContextObject, true);
	if (FJewelLevelSaveData* FoundData = InstanceGameData->JewelSaveData.Find(LevelName))
	{
		OutSaveData = *FoundData;
		return true;
	}
	return false;
}

void UJewelGameInstance::UpdateSave(UObject* WorldContextObject, FJewelLevelSaveData& NewData)
{
	const FString LevelName = UGameplayStatics::GetCurrentLevelName(WorldContextObject, true);
	InstanceGameData->JewelSaveData.FindOrAdd(LevelName) = NewData;
	UpdateUIAfterSave();
}

void UJewelGameInstance::SaveGame()
{
	UGameplayStatics::SaveGameToSlot(InstanceGameData, GetSaveSlotName(), 0);
}

bool UJewelGameInstance::LoadCustomInt(FString FieldName, int32& Value)
{
	check(InstanceGameData);
	return InstanceGameData->LoadCustomInt(FieldName, Value);
}

void UJewelGameInstance::SaveCustomInt(FString FieldName, int32 Value)
{
	check(InstanceGameData);
	InstanceGameData->SaveCustomInt(FieldName, Value);
}

void UJewelGameInstance::ClearCustomInt(FString FieldName)
{
	check(InstanceGameData);
	InstanceGameData->ClearCustomInt(FieldName);
}

void UJewelGameInstance::Init()
{
	// Point to a default save slot at startup. We will later change our save slot when we log in.
	InitSaveGameSlot();

	LoginChangedHandle = FCoreDelegates::OnUserLoginChangedEvent.AddUObject(this, &UJewelGameInstance::OnLoginChanged);
	EnteringForegroundHandle = FCoreDelegates::ApplicationHasEnteredForegroundDelegate.AddUObject(this, &UJewelGameInstance::OnEnteringForeground);
	EnteringBackgroundHandle = FCoreDelegates::ApplicationWillEnterBackgroundDelegate.AddUObject(this, &UJewelGameInstance::OnEnteringBackground);
	ViewportHandle = FViewport::ViewportResizedEvent.AddUObject(this, &UJewelGameInstance::OnViewportResize_Internal);

	Super::Init();
}



void UJewelGameInstance::Shutdown()
{
	FCoreDelegates::OnUserLoginChangedEvent.Remove(LoginChangedHandle);
	FCoreDelegates::OnUserLoginChangedEvent.Remove(EnteringForegroundHandle);
	FCoreDelegates::OnUserLoginChangedEvent.Remove(EnteringBackgroundHandle);
	FViewport::ViewportResizedEvent.Remove(ViewportHandle);


	Super::Shutdown();
}

void UJewelGameInstance::InitSaveGameSlot()
{
	const FString SaveSlotName = GetSaveSlotName();
	if (!UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
	{
		// Clear default save file, if it exists.
		if (UGameplayStatics::DoesSaveGameExist(DefaultSaveGameSlot, 0))
		{
			UGameplayStatics::DeleteGameInSlot(DefaultSaveGameSlot, 0);
		}
		// If we have no save object, create one.
		if (InstanceGameData == nullptr)
		{
			// We're either not logged in with an Online ID, or we have no save data to transfer over (usually, this indicates program startup).
			InstanceGameData = Cast<UJewelSaveGame>(UGameplayStatics::CreateSaveGameObject(UJewelSaveGame::StaticClass()));
		}
		UGameplayStatics::SaveGameToSlot(InstanceGameData, SaveSlotName, 0);
	}
	else
	{
		InstanceGameData = Cast<UJewelSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	}
	check(InstanceGameData);
}

FString UJewelGameInstance::GetSaveSlotName() const
{
	return SaveGamePrefix + DefaultSaveGameSlot;
}

void UJewelGameInstance::RegisterOnlineID(FString NewOnlineID)
{
	SaveGamePrefix = NewOnlineID;
	InitSaveGameSlot();
}

void UJewelGameInstance::OnViewportResize_Internal(FViewport* Viewport, uint32 ID)
{
	OnViewportResize();
}
