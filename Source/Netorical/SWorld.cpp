// Fill out your copyright notice in the Description page of Project Settings.


#include "SWorld.h"

// Sets default values for this component's properties
USWorld::USWorld()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USWorld::BeginPlay()
{
	Super::BeginPlay();

	EventManagerComp = GetOwner()->FindComponentByClass<USEventManager>();

	if (LoadDate.IsEmpty())
		WorldTime.ParseIso8601(*FString(WorldFirstDay), WorldTime);
	else
		WorldTime.ParseIso8601(*FString(LoadDate), WorldTime);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *WorldTime.ToString());

	IncreaseWorldTimeSpeed(5.0f);
	GetWorld()->GetTimerManager().SetTimer(WorldTImeTimerHandle, this, &USWorld::EndOfDay, DayLenght);
}

// World time
void USWorld::EndOfDay()
{
	NextDay();

	/*
		There will be smt
	*/
	DecreaseWorldTimeSpeed(5.0f);
	GetWorld()->GetTimerManager().SetTimer(WorldTImeTimerHandle, this, &USWorld::EndOfDay, DayLenght);
}

void USWorld::SetLoadDate(FString ISODate)
{
	LoadDate = ISODate;
}

FString USWorld::Now()
{
	return WorldTime.ToString();
}

void USWorld::IncreaseWorldTimeSpeed(float x)
{
	DayLenght /= x;
}

void USWorld::DecreaseWorldTimeSpeed(float x)
{
	DayLenght *= x;
}

void USWorld::NextDay()
{
	WorldTime += FTimespan(1, 0, 0, 0);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *WorldTime.ToString());
}

void USWorld::PauseWorld()
{
	GetWorld()->GetTimerManager().PauseTimer(WorldTImeTimerHandle);
	EventManagerComp->PauseTimer(EventManagerComp->EventTimerManager);
}

void USWorld::UnPauseWorld()
{
	GetWorld()->GetTimerManager().UnPauseTimer(WorldTImeTimerHandle);
	EventManagerComp->UnPauseTimer(EventManagerComp->EventTimerManager);
}

//Player Company
void USWorld::SetCompany(int32 Money, int32 Income, int32 Customers, int32 CustomersGrowth, TMap<FString, float> AppliedEffects, TMap<FString, bool> Researched, TMap<FString, bool> HubsBuilded, int32 MaintenanceCost)
{
	Company.Money = Money;
	Company.Income = Income;
	Company.Customers = Customers;
	Company.CustomersGrowth = CustomersGrowth;
	Company.AppliedEffects = AppliedEffects;
	Company.Researched = Researched;
	Company.HubsBuilded = HubsBuilded;
	Company.MaintenanceCost = MaintenanceCost;
}

//idk yet will it be needed
void USWorld::CalcStatistics()
{
	//There will be logic of calculation income, maintenance cost, customers growth by hubs and applied effects.
}
