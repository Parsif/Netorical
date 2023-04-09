// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NetoricalSaveGame.h"
#include "NetoricalGameInstance.generated.h"

UCLASS()
class NETORICAL_API UNetoricalGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	//Player stats
	int32 PMoney;
	int32 PIncome;
	int32 PCutomers;
	int32 PCustomersGrowth;
	TMap<FString, float> PAppliedEffects;
	TArray<FString> PResearched;
	TArray<FString> PHubsBuilded;
	int32 PMaintenanceCost;

	UPROPERTY()
	TObjectPtr<UNetoricalSaveGame> GameData;

	FString SaveSlot = "NetoricalSaveData";

public:
	void SaveGameData(FString SaveDate);
	UNetoricalSaveGame* LoadGameData();
	void UpdateSavePCompanyData();
private:
		void Init() override;
};
