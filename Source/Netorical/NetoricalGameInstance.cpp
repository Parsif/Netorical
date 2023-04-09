// Fill out your copyright notice in the Description page of Project Settings.


#include "NetoricalGameInstance.h"
#include "Engine.h"

void UNetoricalGameInstance::Init()
{
	GameData = Cast<UNetoricalSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, 0));

	if (!GameData)
	{	
		GameData = Cast<UNetoricalSaveGame>(UGameplayStatics::CreateSaveGameObject(UNetoricalSaveGame::StaticClass()));

		UpdateSavePCompanyData();
		GameData->SaveDate = nullptr;

		UGameplayStatics::SaveGameToSlot(GameData, SaveSlot, 0);
	}
}

void UNetoricalGameInstance::SaveGameData(FString SaveDate)
{
	if (GameData)
	{
		UpdateSavePCompanyData();
		GameData->SaveDate = FString(SaveDate);

		UGameplayStatics::SaveGameToSlot(GameData, SaveSlot, 0);
	}
}

UNetoricalSaveGame* UNetoricalGameInstance::LoadGameData()
{
	if (GameData)
		return GameData;
	else
		return nullptr;
}

void UNetoricalGameInstance::UpdateSavePCompanyData()
{
	GameData->SaveMoney = PMoney;
	GameData->SaveIncome = PIncome;
	GameData->SaveCutomers = PCutomers;
	GameData->SaveCustomersGrowth = PCustomersGrowth;
	GameData->SaveAppliedEffects = PAppliedEffects;
	GameData->SavetResearched = PResearched;
	GameData->SaveHubsBuilded = PHubsBuilded;
	GameData->SaveMaintenanceCost = PMaintenanceCost;
}