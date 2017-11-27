// Fill out your copyright notice in the Description page of Project Settings.

#include "JewelSaveGame.h"
#include "JewelBash.h"
#include "Kismet/GameplayStatics.h"

bool UJewelSaveGame::LoadCustomInt(FString FieldName, int32& Value) const
{
	const int32* ValuePointer = JewelCustomIntData.Find(FieldName);
	if (ValuePointer != nullptr)
	{
		Value = *ValuePointer;
		return true;
	}
	return false;
}

void UJewelSaveGame::SaveCustomInt(FString FieldName, int32 Value)
{
	JewelCustomIntData.FindOrAdd(FieldName) = Value;
}

void UJewelSaveGame::ClearCustomInt(FString FieldName)
{
	JewelCustomIntData.Remove(FieldName);
}