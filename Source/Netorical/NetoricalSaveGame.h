// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "NetoricalSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class NETORICAL_API UNetoricalSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UNetoricalSaveGame();

	UPROPERTY()
		int32 SaveMoney;
	UPROPERTY()
		int32 SaveIncome;
	UPROPERTY()
		int32 SaveCutomers;
	UPROPERTY()
		int32 SaveCustomersGrowth;
	UPROPERTY()
		TMap<FString, float> SaveAppliedEffects;
	UPROPERTY()
		TArray<FString> SavetResearched;
	UPROPERTY()
		TArray<FString> SaveHubsBuilded;
	UPROPERTY()
		int32 SaveMaintenanceCost;
	UPROPERTY()
		FString SaveDate;
	
};
