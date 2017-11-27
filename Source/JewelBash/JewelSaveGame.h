// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "JewelSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FJewelLevelSaveData
{
	GENERATED_USTRUCT_BODY();

	/** Score to beat to get gold. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 GoldScore;

	/** Score to beat to get silver. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 SilverScore;

	/** Score to beat to get bronze. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 BronzeScore;

	/** Player's personal best score. Not necessarily a gold-medal score. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TopScore;
};

/**
 * 
 */
UCLASS()
class JEWELBASH_API UJewelSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	/**
	*	@see UGameplayStatics::CreateSaveGameObject
	*	@see UGameplayStatics::SaveGameToSlot
	*	@see UGameplayStatics::DoesSaveGameExist
	*	@see UGameplayStatics::LoadGameFromSlot
	*	@see UGameplayStatics::DeleteGameInSlot
	*/

	/** Complete list of levels played in Jewel mode. */
	UPROPERTY()
	TMap<FString, FJewelLevelSaveData> JewelSaveData;


	//~
	//~ Custom global fields for saved games.
	//~

	/** Load the int32 value associated with the requested variable. */
	bool LoadCustomInt(FString FieldName, int32& Value) const;

	/** Create a variable in the saved game and associate the provided integer value with it. */
	void SaveCustomInt(FString FieldName, int32 Value);

	/** Erase a variable from the saved game. */
	void ClearCustomInt(FString FieldName);

protected:
	UPROPERTY()
	TMap<FString, int32> JewelCustomIntData;
};
