// Fill out your copyright notice in the Description page of Project Settings.


#include "SWorldTime.h"

// Sets default values for this component's properties
USWorldTime::USWorldTime()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void USWorldTime::BeginPlay()
{
	Super::BeginPlay();

	if(LoadDate.IsEmpty())
		WorldTime.ParseIso8601(*FString(WorldFirstDay), WorldTime);
	else
		WorldTime.ParseIso8601(*FString(LoadDate), WorldTime);

	UE_LOG(LogTemp, Warning, TEXT("Date: %s"), *WorldTime.ToString());

	GetWorld()->GetTimerManager().SetTimer(WorldTImeTimerHandle, this, &USWorldTime::NextDay, DayLenght);
}

void USWorldTime::NextDay()
{
	WorldTime += FTimespan(1, 0, 0, 0);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *WorldTime.ToString());
	GetWorld()->GetTimerManager().SetTimer(WorldTImeTimerHandle, this, &USWorldTime::NextDay, DayLenght);
}

void USWorldTime::SetLoadDate(FString ISODate)
{
	LoadDate = ISODate;
}

FString USWorldTime::Now()
{
	return WorldTime.ToString();
}


