// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SEventManager.h"
#include "SWorld.generated.h"

// Player stats struct
USTRUCT(BlueprintType)
struct FUPlayerCompany
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Money;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Income;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Customers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CustomersGrowth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, float> AppliedEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, bool> Researched;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, bool> HubsBuilded;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaintenanceCost;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NETORICAL_API USWorld : public UActorComponent
{
	GENERATED_BODY()
private:
	const FString WorldFirstDay = TEXT("1993-04-01");
	float DayLenght = 20.0f;

	//Components
	USEventManager *EventManagerComp;

	FUPlayerCompany Company;

	//World Time
	FString LoadDate;
	FDateTime WorldTime;
	FTimerHandle WorldTImeTimerHandle;


public:	
	// Sets default values for this component's properties
	USWorld();

	//World time
	void SetLoadDate(FString ISODate);
	FString Now();
	void IncreaseWorldTimeSpeed(float x);
	void DecreaseWorldTimeSpeed(float x);
	void NextDay();
	void PauseWorld();
	void UnPauseWorld();

	//Player Company
	void SetCompany(int32 Money, int32 Income, int32 Customers, int32 CustomersGrowth, TMap<FString, float> AppliedEffects, TMap<FString, bool> Researched, TMap<FString, bool> HubsBuilded, int32 MaintenanceCost);
	FUPlayerCompany* GetCompany();
	void CalcStatistics();

	// Apply and Remove effects to/from stats
	void ApplyEffect();
	void RemoveEffect(FString EffectID);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//World time
	void EndOfDay();
};
