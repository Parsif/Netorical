// Fill out your copyright notice in the Description page of Project Settings.


#include "SWorld.h"
#include <Engine.h>
#include "NetoricalSaveGame.h"
#include "NetoricalGameInstance.h"

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
	GameInstanceObj = Cast<UNetoricalGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	UE_LOG(LogTemp, Warning, TEXT("LoadData: %s"), *FString(GameInstanceObj->LoadGameData()->SaveDate));

	if (GameInstanceObj->LoadGameData()->SaveDate.IsEmpty())
		WorldTime.ParseIso8601(*FString(WorldFirstDay), WorldTime);
	else
		WorldTime.ParseIso8601(*GameInstanceObj->LoadGameData()->SaveDate, WorldTime);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *WorldTime.ToString());

	GetWorld()->GetTimerManager().SetTimer(WorldTImeTimerHandle, this, &USWorld::EndOfDay, DayLenght);
	GetWorld()->GetTimerManager().SetTimer(AutoSaveTimerHandle, this, &USWorld::AutoSaveGame, AutoSaveCycle);
}

/*
	World time 
*/
void USWorld::EndOfDay()
{

	/*
		There will be smt
	*/

	//SaveWorldData();

	NextDay();

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

void USWorld::IncreaseWorldTimeSpeed(float Factor)
{
	DayLenght /= Factor;
}

void USWorld::DecreaseWorldTimeSpeed(float Factor)
{
	DayLenght *= Factor;
}

void USWorld::NextDay()
{
	WorldTime += FTimespan(1, 0, 0, 0);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *WorldTime.ToIso8601());
}

void USWorld::PauseWorld()
{
	GetWorld()->GetTimerManager().PauseTimer(WorldTImeTimerHandle);
	EventManagerComp->PauseTimer(EventManagerComp->EventTimerManager);
	GetWorld()->GetTimerManager().PauseTimer(AutoSaveTimerHandle);
}

void USWorld::UnPauseWorld()
{
	GetWorld()->GetTimerManager().UnPauseTimer(WorldTImeTimerHandle);
	EventManagerComp->UnPauseTimer(EventManagerComp->EventTimerManager);
	GetWorld()->GetTimerManager().UnPauseTimer(AutoSaveTimerHandle);
}


/*
	Company
*/
void USWorld::CalcStatistics()
{
	//There will be logic of calculation income, maintenance cost, customers growth by hubs and applied effects.
}

/*
	Save/Load
*/
void USWorld::SaveWorldData()
{
	UE_LOG(LogTemp, Warning, TEXT("Save game"));
	GameInstanceObj->SaveGameData(WorldTime.ToIso8601());
}

void USWorld::LoadWorldData()
{
	WorldTime.ParseIso8601(*FString(GameInstanceObj->LoadGameData()->SaveDate), WorldTime);
}

void USWorld::AutoSaveGame()
{
	SaveWorldData();
	GetWorld()->GetTimerManager().SetTimer(AutoSaveTimerHandle, this, &USWorld::AutoSaveGame, AutoSaveCycle);
}