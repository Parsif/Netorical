// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NetoricalGameInstance.h"
#include "SEventManager.h"
#include "SWorld.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NETORICAL_API USWorld : public UActorComponent
{
	GENERATED_BODY()
private:
	const FString WorldFirstDay = TEXT("1993-04-01");
	float DayLenght = 20.0f;

	//Components
	USEventManager *EventManagerComp;
	class UNetoricalGameInstance *GameInstanceObj;

	//World Time
	FString LoadDate;
	FDateTime WorldTime;
	FTimerHandle WorldTImeTimerHandle;
	FTimerHandle AutoSaveTimerHandle;

	//Save
	const float AutoSaveCycle = 180.0f;

public:	
	// Sets default values for this component's properties
	USWorld();

	//World time
	void SetLoadDate(FString ISODate);
	FString Now();
	void IncreaseWorldTimeSpeed(float Factor);
	void DecreaseWorldTimeSpeed(float Factor);
	void NextDay();
	void PauseWorld();
	void UnPauseWorld();

	//Player Company
	void CalcStatistics();

	// Apply and Remove effects to/from stats
	void ApplyEffect();
	void RemoveEffect(FString EffectID);

	//Save/load game
	void SaveWorldData();
	void LoadWorldData();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//World time
	void EndOfDay();
	void AutoSaveGame();
};
